//! ************************************************************************************************
//! @file   ThreadBase.h
//! @brief  abstract class wrapper for pthread. For more information man pthread*.
//! @brief  Just inherit this class, implement one method (ThreadFunction) and
//! @brief  run this method in separeted thread.
//! @author gyllidor (gyllidor@ukr.net)
//! @date   24 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
#ifndef THREAD_BASE_H
#define THREAD_BASE_H

// local
#include "BrrBase.h"

namespace brr
{

class ThreadBase : public BrrBase
{
public: // methods
    ThreadBase();
    ThreadBase(const std::string& threadName);
//    bool Run();
//    bool Join();
//    bool NotifyToStop();
//    bool Cancel();

protected: // methods
//    bool CancelationPoint();

protected: // members
    pthread_t m_thread;

}; // class ThreadBase

} // namespace brr

#endif // THREAD_BASE_H
