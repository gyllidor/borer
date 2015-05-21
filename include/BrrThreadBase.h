//! ************************************************************************************************
//! @file   BrrThreadBase.h
//! @brief  abstract class wrapper for pthread. For more information man pthread*.
//! @brief  Just inherit this class, implement one method (ThreadFunction) and
//! @brief  run this method in separeted thread.
//! @author gyllidor (gyllidor@ukr.net)
//! @date   24 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
#ifndef THREAD_BASE_H
#define THREAD_BASE_H

// local
#include "BrrBase.h"
#include "BrrRWLock.h"

// system
#include <pthread.h>

namespace brr
{

class ThreadBase : public Base
{
public: // methods
    //! ********************************************************************************************
    //! @brief default contructor, just set default value for members.
    //! By default cancel state is PTHREAD_CANCEL_DISABLE, cancel type PTHREAD_CANCEL_DEFERRED
    //! ********************************************************************************************
    ThreadBase();

    //! ********************************************************************************************
    //! @brief contructor.
    //! By default cancel state is PTHREAD_CANCEL_DISABLE, cancel type PTHREAD_CANCEL_DEFERRED
    //! @param threadName - set thread name for object.
    //! ********************************************************************************************
    ThreadBase(const std::string& threadName);

    //! ********************************************************************************************
    //! @brief destructor - empty body.
    //! ********************************************************************************************
    virtual ~ThreadBase();

    //! ********************************************************************************************
    //! @brief create thread and run void* ThreadMethod(). By default cancel state is
    //! PTHREAD_CANCEL_DISABLE. If pthread_cancel_state(PTHREAD_CANCEL_DISABLE) failed then warning
    //! message will be printed. The new thread terminates in one of the following ways:
    //! 1) It calls pthread_exit(), specifying an exit status value that is available to another
    //! thread in the same process that calls pthread_join(3).
    //! 2) It returns from ThreadMethod(). This is equivalent to calling pthread_exit() with the
    //! value supplied in the return statement.
    //! 3) It is canceled Cancel() (see pthread_cancel()).
    //! 4) Any of the threads in the process calls exit(), or the main thread performs a return from
    //! main(). This causes the termination of all threads in the process.
    //! man pthread_create.
    //! @return false if thread is already running or pthread_create() failed (also errno printed)
    //! otherwise true.
    //! ********************************************************************************************
    virtual bool Run();

    //! ********************************************************************************************
    //! @brief  check state of the thread - running or not.
    //! @return true if thread is running otherwise false.
    //! ********************************************************************************************
    virtual bool IsRunning();

    //! ********************************************************************************************
    //! @brief Join() - join with a terminated thread. The Join() function waits for the thread to
    //! terminate. If that thread has already terminated, then Join() returns immediately. The
    //! thread must be joinable.
    //! man pthread_join.
    //! @return On success, Join() returns true; on error, it returns false and prints errno.
    //! ********************************************************************************************
    virtual bool Join();

    //! ********************************************************************************************
    //! @brief  Similar to Join() but if retval is not NULL, then Join() copies the exit status of
    //! the target thread (i.e., the value that the target thread supplied to  pthread_exit()) into
    //! the location pointed to by *pResult. If the target thread was canceled, then
    //! PTHREAD_CANCELED is placed in *pResult. If multiple threads simultaneously try to join with
    //! the same thread, the results are undefined. If the thread calling Join() is canceled, then
    //! the target thread will remain joinable (i.e., it will not be detached).
    //! man pthread_join.
    //! @return On success, Join() returns true; on error, it returns false and prints errno.
    //! ********************************************************************************************
    virtual bool Join(void** pResult);

    //! ********************************************************************************************
    //! @brief The Cancel() function sends a cancellation request to the thread m_thread. Whether
    //! and when the target thread reacts to the cancellation request depends on two attributes that
    //! are under the control of that thread: its cancelability state and type. A thread's
    //! cancelability state, determined by SetCancelState(3), can be enabled or disabled
    //! (NOTE/ATTENTION: the default for new threads for ThreadBase  notwithstanding pthread). If a
    //! thread has disabled cancellation,then a cancellation request remains queued until the thread
    //! enables cancellation. If a thread has enabled cancellation, then its cancelability type
    //! determines when cancellation occurs. A thread's cancellation type, determined by
    //! SetCancelType() (man pthread_setcanceltype), may be either asynchronous or deferred
    //! (the default for new threads). Asynchronous cancelability means that the thread can be
    //! canceled at any time (usually immediately, but the system does not guarantee this).
    //! Deferred cancelability means that cancellation will be delayed until the thread next calls a
    //! function that is a cancellation point.
    //! man pthread_cancel.
    //! @return On success, Cancel() returns true; on error, it returns false and prints errno.
    //! ********************************************************************************************
    virtual bool Cancel();

    //! ********************************************************************************************
    //! @brief NotifyToStop() - just set m_isRunning to false (method is thread safe). In case
    //! IsRunning() using in ThreadMethod() to check should thread to stop or not - this method
    //! (NotifyToStop()) can be used for notifing thread to stop.
    //! ********************************************************************************************
    virtual void NotifyToStop();

    //! ********************************************************************************************
    //! @brief The Detach() method marks the thread identified by thread as detached. When a
    //! detached thread terminates, its resources are automatically released back to the system
    //! without the need for another thread to join with the terminated thread. Attempting to
    //! detach an already detached thread results in unspecified behavior.
    //! man pthrad_detach.
    //! @return On success true; on error, it returns false and prints errno.
    //! ********************************************************************************************
    virtual bool Detach();

    //! ********************************************************************************************
    //! @brief The Equal() method compares two thread identifiers.
    //! man pthread_equal.
    //! @return If the two thread IDs are equal, Equal() returns true; otherwise, it returns false.
    //! ********************************************************************************************
    virtual bool Equal(const ThreadBase& thread);

    //! ********************************************************************************************
    //! @brief The Self() method returns the ID of the calling thread. This is the same value that
    //! is returned in *thread in the pthread_create(3) call that created this thread.
    //! man pthread_self.
    //! @return thread ID.
    virtual pthread_t Self();

protected: // methods
    //! ********************************************************************************************
    //! @brief Implement this method in derived class. Call Run() and ThreadMethod will work in
    //! separated thread.
    //! @return returned data(must be on the heap) you can get from Join(**pResult).
    //! ********************************************************************************************
    virtual void* StartRoutine() = 0;

    //! ********************************************************************************************
    //! @brief The SetCancelState() sets the cancelability state of the calling thread to the
    //! value given in state. The state argument must have one of the following values:
    //! 1) PTHREAD_CANCEL_ENABLE - the thread is cancelable.
    //! 2) PTHREAD_CANCEL_DISABLE - the thread is not cancelable. If a cancellation request is
    //! received, it is blocked until cancelability is enabled. This is the default cancelability
    //! state in all new threads (for ThreadBase notwithstanding pthread).
    //! man pthread_setcancelstate. Call this method in StartRoutine().
    //! @return On success, SetCancelState() returns true; on error, it returns false and
    //! prints errno.
    //! ********************************************************************************************
    virtual bool SetCancelState(int state);

    //! ********************************************************************************************
    //! @brief The SetCancelType() sets the cancelability type of the calling thread to the value
    //! given in type. The type argument must have one of the following values:
    //! 1) PTHREAD_CANCEL_DEFERRED - A cancellation request is deferred until the thread next calls
    //! a function that is a cancellation point (see pthreads(7)). This is the default cancelability
    //! type in all new threads, including the initial thread.
    //! 2) PTHREAD_CANCEL_ASYNCHRONOUS - The thread can be canceled at any time. (Typically, it will
    //! be canceled immediately upon receiving a cancellation request, but the system doesn't
    //! guarantee this.)
    //! man pthread_setcanceltype. Call this method in StartRoutine().
    //! @return On success, SetCancelType() returns true; on error, it returns false
    //! and prints errno.
    //! ********************************************************************************************
    virtual bool SetCancelType(int type);

    //! ********************************************************************************************
    //! @brief Call SetCancelState(PTHREAD_CANCEL_ENABLE), USleep(second/1000) then
    //! SetCancelState(PTHREAD_CANCEL_DISABLE) inside. If a cancellation request was sent(Cancel())
    //! before CancelationPoint() then in point of CancelationPoint() thread will be canceled.
    //! ATTENTION this method use brr::USleep(brr::sc_sc_secondInUs/1000) inside. brr::USleep() just
    //! give OS time to handle cancel request. If cancel request was sent then sleep value does not
    //! metter because it will be terminated. Call this method in StartRoutine().
    //! @return On success, Cancel() returns true; on error, it returns false and prints errno.
    //! ********************************************************************************************
    virtual bool CancelationPoint();

    //! ********************************************************************************************
    //! @brief The Exit() method terminates the calling thread and returns a value via pRetVal
    //! that (if the thread is joinable) is available to another thread in the same process that
    //! calls Join(). Call this method in StartRoutine() for exit from thread.
    //! man pthread_exit.
    //! ********************************************************************************************
    virtual void Exit(void* pRetVal);

protected: // methods
    static void* ThreadFunction(void* pContext);

protected: // members
    pthread_t     m_thread;
    volatile bool m_isRunning;
    RWLock        m_rwLockIsRunning;

}; // class ThreadBase

} // namespace brr

#endif // THREAD_BASE_H
