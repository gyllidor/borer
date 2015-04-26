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
#include "RWLock.h"

// system
#include <pthread.h>

namespace brr
{

class ThreadBase : public BrrBase
{
public: // methods
    ThreadBase();
    ThreadBase(const std::string& threadName);
    bool Run();
    bool IsRunning();
    bool Join();
    bool Join(void** pResult);
    bool NotifyToStop();
    bool Cancel();

protected: // methods
    virtual void* ThreadMethod() = 0;
    bool SetCancelState(int type);
    bool CancelationPoint();

private: // methods
    static void* ThreadFunction(void* pContext);

protected: // members
    pthread_t     m_thread;
    volatile bool m_isRunning;
    RWLock        m_rwLock;

}; // class ThreadBase

} // namespace brr

#endif // THREAD_BASE_H
