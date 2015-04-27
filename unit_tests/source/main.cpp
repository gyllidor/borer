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
    std::vector < brrut::BrrTestBase* > poolTests;
    poolTests.push_back( BRR_NEW_NOTHROW brrut::TestThreadBase );

    std::vector < brrut::BrrTestBase* >::iterator itTest = poolTests.begin();
    for (; itTest != poolTests.end(); ++itTest)
        (*itTest)->Run();

    itTest = poolTests.begin();
    for (; itTest != poolTests.end(); ++itTest)
        BRR_DELETE (*itTest);

    BRR_LOGI("test info");
    BRR_LOGW("test warn");
    BRR_LOGE("test erro");
    BRR_LOGV("test verb");
    BRRUT_ASSERT(0==0);
    BRRUT_ASSERT_EXIT(1==0);

    return 0;
}
