//! ************************************************************************************************
//! @file   TestThreadBase.h
//! @brief  unit tests for ThreadBase
//! @author gyllidor (gyllidor@ukr.net)
//! @date   24 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
// local
#include "TestThreadBase.h"

// project
#include "BrrThreadBase.h"
#include "BrrLogger.h"
#include "BrrTypes.h"
#include "BrrMemory.h"

// system
#include "string.h"
#include "unistd.h"

//! ************************************************************************************************
//! @brief constants
//! ************************************************************************************************
static const std::string sc_retVal( "test_string" );

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

}; // class TestRun

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::TestThreadBase::Run()
{
    TestRun();
    TestJoinRetVal();
    TestNotifyToStop();
    TestCancel();
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::TestThreadBase::TestRun()
{
    TestSample thread(false, 1);
    BRR_ASSERT(thread.Run());
    BRR_ASSERT(thread.IsRunning());
    BRR_ASSERT(thread.Join());
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::TestThreadBase::TestJoinRetVal()
{
    char* pRetVal = NULL;
    TestSample thread(true, 0);
    BRR_ASSERT(thread.Run());
    BRR_ASSERT(thread.Join((void**)&pRetVal));
    BRR_ASSERT(sc_retVal == pRetVal);
    BRR_DELETE_ARRAY pRetVal;
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::TestThreadBase::TestNotifyToStop()
{

}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::TestThreadBase::TestCancel()
{

}