//! ************************************************************************************************
//! @file   TestRWLock.cpp
//! @brief  unit tests for BrrRWLock
//! @author gyllidor (gyllidor@ukr.net)
//! @date   16 May 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
// local
#include "TestRWLock.h"

// project
#include "BrrRWLock.h"
#include "BrrThreadBase.h"
#include "BrrTime.h"

//! ************************************************************************************************
//!
//! ************************************************************************************************
struct ThreadWriteLock : public brr::ThreadBase
{
    ThreadWriteLock(brr::RWLock* pRWLock) : m_pRWLock(pRWLock) {}

    void* StartRoutine()
    {
        m_pRWLock->WriteLock();
        brr::Sleep(brr::sc_second);
        m_pRWLock->Unlock();
        return NULL;
    }

private: // members
    brr::RWLock* m_pRWLock;

}; // class ThreadWriteLock

//! ************************************************************************************************
//!
//! ************************************************************************************************
struct ThreadReadLock : public brr::ThreadBase
{
    ThreadReadLock(brr::RWLock* pRWLock) : m_pRWLock(pRWLock) {}

    void* StartRoutine()
    {
        m_pRWLock->ReadLock();
        brr::Sleep(brr::sc_second);
        m_pRWLock->Unlock();
        return NULL;
    }

private: // members
    brr::RWLock* m_pRWLock;

}; // class ThreadReadLock

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::TestRWLock::Run()
{
    BRRUT_ADD_TEST(TestWriteLockOnLockedForWrite);
    BRRUT_ADD_TEST(TestTryWriteLockOnLockedForWrite);
    BRRUT_ADD_TEST(TestReadLockOnLockedForWrite);
    BRRUT_ADD_TEST(TestTryReadLockOnLockedForWrite);
    BRRUT_ADD_TEST(TestWriteLockOnLockedForRead);
    BRRUT_ADD_TEST(TestTryWriteLockOnLockedForRead);
    BRRUT_ADD_TEST(TestReadLockOnLockedForRead);
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::TestRWLock::TestWriteLockOnLockedForWrite()
{
    brr::RWLock     rwLock;
    ThreadWriteLock thread(&rwLock);
    thread.Run();

    // to be sure that thread initialized and started
    brr::USleep(brr::sc_secondInUs/10);

    const time_t c_startTime = brr::GetTime();
    rwLock.WriteLock();
    const time_t c_finishTime = brr::GetTime();

    BRRUT_ASSERT(1 == (c_finishTime - c_startTime));
    thread.Join();
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::TestRWLock::TestTryWriteLockOnLockedForWrite()
{
    brr::RWLock     rwLock;
    ThreadWriteLock thread(&rwLock);
    thread.Run();

    // to be sure that thread initialized and started
    brr::USleep(brr::sc_secondInUs/10);

    const time_t c_startTime = brr::GetTime();
    rwLock.TryWriteLock();
    const time_t c_finishTime = brr::GetTime();

    BRRUT_ASSERT(0 == (c_finishTime - c_startTime));
    thread.Join();
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::TestRWLock::TestReadLockOnLockedForWrite()
{
    brr::RWLock     rwLock;
    ThreadWriteLock thread(&rwLock);
    thread.Run();

    // to be sure that thread initialized and started
    brr::USleep(brr::sc_secondInUs/10);

    const time_t c_startTime = brr::GetTime();
    rwLock.ReadLock();
    const time_t c_finishTime = brr::GetTime();

    BRRUT_ASSERT(1 == (c_finishTime - c_startTime));
    thread.Join();
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::TestRWLock::TestTryReadLockOnLockedForWrite()
{
    brr::RWLock     rwLock;
    ThreadWriteLock thread(&rwLock);
    thread.Run();

    // to be sure that thread initialized and started
    brr::USleep(brr::sc_secondInUs/10);

    const time_t c_startTime = brr::GetTime();
    rwLock.TryReadLock();
    const time_t c_finishTime = brr::GetTime();

    BRRUT_ASSERT(0 == (c_finishTime - c_startTime));
    thread.Join();
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::TestRWLock::TestWriteLockOnLockedForRead()
{
    brr::RWLock    rwLock;
    ThreadReadLock thread(&rwLock);
    thread.Run();

    // to be sure that thread initialized and started
    brr::USleep(brr::sc_secondInUs/10);

    const time_t c_startTime = brr::GetTime();
    rwLock.WriteLock();
    const time_t c_finishTime = brr::GetTime();

    BRRUT_ASSERT(1 == (c_finishTime - c_startTime));
    thread.Join();
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::TestRWLock::TestTryWriteLockOnLockedForRead()
{
    brr::RWLock    rwLock;
    ThreadReadLock thread(&rwLock);
    thread.Run();

    // to be sure that thread initialized and started
    brr::USleep(brr::sc_secondInUs/10);

    const time_t c_startTime = brr::GetTime();
    rwLock.TryWriteLock();
    const time_t c_finishTime = brr::GetTime();

    BRRUT_ASSERT(0 == (c_finishTime - c_startTime));
    thread.Join();
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::TestRWLock::TestReadLockOnLockedForRead()
{
    brr::RWLock    rwLock;
    ThreadReadLock thread(&rwLock);
    thread.Run();

    // to be sure that thread initialized and started
    brr::USleep(brr::sc_secondInUs/10);

    const time_t c_startTime = brr::GetTime();
    rwLock.ReadLock();
    const time_t c_finishTime = brr::GetTime();

    BRRUT_ASSERT(0 == (c_finishTime - c_startTime));
    thread.Join();
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::TestRWLock::TestTryReadLockOnLockedForRead()
{
    brr::RWLock    rwLock;
    ThreadReadLock thread(&rwLock);
    thread.Run();

    // to be sure that thread initialized and started
    brr::USleep(brr::sc_secondInUs/10);

    const time_t c_startTime = brr::GetTime();
    rwLock.TryReadLock();
    const time_t c_finishTime = brr::GetTime();

    BRRUT_ASSERT(0 == (c_finishTime - c_startTime));
    thread.Join();
}
