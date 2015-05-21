//! ************************************************************************************************
//! @file   BrrPtrGuard.h
//! @brief  holders for pointer and array of pointer
//! @author gyllidor (gyllidor@ukr.net)
//! @date   29 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
#ifndef BRR_PTR_GUARD_H
#define BRR_PTR_GUARD_H

// local
#include "BrrBase.h"
#include "BrrMemory.h"
#include "BrrLogger.h"

// system
#include <string>

namespace brr
{

//! ************************************************************************************************
//! @brief intent: hold pointer to some data and dealocation of data in destructor. Object not
//! copyable. In desctructor will be memory dealocation.
//! ************************************************************************************************
template <typename Type>
class PtrGuard : public Base
{
private: // blocked methods
    PtrGuard();
    PtrGuard(const PtrGuard& rhs);
    PtrGuard& operator=(const PtrGuard& rhs);

public: // methods
    PtrGuard(Type* pPointer)
        : Base()
        , m_pPointer(pPointer)
    {}

    PtrGuard(Type* pPointer, const std::string& className)
        : Base(className)
        , m_pPointer(pPointer)
    {}

    ~PtrGuard()
    {
        BRR_DELETE m_pPointer;
        m_pPointer = NULL;
    }

    Type* Data()             { return m_pPointer; }
    Type& operator*()  const { return *m_pPointer; }
    Type* operator->() const { return m_pPointer; }

protected: // members
    Type* m_pPointer;

}; // class PtrGuard

//! ************************************************************************************************
//! @brief intent: hold and dealocation(similar to PtrHolder) array of pointers. Object not
//! copyable. In desctructor will be memory dealocation.
//! ************************************************************************************************
template <typename Type>
class PtrArrayGuard : public PtrGuard <Type>
{
private: // blocked methods
    PtrArrayGuard();
    PtrArrayGuard(const PtrArrayGuard& rhs);
    PtrArrayGuard& operator=(const PtrArrayGuard& rhs);

public: // methods
    PtrArrayGuard(Type* pPointer)
        : PtrGuard <Type> (pPointer)
    {}

    PtrArrayGuard(Type* pPointer, const std::string& className)
        : PtrGuard <Type> (pPointer, className)
    {}

    Type& operator[](size_t idx) { return PtrGuard<Type>::m_pPointer[idx]; }

    ~PtrArrayGuard()
    {
        BRR_DELETE_ARRAY PtrGuard<Type>::m_pPointer;
        PtrGuard<Type>::m_pPointer = NULL;
    }

}; // class PtrArrayGuard

} // namespace brr

#endif // BRR_PTR_GUARD_H
