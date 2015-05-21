//! ************************************************************************************************
//! @file   BrrThreadAttr.cpp
//! @brief  Thread attributes object. man pthread_attr*
//! @author gyllidor (gyllidor@ukr.net)
//! @date   21 May 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
// local
#include "BrrThreadAttr.h"
#include "BrrLogger.h"

//! ************************************************************************************************
//!
//! ************************************************************************************************
brr::ThreadAttr::ThreadAttr()
    : Base()
    , m_attr()
{
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
brr::ThreadAttr::ThreadAttr(const std::string& c_className)
    : Base(c_className)
    , m_attr()
{
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
brr::ThreadAttr::~ThreadAttr()
{
    const int c_result = pthread_attr_destroy(&m_attr);
    if (c_result)
        BRR_LOGE("pthread_attr_destroy() failed, %s", StrErrno(c_result).c_str());
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
bool brr::ThreadAttr::Init()
{
    const int c_result = pthread_attr_init(&m_attr);
    if (c_result)
    {
        BRR_LOGE("pthread_attr_init() failed, %s", StrErrno(c_result).c_str());
        return false;
    }

    return true;
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
bool brr::ThreadAttr::SetDetachState(int detachState)
{
    const int c_result = pthread_attr_setdetachstate(&m_attr, detachState);
    if (c_result)
    {
        BRR_LOGE("pthread_attr_setdetachstate() failed, %s", StrErrno(c_result).c_str());
        return false;
    }

    return true;
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
bool brr::ThreadAttr::SetGuardSize(size_t guardSize)
{
    const int c_result = pthread_attr_setguardsize(&m_attr, guardSize);
    if (c_result)
    {
        BRR_LOGE("pthread_attr_setguardsize() failed, %s", StrErrno(c_result).c_str());
        return false;
    }

    return true;
}
