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

// local
#include "BrrLogger.h"

// system
#include <vector>

//! ************************************************************************************************
//! @brief counters for test, number of all, failed and success tests
//! ************************************************************************************************
static int s_numberOfTests = 0;
static int s_failedTests   = 0;

//! ************************************************************************************************
//! @brief print name of test and then run test;
//! ************************************************************************************************
#define BRRUT_ADD_TEST(TEST_NAME) \
do { \
    BRR_LOGI("### start %s ###", #TEST_NAME); \
    TEST_NAME(); \
} while(0);

//! ************************************************************************************************
//! @brief check EXPRESSION and print message success or failed;
//! ************************************************************************************************
#define BRRUT_ASSERT(EXPRESSION) \
do { \
    ++s_numberOfTests; \
    if (EXPRESSION) \
        BRR_LOGI("success ("#EXPRESSION")"); \
    else \
    { \
        BRR_LOGE("failed ("#EXPRESSION")"); \
        ++s_failedTests; \
    } \
} while(0);

//! ************************************************************************************************
//! @brief check EXPRESSION and print message success or failed. If failed then exit from app;
//! ************************************************************************************************
#define BRRUT_ASSERT_EXIT(EXPRESSION) \
do { \
    ++s_numberOfTests; \
    if (EXPRESSION) \
        BRR_LOGI("success ("#EXPRESSION")"); \
    else \
    { \
        ++s_failedTests; \
        BRR_LOGE("failed ("#EXPRESSION")"); \
        BRR_LOGI("all %d, success %d, failed %d", \
                 s_numberOfTests, s_numberOfTests - s_failedTests, s_failedTests); \
        BRR_LOGI("exit with status 1"); \
        exit(1); \
    } \
} while(0);

//! ************************************************************************************************
//! @brief namespace for unit test, brrut(borer unit test);
//! ************************************************************************************************
namespace brrut
{

class BrrTestBase
{
private: // blocked methods
    BrrTestBase( const BrrTestBase& rhs );
    const BrrTestBase& operator=( const BrrTestBase& rhs );

public: // methods
    BrrTestBase() {}
    virtual ~BrrTestBase() {}

    virtual void Run() = 0;

}; // class BrrTestBase

} // namespace brrut

#endif // BRR_TEST_BASE_H
