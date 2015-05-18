//! ************************************************************************************************
//! @file   ThreadBase.h
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
    //! ********************************************************************************************
    ThreadBase();

    //! ********************************************************************************************
    //! @brief contructor.
    //! @param threadName - set thread name for object.
    //! ********************************************************************************************
    ThreadBase(const std::string& threadName);

    //! ********************************************************************************************
    //! @brief destructor - empty body.
    //! ********************************************************************************************
    virtual ~ThreadBase();

    //! ********************************************************************************************
    //! @brief  create thread and run void* ThreadMethod(). By default cancel state is
    //! @brief  PTHREAD_CANCEL_DISABLE. If pthread_cancel_state(PTHREAD_CANCEL_DISABLE) failed
    //! @brief  then warning message will be printed.
    //! @brief  The new thread terminates in one of the following ways:
    //! @brief  1) It calls pthread_exit(), specifying an exit status value that is available to
    //! @brief  another thread in the same process that calls pthread_join(3).
    //! @brief  2) It returns from ThreadMethod(). This is equivalent to calling pthread_exit()
    //! @brief  with the value supplied in the return statement.
    //! @brief  3) It is canceled Cancel() (see pthread_cancel()).
    //! @brief  4) Any of the threads in the process calls exit(), or the main thread performs a
    //! @brief  return from main(). This causes the termination of all threads in the process.
    //! @brief  for more information man pthread_create().
    //! @return false if thread is already running or pthread_create() failed (also errno printed)
    //!         otherwise true.
    //! ********************************************************************************************
    virtual bool Run();

    //! ********************************************************************************************
    //! @brief  check state of the thread - running or not.
    //! @return true if thread is running otherwise false.
    //! ********************************************************************************************
    virtual bool IsRunning();

    //! ********************************************************************************************
    //! @brief  Join() - join with a terminated thread. The Join() function waits for the thread to
    //! @brief  terminate. If that thread has already terminated, then Join() returns immediately.
    //! @brief  the thread must be joinable.
    //! @brief  For more information man pthread_join.
    //! @return On success, Join() returns true; on error, it returns false and prints errno.
    //! ********************************************************************************************
    virtual bool Join();

    //! ********************************************************************************************
    //! @brief  Similar to Join() but if retval is not NULL, then Join() copies the exit status of
    //! @brief  the target thread (i.e., the value that the target thread supplied to
    //! @brief  pthread_exit()) into the location pointed to by *pResult. If the target thread was
    //! @brief  canceled, then PTHREAD_CANCELED is placed in *pResult. If multiple threads
    //! @brief  simultaneously try to join with the same thread, the results are undefined.
    //! @brief  If the thread calling Join() is canceled, then the target thread will remain
    //! @brief  joinable (i.e., it will not be detached).
    //! @brief  For more information man pthread_join.
    //! @return On success, Join() returns true; on error, it returns false and prints errno.
    //! ********************************************************************************************
    virtual bool Join(void** pResult);

    //! @todo add to run SetCancelType (implement this)

    //! ********************************************************************************************
    //! @brief  The Cancel() function sends a cancellation request to the thread m_thread.
    //! @brief  Whether and when the target thread reacts to the cancellation request depends on
    //! @brief  two attributes that are under the control of that thread: its cancelability state
    //! @brief  and type.
    //! @brief  A thread's cancelability state, determined by SetCancelState(3), can be enabled
    //! @brief  or disabled (NOTE/ATTENTION: the default for new threads for ThreadBase
    //! @brief  notwithstanding pthread).
    //! @brief  If a thread has disabled cancellation,then a cancellation request remains queued
    //! @brief  until the thread enables cancellation.
    //! @brief  If a thread has enabled cancellation, then its cancelability type determines when
    //! @brief  cancellation occurs.
    //! @brief  A thread's cancellation type, determined by SetCancelType()
    //! @brief  (man pthread_setcanceltype), may be either asynchronous or deferred (the default for
    //! @brief  new threads). Asynchronous cancelability means that the thread can be canceled
    //! @brief  at any time (usually immediately, but the system does not guarantee this).
    //! @brief  Deferred cancelability means that cancellation will be delayed until the thread next
    //! @brief  calls a function that is a cancellation point.
    //! @brief  For more information man pthread_cancel.
    //! @return On success, Cancel() returns true; on error, it returns false and prints errno.
    //! ********************************************************************************************
    virtual bool Cancel();

    //! ********************************************************************************************
    //! @brief NotifyToStop() - just set m_isRunning to false (method is thread safe).
    //! @brief In case IsRunning() using in ThreadMethod() to check should thread to stop
    //! @brief or not - this method (NotifyToStop()) can be used for notifing thread to stop.
    //! ********************************************************************************************
    virtual void NotifyToStop();

protected: // methods
    //! ********************************************************************************************
    //! @brief  Implement this method in derived class. Call Run() and ThreadMethod will work in
    //! @brief  separated thread.
    //! @return returned data(must be on the heap) you can get from Join(**pResult).
    //! ********************************************************************************************
    virtual void* ThreadMethod() = 0;

    //! ********************************************************************************************
    //! @brief  The SetCancelState() sets the cancelability state of the calling thread to the
    //! @brief  value given in state. The state argument must have one of the following values:
    //! @brief  1) PTHREAD_CANCEL_ENABLE - the thread is cancelable.
    //! @brief  2) PTHREAD_CANCEL_DISABLE - the thread is not cancelable. If a cancellation request
    //! @brief  is received, it is blocked until cancelability is enabled. This is the default
    //! @brief  cancelability state in all new threads (for ThreadBase notwithstanding pthread).
    //! @return On success, Cancel() returns true; on error, it returns false and prints errno.
    //! ********************************************************************************************
    virtual bool SetCancelState(int state);

    //! ********************************************************************************************
    //! @brief  Call SetCancelState(PTHREAD_CANCEL_ENABLE), USleep(second/1000) then
    //! @brief  SetCancelState(PTHREAD_CANCEL_DISABLE) inside. If a cancellation request
    //! @brief  was sent(Cancel()) before CancelationPoint() then in point of CancelationPoint()
    //! @brief  thread will be canceled.
    //! @brief  ATTENTION this method use brr::USleep(brr::sc_sc_secondInUs/1000) inside.
    //! @brief  brr::USleep() Just give OS time to handle cancel request.
    //! @brief  If cancel request was sent then sleep value does not metter because
    //! @brief  it will be terminated.
    //! @return On success, Cancel() returns true; on error, it returns false and prints errno.
    //! ********************************************************************************************
    virtual bool CancelationPoint();

protected: // methods
    static void* ThreadFunction(void* pContext);

protected: // members
    pthread_t     m_thread;
    volatile bool m_isRunning;
    RWLock        m_rwLockIsRunning;

}; // class ThreadBase

} // namespace brr

#endif // THREAD_BASE_H
