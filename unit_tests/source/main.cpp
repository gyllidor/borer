//! ************************************************************************************************
//! @file   main.h
//! @brief  entry point for unit tests
//! @author gyllidor (gyllidor@ukr.net)
//! @date   24 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
#include "BrrLogger.h"
#include "BrrTestBase.h"

int main()
{
    brrut::BrrTestBase tests;
    tests.Run();

    BRR_ASSERT_EXIT(1==0);
    BRR_LOGI( "test info" );
    BRR_LOGW( "test warn" );
    BRR_LOGE( "test erro" );
    BRR_LOGV( "test verb" );

    return 0;
}
