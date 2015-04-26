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
#include "ThreadBase.h"
#include "BrrLogger.h"
#include "RWLockGuard.h"

//! ************************************************************************************************
//!
//! ************************************************************************************************
void *brr::ThreadBase::ThreadFunction(void *pContext)
{
    brr::ThreadBase* pThread = static_cast < brr::ThreadBase* > (pContext);
    if ( NULL == pThread )
    {
        BRR_LOGE("static_cast failed");
        return NULL;
    }

    void* pResult = pThread->ThreadMethod();
    pThread->NotifyToStop();
    return pResult;
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
brr::ThreadBase::ThreadBase()
    : BrrBase()
    , m_thread(0)
    , m_isRunning(false)
    , m_rwLock()
{
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
brr::ThreadBase::ThreadBase(const std::string &threadName)
    : BrrBase(threadName)
    , m_thread(0)
    , m_isRunning(false)
    , m_rwLock(threadName + "RwLock")
{
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
bool brr::ThreadBase::Run()
{
    if (false == SetCancelState(PTHREAD_CANCEL_DISABLE))
        BRR_LOGW( "Run(): failed to set state PTHREAD_CANCEL_DISABLE" );

    const int c_result = pthread_create(&m_thread, NULL, ThreadFunction, this);
    if (c_result)
    {
        BRR_LOGE("pthread_create() failed, %s", StrErrno(c_result).c_str() );
        return false;
    }

    WriteLockGuard guard(&m_rwLock);
    return (m_isRunning = true);
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
bool brr::ThreadBase::IsRunning()
{
    ReadLockGuard guard(&m_rwLock);
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
bool brr::ThreadBase::NotifyToStop()
{
    WriteLockGuard guard(&m_rwLock);
    return (m_isRunning = false);
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
bool brr::ThreadBase::SetCancelState(int type)
{
    const int c_result = pthread_setcancelstate(type, NULL);
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
bool brr::ThreadBase::CancelationPoint()
{
    if (false == SetCancelState(PTHREAD_CANCEL_ENABLE) ||
        false == SetCancelState(PTHREAD_CANCEL_DISABLE))
        return false;

    return true;
}
