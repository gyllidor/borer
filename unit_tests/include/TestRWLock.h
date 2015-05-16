//! ************************************************************************************************
//! @file   TestRWLock.h
//! @brief  unit tests for BrrRWLock
//! @author gyllidor (gyllidor@ukr.net)
//! @date   16 May 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
#ifndef TEST_RW_LOCK_H
#define TEST_RW_LOCK_H

// local
#include "BrrTestBase.h"

namespace brrut
{

class TestRWLock : public TestBase
{
public: // methods
    void Run();

private: // methods
    void TestWriteLockOnLockedForWrite();
    void TestTryWriteLockOnLockedForWrite();
    void TestReadLockOnLockedForWrite();
    void TestTryReadLockOnLockedForWrite();

    void TestWriteLockOnLockedForRead();
    void TestTryWriteLockOnLockedForRead();
    void TestReadLockOnLockedForRead();
    void TestTryReadLockOnLockedForRead();

}; // class TestRWLock

} // namespace brrut

#endif // TEST_RW_LOCK_H
