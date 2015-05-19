//! ************************************************************************************************
//! @file   TestRWLockGuard.h
//! @brief  unit tests for BrrRWLockGuard
//! @author gyllidor (gyllidor@ukr.net)
//! @date   19 May 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
#ifndef TEST_RWLOCK_GUARD_H
#define TEST_RWLOCK_GUARD_H

// local
#include "BrrTestBase.h"

namespace brrut {

class TestRWLockGuard : public TestBase
{
public: // methods
    void Run();

private: // methods
    void TestWriteLockGuard();
    void TestReadLockGuard();

}; // class TestRWLockGuard

}

#endif // TEST_RWLOCK_GUARD_H
