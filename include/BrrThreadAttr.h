//! ************************************************************************************************
//! @file   BrrThreadAttr.h
//! @brief  Thread attributes object. man pthread_attr*
//! @author gyllidor (gyllidor@ukr.net)
//! @date   21 May 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
#ifndef BRR_THREAD_ATTR_H
#define BRR_THREAD_ATTR_H

// local
#include "BrrBase.h"

// system
#include <pthread.h>

namespace brr
{

class ThreadAttr : public Base
{

public: // methods
    ThreadAttr();
    ThreadAttr(const std::string& c_className);
    ~ThreadAttr();

private: // members
    pthread_attr_t m_attr;

}; // class ThreadAttr

} // namespace

#endif // BRR_THREAD_ATTR_H
