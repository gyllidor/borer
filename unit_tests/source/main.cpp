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
#include "TestRWLock.h"

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

    brrut::TestRunner runner;
    runner.AddTest(BRR_NEW_NOTHROW brrut::TestThreadBase);
    runner.AddTest(BRR_NEW_NOTHROW brrut::TestPtrGuard);
    runner.AddTest(BRR_NEW_NOTHROW brrut::TestRWLock);

    runner.Run();
    return 0;
}
