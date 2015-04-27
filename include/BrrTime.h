//! ************************************************************************************************
//! @file   BrrTime.h
//! @brief  helpfull functions for time management
//! @author gyllidor (gyllidor@ukr.net)
//! @date   26 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
#ifndef BRR_TIME_H
#define BRR_TIME_H

// local
#include "BrrTypes.h"

// system
#include <time.h>

namespace brr
{
//! ************************************************************************************************
//! @brief just constant in one second for more detailes in source code;
//! ************************************************************************************************
static const uint sc_second = 1;

//! ************************************************************************************************
//! @brief just constant for one second in us(microseconds) for more detailes in source code;
//! @brief use carefully, short sleep in loop may decrease performance;
//! ************************************************************************************************
static const uint sc_secondInUs = 1000000;

//! ************************************************************************************************
//! @brief  For more details "man 3 sleep"
//! @brief  sleep for the specified number of seconds. Makes the calling thread sleep until seconds
//! @brief  seconds have elapsed or a signal arrives which is not ignored.
//! @param  [in] seconds - number of seconds for sleep;
//! @return Zero if the requested time has elapsed, or the number of seconds left to sleep,
//! @return if the call was interrupted by a signal handler;
//! ************************************************************************************************
uint Sleep(uint seconds);

//! ************************************************************************************************
//! @brief  For more details "man 3 usleep"
//! @brief  Suspend execution for microsecond intervals. The usleep() function suspends execution of
//! @brief  the calling thread for (at least) microSeconds microseconds. The sleep may be lengthened
//! @brief  slightly by any system activity or by the time spent processing the call or by the
//! @brief  granularity of system timers.
//! @param  [in] microSeconds - number of microseconds for sleep;
//! @return 0 on success. On error, -1 is returned, with errno set to indicate the cause of the
//! @return error.
//! ************************************************************************************************
int USleep(uint microSeconds);

//! ************************************************************************************************
//! @brief  For more details "man 3 time"
//! @brief  Function shall return the value of time in seconds since the Epoch.
//! @return Upon successful completion, GetTime() shall return the value of time. Otherwise,
//! @return (time_t)-1 shall be returned.
//! ************************************************************************************************
time_t GetTime();

//! ************************************************************************************************
//! @brief  For more details "man 3 time"
//! @brief  Function shall return the value of time in seconds since the Epoch.
//! @param  [in] tloc - argument points to an area where the return value is also stored.
//! @return Upon successful completion, GetTime() shall return the value of time. Otherwise,
//! @return (time_t)-1 shall be returned.
//! ************************************************************************************************
time_t GetTime(time_t& tloc);

} // namespace brr

#endif // BRR_TIME_H
