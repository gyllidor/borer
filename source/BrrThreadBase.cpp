//! ************************************************************************************************
//! @file   ThreadBase.h
//! @brief  abstract class wrapper for pthread. For more information man pthread*.
//! @brief  Just inherit this class, implement one method (ThreadFunction) and
//! @brief  run this method in separeted thread.
//! @author gyllidor (gyllidor@ukr.net)
//! @date   24 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
// local
#include "BrrThreadBase.h"
#include "BrrLogger.h"
#include "BrrRWLockGuard.h"
#include "BrrTime.h"

//! ************************************************************************************************
//!
//! ************************************************************************************************
void* brr::ThreadBase::ThreadFunction(void *pContext)
{
    brr::ThreadBase* pThread = static_cast < brr::ThreadBase* > (pContext);
    if (NULL == pThread)
    {
        BRR_LOGE("static_cast failed");
        return NULL;
    }

    //! @note remove this when attr will be ready.
    pThread->SetCancelState(PTHREAD_CANCEL_DISABLE);

    void* pResult = pThread->ThreadMethod();
    pThread->NotifyToStop();
    return pResult;
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
brr::ThreadBase::ThreadBase()
    : Base()
    , m_thread(0)
    , m_isRunning(false)
    , m_rwLockIsRunning()
{
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
brr::ThreadBase::ThreadBase(const std::string &threadName)
    : Base(threadName)
    , m_thread(0)
    , m_isRunning(false)
    , m_rwLockIsRunning(threadName + "RwLock")
{
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
brr::ThreadBase::~ThreadBase()
{
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
bool brr::ThreadBase::Run()
{
    {
        ReadLockGuard guard(&m_rwLockIsRunning);
        if (m_isRunning)
        {
            BRR_LOGW("Thread(%s) is already running", Base::GetClassName().c_str());
            return false;
        }
    }

    const int c_result = pthread_create(&m_thread, NULL, ThreadFunction, this);
    if (c_result)
    {
        BRR_LOGE("pthread_create() failed, %s", StrErrno(c_result).c_str() );
        return false;
    }

    WriteLockGuard guard(&m_rwLockIsRunning);
    return (m_isRunning = true);
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
bool brr::ThreadBase::IsRunning()
{
    ReadLockGuard guard(&m_rwLockIsRunning);
    return m_isRunning;
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
bool brr::ThreadBase::Join()
{
    return Join(NULL);
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
bool brr::ThreadBase::Join(void** pResult)
{
    const int c_result = pthread_join(m_thread, pResult);
    if (c_result)
    {
        BRR_LOGE("pthread_join() failed, %s", StrErrno(c_result).c_str() );
        return false;
    }

    return true;
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
bool brr::ThreadBase::Cancel()
{
    const int c_result = pthread_cancel(m_thread);
    if (c_result)
    {
        BRR_LOGE("pthread_cancel() failed, %s", StrErrno(c_result).c_str() );
        return false;
    }

    return true;
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brr::ThreadBase::NotifyToStop()
{
    WriteLockGuard guard(&m_rwLockIsRunning);
    m_isRunning = false;
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
bool brr::ThreadBase::SetCancelState(int state)
{
    const int c_result = pthread_setcancelstate(state, NULL);
    if (c_result)
    {
        BRR_LOGE("pthread_setcancelstate() failed, %s", StrErrno(c_result).c_str());
        return false;
    }

    return true;
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
bool brr::ThreadBase::SetCancelType(int type)
{
    const int c_result = pthread_setcanceltype(type, NULL);
    if (c_result)
    {
        BRR_LOGE("pthread_setcanceltype() failed, %s", StrErrno(c_result).c_str());
        return false;
    }

    return true;
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
bool brr::ThreadBase::CancelationPoint()
{
    if (false == SetCancelState(PTHREAD_CANCEL_ENABLE))
        return false;

    //! Just give OS time to handle cancel request.
    //! If cancel request was sent then sleep value does not metter because
    //! it will be terminated.
    USleep(sc_secondInUs/1000);
    if (false == SetCancelState(PTHREAD_CANCEL_DISABLE))
        return false;

    return true;
}
