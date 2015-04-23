//! ************************************************************************************************
//! @file   ThreadBase.h
//! @brief  abstract class wrapper for pthread. For more information man pthread*.
//! @brief  Just inherit this class, implement one method (ThreadFunction) and
//! @brief  run this method in separeted thread.
//! @author gyllidor (gyllidor@ukr.net)
//! @date   24 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
// local
#include "ThreadBase.h"

//! ************************************************************************************************
//!
//! ************************************************************************************************
brr::ThreadBase::ThreadBase()
    : BrrBase()
    , m_thread(0)
{
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
brr::ThreadBase::ThreadBase(const std::string &threadName)
    : BrrBase(threadName)
    , m_thread(0)
{
}
