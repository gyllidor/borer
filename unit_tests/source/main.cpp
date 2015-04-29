//! ************************************************************************************************
//! @file   main.h
//! @brief  entry point for unit tests
//! @author gyllidor (gyllidor@ukr.net)
//! @date   24 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
// local
#include "TestThreadBase.h"

// project
#include "BrrLogger.h"
#include "BrrMemory.h"

// system
#include <vector>

int main()
{
    //! @brief add test to pool
    std::vector < brrut::TestBase* > poolTests;
    poolTests.push_back( BRR_NEW_NOTHROW brrut::TestThreadBase );

    //! @brief run all tests
    std::vector < brrut::TestBase* >::iterator itTest = poolTests.begin();
    for (; itTest != poolTests.end(); ++itTest)
        (*itTest)->Run();

    //! @brief memory dealocation
    itTest = poolTests.begin();
    for (; itTest != poolTests.end(); ++itTest)
        BRR_DELETE (*itTest);

    //! @brief tests for log macroses
    BRR_LOGI("test info");
    BRR_LOGW("test warn");
    BRR_LOGE("test erro");
    BRR_LOGV("test verb");

    //! @brief test for ASSERT
    BRRUT_ASSERT(0==0);
    BRRUT_ASSERT(0==1);

    brrut::TestCounter::GetInstance().PrintResult();

    return 0;
}
