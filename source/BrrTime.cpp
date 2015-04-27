//! ************************************************************************************************
//! @file   BrrTime.cpp
//! @brief  helpfull functions for time management
//! @author gyllidor (gyllidor@ukr.net)
//! @date   26 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
// local
#include "BrrTime.h"
#include "BrrLogger.h"

// system
#include "unistd.h"

//! ************************************************************************************************
//!
//! ************************************************************************************************
uint brr::Sleep(uint seconds)
{
    const uint c_result = sleep(seconds);
    if ( c_result )
        BRR_LOGW("sleep interupted by signal handler, seconds left %u", c_result);

    return c_result;
}


//! ************************************************************************************************
//!
//! ************************************************************************************************
int brr::USleep(uint microSeconds)
{
    const int c_result = usleep(microSeconds);
    if (c_result)
        BRR_LOGW("error occured, %s", StrErrno(c_result).c_str());

    return c_result;
}
