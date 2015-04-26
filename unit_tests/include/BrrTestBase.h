//! ************************************************************************************************
//! @file   BrrTestBase.h
//! @brief  simple base class for unit tests; Just implement tests what you need and call them
//! @brief  in method Run;
//! @author gyllidor (gyllidor@ukr.net)
//! @date   26 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
#ifndef BRR_TEST_BASE_H
#define BRR_TEST_BASE_H

// system
#include <vector>

//! ************************************************************************************************
//! @brief namespace for unit test, brrut(borer unit test);
//! ************************************************************************************************
namespace brrut
{

class BrrTestBase
{
private: // blocked methods
    BrrTestBase( const BrrTestBase& rhs );
    const BrrTestBase& operator=( const BrrTestBase& rhs );

public: // methods
    BrrTestBase() {}
    virtual ~BrrTestBase() {}

    virtual void Run() = 0;

}; // class BrrTestBase

} // namespace brrut

#endif // BRR_TEST_BASE_H
