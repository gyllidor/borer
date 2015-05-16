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
    //! ********************************************************************************************
    //! @brief lock pRWLock for write (call WriteLock), if pRWLock is NULL print error and
    //! @brief do nothing, if lock failed then print error.
    //! ********************************************************************************************
    WriteLockGuard(RWLock* pRWLock);

    //! ********************************************************************************************
    //! @brief lock pRWLock for write (call WriteLock), if pRWLock is NULL  print error and
    //! @brief do nothing, if lock failed then print error with c_className.
    //! ********************************************************************************************
    WriteLockGuard(RWLock* pRWLock, const std::string& c_className);

    //! ********************************************************************************************
    //! @brief unlock pRWLock (call Unlock), if pRWLock is NULL print error and do nothing,
    //! @brief if lock failed then print error and c_className if exist.
    //! ********************************************************************************************
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
    //! ********************************************************************************************
    //! @brief lock pRWLock for read (call ReadLock), if pRWLock is NULL print error and do nothing,
    //! @brief if lock failed then print error.
    //! ********************************************************************************************
    ReadLockGuard(RWLock* pRWLock);

    //! ********************************************************************************************
    //! @brief lock pRWLock for read (call ReadLock), if pRWLock is NULL print error and do nothing,
    //! @brief if lock failed then print error with c_className.
    //! ********************************************************************************************
    ReadLockGuard(RWLock* pRWLock, const std::string& c_className);

    //! ********************************************************************************************
    //! @brief unlock pRWLock (call Unlock), if pRWLock is NULL print error and do nothing,
    //! @brief if lock failed then print error and c_className if exist.
    //! ********************************************************************************************
    ~ReadLockGuard();

private: // members
    RWLock* m_pRWLock;

}; // class ReadLockGuard

} // namespace brr

#endif // RW_LOCK_GUARD_H
