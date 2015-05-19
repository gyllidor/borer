//! ************************************************************************************************
//! @file   BrrBase.h
//! @brief  base class for all classes in borer
//! @author gyllidor (gyllidor@ukr.net)
//! @date   24 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
#ifndef BRR_BASE_H
#define BRR_BASE_H

// system
#include <string>

namespace brr
{

//! ************************************************************************************************
//! @brief Base class for all classes in Borer lib.
//! ************************************************************************************************
class Base
{
public: // methods
    Base() : m_className() {}
    Base(const std::string& className) : m_className(className) {}
    virtual ~Base() {}

    virtual const std::string& GetClassName() { return m_className; }

protected: // members
    std::string m_className;

}; // class BrrBase

} // namespace brr

#endif // BRR_BASE_H
