#ifndef QTHREADSENDER_H
#define QTHREADSENDER_H

#include <QAbstractEventDispatcher>
#include <QMetaObject>
#include <QObject>
#include <QThread>
#include <exception>
#include <tuple>
#include <type_traits>
#include <stdexec/concepts.hpp>
#include <stdexec/execution.hpp>

namespace QtStdExec
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
        friend QThreadScheduler tag_invoke(stdexec::get_completion_scheduler_t<CPO>, default_env env) noexcept
        {
            return QThreadScheduler(env.thread);
        }
    };
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

        friend default_env tag_invoke(stdexec::get_env_t, const QThreadSender &snd) noexcept
        {
            return {snd.m_thread};
        }

        template <class Recv>
        friend inline QThreadOperationState<Recv> tag_invoke(stdexec::connect_t, QThreadSender sender, Recv &&receiver)
        {
            return QThreadOperationState<Recv>(std::move(receiver), sender.thread());
        }

      private:
        QThread *m_thread;
    };

    friend QThreadSender tag_invoke(stdexec::schedule_t, QThreadScheduler sched)
    {
        return QThreadSender(sched.thread());
    }
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

inline QThreadScheduler qThreadAsScheduler(QThread *thread)
{
    return QThreadScheduler(thread);
}

inline QThreadScheduler qThreadAsScheduler(QThread &thread)
{
    return QThreadScheduler(&thread);
}

template <class Recv>
class QThreadOperationState
{
  public:
    QThreadOperationState(Recv &&receiver, QThread *thread)
        : m_receiver(std::move(receiver))
        , m_thread(thread)
    {}
    void start() noexcept
    {
        QMetaObject::invokeMethod(
            m_thread->eventDispatcher(), [this]() { stdexec::set_value(std::move(m_receiver)); }, Qt::QueuedConnection);
    }
    friend void tag_invoke(stdexec::tag_t<stdexec::start>, QThreadOperationState &oper_state) noexcept
    {
        oper_state.start();
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
        friend QThreadScheduler tag_invoke(stdexec::get_completion_scheduler_t<CPO>, default_env env) noexcept
        {
            return QThreadScheduler(env.thread);
        }
    };
    friend default_env tag_invoke(stdexec::get_env_t, const QObjectSender &snd) noexcept
    {
        return {snd.m_obj->thread()};
    }

  public:
    using is_sender = void;
    using completion_signatures =
        stdexec::completion_signatures<stdexec::set_value_t(Args...), stdexec::set_error_t(std::exception_ptr)>;

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
    friend inline QObjectOperationState<Recv, QObj, Ret, Args...> tag_invoke(stdexec::tag_t<stdexec::connect>,
                                                                             QObjectSender sender,
                                                                             Recv &&receiver)
    {
        return QObjectOperationState<Recv, QObj, Ret, Args...>(std::move(receiver), sender.m_obj, sender.m_ptr);
    }

  private:
    QObj *m_obj;
    m_ptr_type m_ptr;
};

template <class Recv, class QObj, class Ret, class... Args>
class QObjectOperationState
{
  public:
    using m_ptr_type = Ret (QObj::*)(Args...);
    QObjectOperationState(Recv &&receiver, QObj *obj, m_ptr_type ptr)
        : m_receiver(std::move(receiver))
        , m_obj(obj)
        , m_ptr(ptr)
    {}
    friend void tag_invoke(stdexec::tag_t<stdexec::start>, QObjectOperationState &oper_state) noexcept
    {
        oper_state.connection = QObject::connect(oper_state.m_obj, oper_state.m_ptr, [&oper_state](Args... args) {
            stdexec::set_value(std::move(oper_state.m_receiver), std::forward<Args>(args)...);
        });
    }
    ~QObjectOperationState()
    {
        QObject::disconnect(connection);
    }

  private:
    Recv m_receiver;
    QObj *m_obj;
    m_ptr_type m_ptr;
    QMetaObject::Connection connection;
};

template <class QObj, class Ret, class... Args>
inline QObjectSender<QObj, Ret, Args...> qObjectAsSender(QObj *obj, Ret (QObj::*ptr)(Args...))
{
    return QObjectSender<QObj, Ret, Args...>(obj, ptr);
}

template <class QObj, class Ret, class... Args>
inline auto qObjectAsTupleSender(QObj *obj, Ret (QObj::*ptr)(Args...))
{
    return QObjectSender<QObj, Ret, Args...>(obj, ptr) |
           stdexec::then([](Args... args) { return std::tuple<std::remove_reference_t<Args>...>(std::move(args)...); });
}

} // namespace QtStdExec

#endif // QTHREADSENDER_H
