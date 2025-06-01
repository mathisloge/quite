#pragma once

#include <QAbstractEventDispatcher>
#include <QMetaObject>
#include <QObject>
#include <QThread>
#include <exception>
#include <tuple>
#include <type_traits>
#include <stdexec/concepts.hpp>
#include <stdexec/execution.hpp>

namespace quite
{

template <class Recv>
class QThreadOperationState;

class QThreadScheduler
{
  public:
    explicit QThreadScheduler(QThread *thread)
        : m_thread(thread)
    {}

    QThread *thread()
    {
        return m_thread;
    }

    struct default_env
    {
        QThread *thread;
        template <typename CPO>
        auto query(stdexec::get_completion_scheduler_t<CPO>) const noexcept
        {
            return QThreadScheduler{thread};
        }
    };

    default_env query(stdexec::get_env_t) noexcept
    {
        return {m_thread};
    }

    auto schedule() const noexcept
    {
        return QThreadSender{m_thread};
    }

    class QThreadSender
    {
      public:
        using is_sender = void;
        using completion_signatures =
            stdexec::completion_signatures<stdexec::set_value_t(), stdexec::set_error_t(std::exception_ptr)>;

        explicit QThreadSender(QThread *thread)
            : m_thread(thread)
        {}

        QThread *thread()
        {
            return m_thread;
        }

        default_env query(stdexec::get_env_t) const noexcept
        {
            return {m_thread};
        }

        template <class Recv>
        QThreadOperationState<Recv> connect(Recv &&receiver)
        {
            return QThreadOperationState<Recv>(std::forward<Recv>(receiver), thread());
        }

      private:
        QThread *m_thread;
    };

    friend bool operator==(const QThreadScheduler &a, const QThreadScheduler &b) noexcept
    {
        return a.m_thread == b.m_thread;
    }
    friend bool operator!=(const QThreadScheduler &a, const QThreadScheduler &b) noexcept
    {
        return a.m_thread != b.m_thread;
    }

  private:
    QThread *m_thread = nullptr;
};

inline QThreadScheduler qthread_as_scheduler(QThread *thread)
{
    return QThreadScheduler(thread);
}

inline QThreadScheduler qthread_as_scheduler(QThread &thread)
{
    return QThreadScheduler(&thread);
}

template <class Recv>
class QThreadOperationState
{
  public:
    using operation_state_concept = stdexec::operation_state_t;
    QThreadOperationState(Recv &&receiver, QThread *thread)
        : m_receiver(std::move(receiver))
        , m_thread(thread)
    {}
    void start() noexcept
    {
        QMetaObject::invokeMethod(
            m_thread->eventDispatcher(), [this]() { stdexec::set_value(std::move(m_receiver)); }, Qt::QueuedConnection);
    }

  private:
    Q_DISABLE_COPY_MOVE(QThreadOperationState)
    Recv m_receiver;
    QThread *m_thread;
};

template <class Recv, class QObj, class Ret, class... Args>
class QObjectOperationState;

template <class QObj, class Ret, class... Args>
class QObjectSender
{
    struct default_env
    {
        QThread *thread;
        template <typename CPO>
        auto query(stdexec::get_completion_scheduler_t<CPO>) const noexcept
        {
            return QThreadScheduler{thread};
        }
    };
    default_env query(stdexec::get_env_t) noexcept
    {
        return {m_obj->thread()};
    }

  public:
    using is_sender = void;
    using completion_signatures = stdexec::completion_signatures<stdexec::set_value_t(Args...),
                                                                 stdexec::set_error_t(std::exception_ptr),
                                                                 stdexec::set_stopped_t()>;

    using m_ptr_type = Ret (QObj::*)(Args...);
    QObjectSender(QObj *obj, m_ptr_type ptr)
        : m_obj(obj)
        , m_ptr(ptr)
    {}
    QObj *object()
    {
        return m_obj;
    }
    m_ptr_type member_ptr()
    {
        return m_ptr;
    }
    template <class Recv>
    QObjectOperationState<Recv, QObj, Ret, Args...> connect(Recv &&receiver)
    {
        return QObjectOperationState<Recv, QObj, Ret, Args...>(std::forward<Recv>(receiver), m_obj, m_ptr);
    }

  private:
    QObj *m_obj;
    m_ptr_type m_ptr;
};

template <class Recv, class QObj, class Ret, class... Args>
class QObjectOperationState
{
  public:
    using operation_state_concept = stdexec::operation_state_t;
    using m_ptr_type = Ret (QObj::*)(Args...);

    QObjectOperationState(Recv &&receiver, QObj *obj, m_ptr_type ptr)
        : m_receiver(std::move(receiver))
        , m_obj(obj)
        , m_ptr(ptr)
    {}

  private:
    struct stop_callback_t
    {
        QObjectOperationState *self;

        void operator()() const noexcept
        {
            self->m_stop_callback.reset();
            QObject::disconnect(self->m_connection);
            if (!self->m_completed.test_and_set(std::memory_order_acq_rel))
            {
                QMetaObject::invokeMethod(
                    self->m_obj->thread()->eventDispatcher(),
                    [this]() { stdexec::set_stopped(std::move(self->m_receiver)); },
                    Qt::QueuedConnection);
            }
        }
    };

  private:
    using stop_token_type = stdexec::stop_token_of_t<stdexec::env_of_t<Recv>>;
    using stop_callback_type = typename stop_token_type::template callback_type<stop_callback_t>;

  public:
    void start() noexcept
    {
        m_stop_callback.emplace(stdexec::get_stop_token(stdexec::get_env(m_receiver)), stop_callback_t{this});
        m_connection = QObject::connect(
            m_obj,
            m_ptr,
            m_obj,
            [this](Args... args) {
                QObject::disconnect(m_connection);
                m_stop_callback.reset();
                if (!m_completed.test_and_set(std::memory_order_acq_rel))
                {
                    QMetaObject::invokeMethod(
                        m_obj,
                        [this, &args...] { stdexec::set_value(std::move(m_receiver), std::forward<Args>(args)...); },
                        Qt::QueuedConnection);
                }
            },
            Qt::SingleShotConnection);
    }
    ~QObjectOperationState() = default;

  private:
    Recv m_receiver;
    QObj *m_obj;
    m_ptr_type m_ptr;
    QMetaObject::Connection m_connection;
    std::atomic_flag m_completed{false};
    std::optional<stop_callback_type> m_stop_callback;
};

template <class QObj, class Ret, class... Args>
inline QObjectSender<QObj, Ret, Args...> qobject_as_sender(QObj *obj, Ret (QObj::*ptr)(Args...))
{
    return QObjectSender<QObj, Ret, Args...>(obj, ptr);
}

template <class QObj, class Ret, class... Args>
inline auto qobject_as_tuple_sender(QObj *obj, Ret (QObj::*ptr)(Args...))
{
    return QObjectSender<QObj, Ret, Args...>(obj, ptr) |
           stdexec::then([](Args... args) { return std::tuple<std::remove_reference_t<Args>...>(std::move(args)...); });
}

} // namespace quite
