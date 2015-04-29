//! ************************************************************************************************
//! @file   BrrPtrHolder.h
//! @brief  holders for pointer and array of pointer
//! @author gyllidor (gyllidor@ukr.net)
//! @date   29 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
#ifndef BRR_PTR_HOLDER_H
#define BRR_PTR_HOLDER_H

// local
#include "BrrBase.h"
#include "BrrMemory.h"
#include "BrrLogger.h"

// system
#include <string>

namespace brr
{

//! ************************************************************************************************
//! @brief object not copyable. In desctructor will be memory dealocation;
//! ************************************************************************************************
template <typename Type>
class PtrHolder : public Base
{
private: // blocked methods
    PtrHolder();
    PtrHolder(const PtrHolder& rhs);
    PtrHolder& operator=(const PtrHolder& rhs);

public: // methods
    PtrHolder(Type*& pPointer)
        : Base()
        , m_pPointer(pPointer)
    {}

    PtrHolder(Type* pPointer, const std::string& className)
        : Base(className)
        , m_pPointer(pPointer)
    {}

    ~PtrHolder()
    {
        BRR_DELETE m_pPointer;
        m_pPointer = NULL;
    }

    const Type& operator*()  const { return *m_pPointer; }
          Type& operator*()        { return *m_pPointer; }
    const Type& operator->() const { return *m_pPointer; }
          Type& operator->()       { return *m_pPointer; }

protected: // members
    Type*& m_pPointer;

}; // class PtrHolder

//! ************************************************************************************************
//! @brief intent: hold and dealocation(similar to PtrHolder) array of pointers;
//! @brief object not copyable. In desctructor will be memory dealocation;
//! ************************************************************************************************
template <typename Type>
class PtrArrayHolder : public PtrHolder <Type>
{
private: // blocked methods
    PtrArrayHolder();
    PtrArrayHolder(const PtrArrayHolder& rhs);
    PtrArrayHolder& operator=(const PtrArrayHolder& rhs);

public: // methods
    PtrArrayHolder(Type*& pPointer)
        : PtrHolder <Type> (pPointer)
    {}

    const Type& operator[](size_t idx) const { return PtrHolder<Type>::m_pPointer[idx]; }
          Type& operator[](size_t idx)       { return PtrHolder<Type>::m_pPointer[idx]; }

    ~PtrArrayHolder()
    {
        BRR_DELETE_ARRAY PtrHolder<Type>::m_pPointer;
        PtrHolder<Type>::m_pPointer = NULL;
    }

}; // class PtrArrayHolder

} // namespace brr

#endif // BRR_PTR_HOLDER
