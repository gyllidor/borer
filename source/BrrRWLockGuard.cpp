//! ************************************************************************************************
//! @file   RWLockGuard.cpp
//! @brief  Guard for class RWLock. In constructor RWLock will be locked, in desctructor unlocked
//! @author gyllidor (gyllidor@ukr.net)
//! @date   26 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
// local
#include "BrrRWLockGuard.h"
#include "BrrRWLock.h"
#include "BrrLogger.h"

//! ************************************************************************************************
//! @file class WriteLockGuard
//! ************************************************************************************************
brr::WriteLockGuard::WriteLockGuard(RWLock* pRWLock)
    : BrrBase()
    , m_pRWLock(pRWLock)
{
    if (NULL == pRWLock)
        BRR_LOGE("NULL == pRWLock");
    else if (false == m_pRWLock->WriteLock())
        BRR_LOGE("WriteLock() failed");
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
brr::WriteLockGuard::WriteLockGuard(RWLock *pRWLock, const std::string &c_className)
    : BrrBase(c_className)
    , m_pRWLock(pRWLock)
{
    if (NULL == pRWLock)
        BRR_LOGE("NULL == pRWLock");
    else if (false == m_pRWLock->WriteLock())
        BRR_LOGE("WriteLock(%s) failed", BrrBase::GetClassName().c_str());
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
brr::WriteLockGuard::~WriteLockGuard()
{
    if (NULL == m_pRWLock)
        BRR_LOGE("NULL == m_pRWLock");
    else if (false == m_pRWLock->Unlock())
    {
        const std::string c_className(BrrBase::GetClassName());
        BRR_LOGE("Unlock(%s) failed", ( c_className == "<empty>" ) ? "" : c_className.c_str());
    }
}

//! ************************************************************************************************
//! @file class ReadLockGuard
//! ************************************************************************************************
brr::ReadLockGuard::ReadLockGuard(RWLock* pRWLock)
    : BrrBase()
    , m_pRWLock(pRWLock)
{
    if (NULL == pRWLock)
        BRR_LOGE("NULL == pRWLock");
    else if (false == m_pRWLock->ReadLock())
        BRR_LOGE("WriteLock() failed");
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
brr::ReadLockGuard::ReadLockGuard(RWLock *pRWLock, const std::string &c_className)
    : BrrBase(c_className)
    , m_pRWLock(pRWLock)
{
    if (NULL == pRWLock)
        BRR_LOGE("NULL == pRWLock");
    else if (false == m_pRWLock->ReadLock())
        BRR_LOGE("WriteLock(%s) failed", BrrBase::GetClassName().c_str());
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
brr::ReadLockGuard::~ReadLockGuard()
{
    if (NULL == m_pRWLock)
        BRR_LOGE("NULL == m_pRWLock");
    else if (false == m_pRWLock->Unlock())
    {
        const std::string c_className(BrrBase::GetClassName());
        BRR_LOGE("Unlock(%s) failed", ( c_className == "<empty>" ) ? "" : c_className.c_str());
    }
}
