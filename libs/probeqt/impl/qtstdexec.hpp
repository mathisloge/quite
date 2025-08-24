// SPDX-FileCopyrightText: 2025 Mathis Logemann <mathis@quite.rocks>
//
// SPDX-License-Identifier: MIT

#pragma once
#include <QAbstractEventDispatcher>
#include <QMetaObject>
#include <QObject>
#include <QThread>
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
        : thread_(thread)
    {}

    QThread *thread()
    {
        return thread_;
    }

    struct DefaultEnv
    {
        QThread *thread;
        template <typename CPO>
        auto query(stdexec::get_completion_scheduler_t<CPO>) const noexcept
        {
            return QThreadScheduler{thread};
        }
    };

    DefaultEnv query(stdexec::get_env_t) noexcept
    {
        return {thread_};
    }

    auto schedule() const noexcept
    {
        return QThreadSender{thread_};
    }

    class QThreadSender
    {
      public:
        using is_sender = void;
        using completion_signatures =
            stdexec::completion_signatures<stdexec::set_value_t(), stdexec::set_error_t(std::exception_ptr)>;

        explicit QThreadSender(QThread *thread)
            : thread_(thread)
        {}

        QThread *thread()
        {
            return thread_;
        }

        DefaultEnv query(stdexec::get_env_t) const noexcept
        {
            return {thread_};
        }

        template <class Recv>
        QThreadOperationState<Recv> connect(Recv &&receiver)
        {
            return QThreadOperationState<Recv>(std::forward<Recv>(receiver), thread());
        }

      private:
        QThread *thread_;
    };

    bool operator==(const QThreadScheduler &b) const noexcept = default;

  private:
    QThread *thread_ = nullptr;
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
    Q_DISABLE_COPY_MOVE(QThreadOperationState);
    QThreadOperationState(Recv &&receiver, QThread *thread)
        : receiver_{std::move(receiver)}
        , thread_{thread}
    {}

    ~QThreadOperationState() = default;

    void start() noexcept
    {
        QMetaObject::invokeMethod(
            thread_->eventDispatcher(), [this]() { stdexec::set_value(std::move(receiver_)); }, Qt::QueuedConnection);
    }

  private:
    Recv receiver_;
    QThread *thread_;
};

template <class Recv, class QObj, class Ret, class... Args>
class QObjectOperationState;

template <class QObj, class Ret, class... Args>
class QObjectSender
{
    struct DefaultEnv
    {
        QThread *thread;
        template <typename CPO>
        auto query(stdexec::get_completion_scheduler_t<CPO> /*cpo*/) const noexcept
        {
            return QThreadScheduler{thread};
        }
    };

    DefaultEnv query([[maybe_unused]] stdexec::get_env_t env) noexcept
    {
        return {obj_->thread()};
    }

  public:
    using is_sender = void;
    using completion_signatures = stdexec::completion_signatures<stdexec::set_value_t(Args...),
                                                                 stdexec::set_error_t(std::exception_ptr),
                                                                 stdexec::set_stopped_t()>;

    using MemberPointer = Ret (QObj::*)(Args...);
    QObjectSender(QObj *obj, MemberPointer ptr)
        : obj_(obj)
        , ptr_(ptr)
    {}

    QObj *object()
    {
        return obj_;
    }

    MemberPointer member_ptr()
    {
        return ptr_;
    }

    template <class Recv>
    QObjectOperationState<Recv, QObj, Ret, Args...> connect(Recv &&receiver)
    {
        return QObjectOperationState<Recv, QObj, Ret, Args...>(std::forward<Recv>(receiver), obj_, ptr_);
    }

  private:
    QObj *obj_;
    MemberPointer ptr_;
};

template <class Recv, class QObj, class Ret, class... Args>
class QObjectOperationState
{
  public:
    using operation_state_concept = stdexec::operation_state_t;
    using m_ptr_type = Ret (QObj::*)(Args...);

    QObjectOperationState(Recv &&receiver, QObj *obj, m_ptr_type ptr)
        : receiver_(std::move(receiver))
        , obj_(obj)
        , ptr_(ptr)
    {}

  private:
    struct StopCallback
    {
        QObjectOperationState *self;

        void operator()() const noexcept
        {
            self->stop_callback_.reset();
            QObject::disconnect(self->connection_);
            if (not self->completed_.test_and_set(std::memory_order_acq_rel))
            {
                QMetaObject::invokeMethod(
                    self->obj_->thread()->eventDispatcher(),
                    [this]() { stdexec::set_stopped(std::move(self->receiver_)); },
                    Qt::QueuedConnection);
            }
        }
    };

  private:
    using stop_token_type = stdexec::stop_token_of_t<stdexec::env_of_t<Recv>>;
    using stop_callback_type = typename stop_token_type::template callback_type<StopCallback>;

  public:
    void start() noexcept
    {
        stop_callback_.emplace(stdexec::get_stop_token(stdexec::get_env(receiver_)), StopCallback{this});
        connection_ = QObject::connect(
            obj_,
            ptr_,
            obj_,
            [this](Args... args) {
                QObject::disconnect(connection_);
                stop_callback_.reset();
                if (!completed_.test_and_set(std::memory_order_acq_rel))
                {
                    QMetaObject::invokeMethod(
                        obj_,
                        [this, &args...] { stdexec::set_value(std::move(receiver_), std::forward<Args>(args)...); },
                        Qt::QueuedConnection);
                }
            },
            Qt::SingleShotConnection);
    }

  private:
    Recv receiver_;
    QObj *obj_;
    m_ptr_type ptr_;
    QMetaObject::Connection connection_;
    std::atomic_flag completed_{false};
    std::optional<stop_callback_type> stop_callback_;
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
           stdexec::then([](Args... args) { return std::tuple<std::remove_cvref_t<Args>...>(std::move(args)...); });
}

} // namespace quite
