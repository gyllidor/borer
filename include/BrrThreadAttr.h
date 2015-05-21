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
    //! ********************************************************************************************
    //! @brief Default constructor; You must call Init() before use other methods.
    //! ********************************************************************************************
    ThreadAttr();

    //! ********************************************************************************************
    //! @brief Constructor; You must call Init() before use other methods.
    //! @param use className if you need know class/object name or something else.
    //! ********************************************************************************************
    ThreadAttr(const std::string& c_className);

    //! ********************************************************************************************
    //! @brief Destroy of m_attr;
    //! ********************************************************************************************
    ~ThreadAttr();

    //! ********************************************************************************************
    //! @brief The Init() function initializes the thread attributes object pointed to by m_attr
    //! with default attribute values. After this call, individual attributes of the object can be
    //! set using various related functions, and then the object can be used in one or more
    //! ThreadBase classes that create threads. Calling Init() on a thread attributes object that
    //! has already been initialized results in undefined behavior.
    //! man pthread_attr_init.
    //! @return true if success, otherwise false.
    //! ********************************************************************************************
    bool Init();

    //! ********************************************************************************************
    //! @brief The SetDetachState() function sets the detach state attribute of the thread to the
    //! value specified in detachstate. The detach state attribute determines whether a thread
    //! created using the thread attributes object attr will be created in a joinable or a detached
    //! state. The following values may be specified in detachstate:
    //! 1) PTHREAD_CREATE_DETACHED - Threads that are created using attr will be created in a
    //! detached state.
    //! PTHREAD_CREATE_JOINABLE - Threads that are created using attr will be created in a joinable
    //! state.
    //! The default setting of the detach state attribute in a newly initialized thread attributes
    //! object is PTHREAD_CREATE_JOINABLE.
    //! man pthread_attr_setdetachstate.
    //! @return true if success, otherwise false.
    //! ********************************************************************************************
    bool SetDetachState(int detachState);

    //! ********************************************************************************************
    //! @brief The SetGuardSize() function sets the guard size attribute of the thread attributes
    //! to the value specified in guardsize. If guardsize is greater than 0, then for each new
    //! thread created using attr the system allocates an additional region of at least guardsize
    //! bytes at the end of the thread's stack to act as the guard area for the stack. If guardsize
    //! is 0, then new threads created with attr will not have a guard area. The default guard size
    //! is the same as the system page size. If use SetStack() or SetStackAddr() then the guard size
    //! attribute is ignored(i.e., no guard area is created by the system).
    //! man pthread_attr_setguardsize.
    //! @return true if success, otherwise false.
    //! ********************************************************************************************
    bool SetGuardSize(size_t guardSize);

private: // members
    pthread_attr_t m_attr;

}; // class ThreadAttr

} // namespace

#endif // BRR_THREAD_ATTR_H
