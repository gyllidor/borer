//! ************************************************************************************************
//! @file   TestRWLockGuard.cpp
//! @brief  unit tests for BrrRWLockGuard
//! @author gyllidor (gyllidor@ukr.net)
//! @date   19 May 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
// local
#include "TestRWLockGuard.h"

// project
#include "BrrRWLockGuard.h"
#include "BrrRWLock.h"

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::TestRWLockGuard::Run()
{
    BRRUT_ADD_TEST(TestWriteLockGuard);
    BRRUT_ADD_TEST(TestReadLockGuard);
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::TestRWLockGuard::TestWriteLockGuard()
{
    brr::RWLock rwLock;
    {
        brr::ReadLockGuard guard(&rwLock);
        BRRUT_ASSERT(rwLock.TryWriteLock() == false);
    }

    BRRUT_ASSERT(rwLock.WriteLock() == true);
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::TestRWLockGuard::TestReadLockGuard()
{
    brr::RWLock rwLock;
    {
        brr::WriteLockGuard guard(&rwLock);
        BRRUT_ASSERT(rwLock.TryReadLock() == false);
    }

    BRRUT_ASSERT(rwLock.ReadLock() == true);
}
