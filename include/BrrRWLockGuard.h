//! ************************************************************************************************
//! @file   RWLockGuard.h
//! @brief  Guard for class RWLock. In constructor RWLock will be locked, in desctructor unlocked
//! @author gyllidor (gyllidor@ukr.net)
//! @date   26 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
#ifndef RW_LOCK_GUARD_H
#define RW_LOCK_GUARD_H

// local
#include "BrrBase.h"

namespace brr
{
class RWLock;

//! ************************************************************************************************
//! @file Lock RWLock for write
//! ************************************************************************************************
class WriteLockGuard : public Base
{
private: // blocked methods
    WriteLockGuard(const WriteLockGuard& c_guard);
    const WriteLockGuard& operator=(const WriteLockGuard& c_guard);

public: // methods
    WriteLockGuard(RWLock* pRWLock);
    WriteLockGuard(RWLock* pRWLock, const std::string& c_className);
    ~WriteLockGuard();

private: // members
    RWLock* m_pRWLock;

}; // class WriteLockGuard

//! ************************************************************************************************
//! @file Lock RWLock for read
//! ************************************************************************************************
class ReadLockGuard : public Base
{
private: // blocked methods
    ReadLockGuard(const ReadLockGuard& c_guard);
    const ReadLockGuard& operator=(const ReadLockGuard& c_guard);

public: // methods
    ReadLockGuard(RWLock* pRWLock);
    ReadLockGuard(RWLock* pRWLock, const std::string& c_className);
    ~ReadLockGuard();

private: // members
    RWLock* m_pRWLock;

}; // class ReadLockGuard

} // namespace brr

#endif // RW_LOCK_GUARD_H
