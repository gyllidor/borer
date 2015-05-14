//! ************************************************************************************************
//! @file   main.h
//! @brief  entry point for unit tests
//! @author gyllidor (gyllidor@ukr.net)
//! @date   24 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
// local
#include "TestThreadBase.h"
#include "TestPtrGuard.h"

// project
#include "BrrLogger.h"
#include "BrrMemory.h"

// system
#include <vector>

//! ************************************************************************************************
//! @brief main
//! ************************************************************************************************
int main()
{
    //! @brief tests for log macroses
    BRR_LOGI("test info");
    BRR_LOGW("test warn");
    BRR_LOGE("test erro");
    BRR_LOGV("test verb");

    //! @brief test for ASSERT
    BRRUT_ASSERT(0==0);

    //! @brief add test to pool
    std::vector <brrut::TestBase*> poolTests;
    poolTests.push_back(BRR_NEW_NOTHROW brrut::TestThreadBase);
    poolTests.push_back(BRR_NEW_NOTHROW brrut::TestPtrGuard);

    //! @brief run all tests
    std::vector <brrut::TestBase*>::iterator itTest = poolTests.begin();
    for (; itTest != poolTests.end(); ++itTest)
        (*itTest)->Run();

    //! @brief memory dealocation
    for (itTest = poolTests.begin(); itTest != poolTests.end(); ++itTest)
        BRR_DELETE (*itTest);

    brrut::UnitTestCounter::GetInstance().PrintResult();

    return 0;
}
