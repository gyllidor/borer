//! ************************************************************************************************
//! @file   RWLock.h
//! @brief  wraper for pthread_rwlock_t
//! @author gyllidor (gyllidor@ukr.net)
//! @date   26 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
#ifndef RW_LOCK_H
#define RW_LOCK_H

// local
#include "BrrBase.h"

// system
#include <pthread.h>

namespace brr
{

class RWLock : public Base
{
private: // blocked methods
    RWLock( const RWLock& rwLock );
    const RWLock& operator=( const RWLock& rwLock );

public: // methods
    RWLock();
    RWLock( const std::string& c_className );
    ~RWLock();

    bool ReadLock();
    bool TryReadLock();
    bool WriteLock();
    bool TryWriteLock();
    bool Unlock();

private: // members
    pthread_rwlock_t m_rwLock;

}; // class RWLock

} // namespace brr

#endif // RW_LOCK_H
