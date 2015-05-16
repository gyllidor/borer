//! ************************************************************************************************
//! @file   BrrTestBase.h
//! @brief  simple base class for unit tests; Just implement tests what you need and call them
//! @brief  in method Run;
//! @author gyllidor (gyllidor@ukr.net)
//! @date   26 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
#ifndef BRR_TEST_BASE_H
#define BRR_TEST_BASE_H

// project
#include "BrrLogger.h"
#include "BrrMemory.h"

// system
#include <vector>

//! ************************************************************************************************
//! @brief namespace for unit test, brrut(borer unit test).
//! ************************************************************************************************
namespace brrut
{

//! ************************************************************************************************
//! @brief counters for test, number of all, failed and success tests.
//! ************************************************************************************************
class UnitTestCounter
{
private: // blocked methods
    UnitTestCounter() : m_allTest(0), m_failedTest(0) {}
    UnitTestCounter(const UnitTestCounter& rhs);
    UnitTestCounter& operator=(const UnitTestCounter& rhs);

public: // methods
    static UnitTestCounter& GetInstance() { static UnitTestCounter tCounter; return tCounter; }
    int  IncreaseAllTest()     { return ++m_allTest; }
    int  IncreaseFailedTest()  { ++m_allTest; return ++m_failedTest; }
    void PrintResult()
    {
        BRR_LOGI("### Test results: all %d | success %d | failed %d ###",
                 m_allTest, m_allTest-m_failedTest, m_failedTest );
    }

private: // members
    int m_allTest;
    int m_failedTest;

}; // TestCounter

//! ************************************************************************************************
//! @brief base abstract class for unit tests.
//! ************************************************************************************************
class TestBase
{
private: // blocked methods
    TestBase( const TestBase& rhs );
    const TestBase& operator=( const TestBase& rhs );

public: // methods
    TestBase() {}
    virtual ~TestBase() {}

    virtual void Run() = 0;

}; // class TestBase

//! ************************************************************************************************
//! @brief run pool of tests and print results.
//! ************************************************************************************************
class TestRunner : public TestBase
{
public: // methods
    TestRunner() : m_poolTests() {}
    ~TestRunner()
    {
        std::vector <TestBase*>::iterator itTest = m_poolTests.begin();
        for (; itTest != m_poolTests.end(); ++itTest)
            BRR_DELETE (*itTest);
    }

    void Run()
    {
        std::vector <brrut::TestBase*>::iterator itTest = m_poolTests.begin();
        for (; itTest != m_poolTests.end(); ++itTest)
            (*itTest)->Run();

        UnitTestCounter::GetInstance().PrintResult();
    }

    void AddTest( TestBase* pTest ) { m_poolTests.push_back(pTest); }

private: // members
    std::vector <TestBase*> m_poolTests;

}; // class TestRunner

//! ************************************************************************************************
//! @brief print name of test and then run test.
//! ************************************************************************************************
#define BRRUT_ADD_TEST(TEST_NAME) \
do { \
    BRR_LOGI("### start " #TEST_NAME " ###"); \
    TEST_NAME(); \
} while(0);

//! ************************************************************************************************
//! @brief check EXPRESSION and print message success or failed.
//! ************************************************************************************************
#define BRRUT_ASSERT(EXPRESSION) \
do { \
    if (EXPRESSION) \
    { \
        brrut::UnitTestCounter::GetInstance().IncreaseAllTest(); \
        BRR_LOGI("success ("#EXPRESSION")"); \
    } \
    else \
    { \
        brrut::UnitTestCounter::GetInstance().IncreaseFailedTest(); \
        BRR_LOGE("failed ("#EXPRESSION")"); \
    } \
} while(0);

//! ************************************************************************************************
//! @brief check EXPRESSION and print message success or failed and MSG.
//! ************************************************************************************************
#define BRRUT_ASSERT_MSG(EXPRESSION, MSG) \
do { \
    if (EXPRESSION) \
    { \
        brrut::UnitTestCounter::GetInstance().IncreaseAllTest(); \
        BRR_LOGI("success ("#EXPRESSION") %s", MSG); \
    } \
    else \
    { \
        brrut::UnitTestCounter::GetInstance().IncreaseFailedTest(); \
        BRR_LOGE("failed ("#EXPRESSION") %s", MSG); \
    } \
} while(0);

//! ************************************************************************************************
//! @brief check EXPRESSION and print message success or failed. If failed then exit from app.
//! ************************************************************************************************
#define BRRUT_ASSERT_EXIT(EXPRESSION) \
do { \
    if (EXPRESSION) \
    { \
        brrut::UnitTestCounter::GetInstance().IncreaseAllTest(); \
        BRR_LOGI("success ("#EXPRESSION")"); \
    } \
    else \
    { \
        brrut::UnitTestCounter::GetInstance().IncreaseFailedTest(); \
        BRR_LOGE("failed ("#EXPRESSION")"); \
        BRR_LOGI("exit with status 1"); \
        brrut::UnitTestCounter::GetInstance().PrintResult(); \
        exit(1); \
    } \
} while(0);

//! ************************************************************************************************
//! @brief check EXPRESSION and print message success or failed and MSG.
//! @brief If failed then exit from application.
//! ************************************************************************************************
#define BRRUT_ASSERT_EXIT_MSG(EXPRESSION, MSG) \
do { \
    if (EXPRESSION) \
    { \
        brrut::UnitTestCounter::GetInstance().IncreaseAllTest(); \
        BRR_LOGI("success ("#EXPRESSION") %s", MSG); \
    } \
    else \
    { \
        brrut::UnitTestCounter::GetInstance().IncreaseFailedTest(); \
        BRR_LOGE("failed ("#EXPRESSION") %s", MSG); \
        BRR_LOGI("exit with status 1"); \
        brrut::UnitTestCounter::GetInstance().PrintResult(); \
        exit(1); \
    } \
} while(0);

} // namespace brrut

#endif // BRR_TEST_BASE_H
