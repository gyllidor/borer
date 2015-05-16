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

//! ************************************************************************************************
//! @brief wrapper for pthread_rwlock.
//! @brief object not copyable.
//! ************************************************************************************************
class RWLock : public Base
{
private: // blocked methods
    RWLock( const RWLock& rwLock );
    const RWLock& operator=( const RWLock& rwLock );

public: // methods
    RWLock();
    RWLock( const std::string& c_className );
    ~RWLock();

    //! ********************************************************************************************
    //! @brief  the ReadLock() function shall apply a read lock to the read-write lock
    //! @brief  referenced by rwlock. The calling thread acquires the read lock if a writer does not
    //! @brief  hold the lock and there are no writers blocked on the lock.
    //! @brief  for more information look man pthread_rwlock_rdlock.
    //! @return true if success otherwise false and print errno.
    //! ********************************************************************************************
    bool ReadLock();

    //! ********************************************************************************************
    //! @brief  The TryReadLock() function shall apply a read lock as in the ReadLock() function,
    //! @brief  with the exception that the function shall fail if the equivalent ReadLock() call
    //! @brief  would have blocked the calling thread. In no case shall the TryReadLock() function
    //! @brief  ever block; it always either acquires the lock or fails and returns immediately.
    //! @brief  for more information look man pthread_rwlock_tryrdlock.
    //! @return true if success otherwise false immediately.
    //! ********************************************************************************************
    bool TryReadLock();

    //! ********************************************************************************************
    //! @brief  The WriteLock() function shall apply a write lock to the read-write
    //! @brief  lock referenced by rwlock. The calling thread acquires the write lock if no other
    //! @brief  thread (reader or writer) holds the read-write lock rwlock. Otherwise, the thread
    //! @brief  shall block until it can acquire the lock. The calling thread may deadlock if at the
    //! @brief  time the call is made it holds the read-write lock (whether a read or write lock).
    //! @brief  for more information look man pthread_rwlock_wrlock.
    //! @return true if success otherwise false and print errno.
    //! ********************************************************************************************
    bool WriteLock();

    //! ********************************************************************************************
    //! @brief  The  TryWriteLock() function shall apply a write lock like the WriteLock() function,
    //! @brief  with the exception that the function shall fail if any thread currently holds
    //! @brief  rwlock (for reading or writing).
    //! @brief  for more information look man pthread_rwlock_trywrlock.
    //! @return true if success otherwise false immediately.
    //! ********************************************************************************************
    bool TryWriteLock();

    //! ********************************************************************************************
    //! @brief  The Unlock() function shall release a lock held on the read-write lock object
    //! @brief  referenced by rwlock. Results are undefined if the read-write lock rwlock is not
    //! @brief  held by the calling thread.
    //! @brief  for more information look man pthread_rwlock_unlock.
    //! @return true if success otherwise false and print errno.
    //! ********************************************************************************************
    bool Unlock();

private: // members
    pthread_rwlock_t m_rwLock;

}; // class RWLock

} // namespace brr

#endif // RW_LOCK_H
