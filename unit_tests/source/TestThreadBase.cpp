//! ************************************************************************************************
//! @file   TestThreadBase.h
//! @brief  unit tests for ThreadBase
//! @author gyllidor (gyllidor@ukr.net)
//! @date   24 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
// local
#include "TestThreadBase.h"
#include "BrrTime.h"

// project
#include "BrrThreadBase.h"
#include "BrrTypes.h"
#include "BrrMemory.h"

// system
#include <string.h>
#include <unistd.h>

//! ************************************************************************************************
//! @brief constants
//! ************************************************************************************************
static const std::string sc_retVal     = "test_string";
static const time_t      sc_timeFailed = -1;

//! ************************************************************************************************
//! @brief class ThreadBase sample
//! ************************************************************************************************
struct TestSample : public brr::ThreadBase
{
    TestSample()
        : m_shouldReturnVal(false)
        , m_timeOut(0)
    {}

    TestSample(bool shouldReturnVal, uint timeOut)
        : m_shouldReturnVal(shouldReturnVal)
        , m_timeOut(timeOut)
    {}

    void* ThreadMethod()
    {
        sleep(m_timeOut);

        if (m_shouldReturnVal)
        {
            const int c_size = sc_retVal.length() + 1;
            char* pRetVal = BRR_NEW_NOTHROW_ARRAY char[c_size];
            memset(pRetVal, 0, c_size);
            memcpy(pRetVal, sc_retVal.c_str(), sc_retVal.length());
            return pRetVal;
        }

        return NULL;
    }

private:
    volatile bool m_shouldReturnVal;
    volatile uint m_timeOut;

}; // class TestSample

//! ************************************************************************************************
//! @brief class ThreadBase sample 2
//! ************************************************************************************************
struct TestSample2 : public brr::ThreadBase
{
    void* ThreadMethod()
    {
        uint sleepCounter = 20;
        while (ThreadBase::IsRunning() && sleepCounter--)
        {
            brr::USleep(brr::sc_secondInUs/5);
            ThreadBase::CancelationPoint();
        }

        return NULL;
    }

}; // struct TestSample2

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::TestThreadBase::Run()
{
    BRRUT_ADD_TEST(TestRun);
    BRRUT_ADD_TEST(TestJoinRetVal);
    BRRUT_ADD_TEST(TestNotifyToStop);
    BRRUT_ADD_TEST(TestCancel);
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::TestThreadBase::TestRun()
{
    TestSample thread(false, 1);
    BRRUT_ASSERT(thread.Run());
    BRRUT_ASSERT(thread.IsRunning());
    BRRUT_ASSERT(thread.Join());
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::TestThreadBase::TestJoinRetVal()
{
    char* pRetVal = NULL;
    TestSample thread(true, 0);
    BRRUT_ASSERT(thread.Run());
    BRRUT_ASSERT(thread.Join((void**)&pRetVal));
    BRRUT_ASSERT(sc_retVal == pRetVal);
    BRR_DELETE_ARRAY pRetVal;
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::TestThreadBase::TestNotifyToStop()
{
    TestSample2 thread;
    BRRUT_ASSERT(thread.Run());

    const time_t startTime = brr::GetTime();
    BRRUT_ASSERT(startTime != sc_timeFailed);

    thread.NotifyToStop();
    BRRUT_ASSERT(thread.Join());
    const time_t finishTime = brr::GetTime();
    BRRUT_ASSERT(finishTime != sc_timeFailed)
    BRRUT_ASSERT((finishTime - startTime) <=1 );
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::TestThreadBase::TestCancel()
{
    TestSample2 thread;
    BRRUT_ASSERT(thread.Run());

    const time_t startTime = brr::GetTime();
    BRRUT_ASSERT(startTime != sc_timeFailed);
    BRRUT_ASSERT(thread.Cancel());
    BRRUT_ASSERT(thread.Join());
    const time_t finishTime = brr::GetTime();
    BRRUT_ASSERT(finishTime != sc_timeFailed);
    BRRUT_ASSERT((finishTime - startTime) <= 1);
}
