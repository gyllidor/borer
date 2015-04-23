//! ************************************************************************************************
//! @file   BrrBase.h
//! @brief  base class for all classes in borer
//! @author gyllidor (gyllidor@ukr.net)
//! @date   24 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
#ifndef BASE_H
#define BASE_H

// system
#include <string>

namespace brr
{

class BrrBase
{
public: // methods
    BrrBase() : m_className("<empty>") {}
    BrrBase(const std::string& className) : m_className(className) {}

    virtual const std::string& GetClassName() { return m_className; }

protected: // members
std::string m_className;

}; // class BrrBase

} // namespace brr

#endif // BASE_H
