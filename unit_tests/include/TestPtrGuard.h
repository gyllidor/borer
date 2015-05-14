//! ************************************************************************************************
//! @file   TestPtrGuard.h
//! @brief  unit tests for BrrPtrGuard
//! @author gyllidor (gyllidor@ukr.net)
//! @date   14 May 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
#ifndef TEST_PTR_GUARD_H
#define TEST_PTR_GUARD_H

// local
#include "BrrTestBase.h"

namespace brrut
{

class TestPtrGuard : public TestBase
{
public: // methods
    void Run();

private: // methods
    void TestDereferencePtr();
    void TestDereferenceArrayPtr();

}; // class TestPtrGuard

} // namespace brrut

#endif // TEST_PTR_GUARD
