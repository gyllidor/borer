//! ************************************************************************************************
//! @file   RWLock.cpp
//! @brief  wraper for pthread_rwlock_t
//! @author gyllidor (gyllidor@ukr.net)
//! @date   26 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
// local
#include "RWLock.h"
#include "BrrLogger.h"

//! ************************************************************************************************
//!
//! ************************************************************************************************
brr::RWLock::RWLock()
    : BrrBase()
    , m_rwLock()
{
    const int c_result = pthread_rwlock_init(&m_rwLock, NULL);
    if ( c_result )
        BRR_LOGE("pthread_rwlock_init() failed");
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
brr::RWLock::RWLock(const std::string &c_className)
    : BrrBase(c_className)
    , m_rwLock()
{
    const int c_result = pthread_rwlock_init(&m_rwLock, NULL);
    if ( c_result )
        BRR_LOGE("pthread_rwlock_init() failed");
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
brr::RWLock::~RWLock()
{
    const int c_result = pthread_rwlock_destroy(&m_rwLock);
    if ( c_result )
        BRR_LOGE("pthread_rwlock_destroy() failed");
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
bool brr::RWLock::ReadLock()
{
    const int c_result = pthread_rwlock_rdlock(&m_rwLock);
    if ( c_result )
    {
        BRR_LOGE("pthread_rwlock_rdlock() failed, %s", ErrnoDescription(c_result).c_str());
        return false;
    }

    return true;
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
bool brr::RWLock::TryReadLock()
{
    const int c_result = pthread_rwlock_tryrdlock(&m_rwLock);
    if ( c_result )
    {
        BRR_LOGE("pthread_rwlock_tryrdlock() failed, %s", ErrnoDescription(c_result).c_str());
        return false;
    }

    return true;
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
bool brr::RWLock::WriteLock()
{
    const int c_result = pthread_rwlock_wrlock(&m_rwLock);
    if ( c_result )
    {
        BRR_LOGE("pthread_rwlock_wrlock() failed, %s", ErrnoDescription(c_result).c_str());
        return false;
    }

    return true;
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
bool brr::RWLock::TryWriteLock()
{
    const int c_result = pthread_rwlock_trywrlock(&m_rwLock);
    if ( c_result )
    {
        BRR_LOGE("pthread_rwlock_trywrlock() failed, %s", ErrnoDescription(c_result).c_str());
        return false;
    }

    return true;
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
bool brr::RWLock::Unlock()
{
    const int c_result = pthread_rwlock_unlock(&m_rwLock);
    if ( c_result )
    {
        BRR_LOGE("pthread_rwlock_unlock() failed, %s", ErrnoDescription(c_result).c_str());
        return false;
    }

    return true;
}
