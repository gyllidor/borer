//! ************************************************************************************************
//! @file   TestThreadBase.h
//! @brief  unit tests for ThreadBase
//! @author gyllidor (gyllidor@ukr.net)
//! @date   24 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
#ifndef TEST_THREAD_BASE_H
#define TEST_THREAD_BASE_H

// local
#include "BrrTestBase.h"

namespace brrut
{

class TestThreadBase : public TestBase
{
public: // methods
    void Run();

private: // methods
    void TestRun();
    void TestJoinRetVal();
    void TestNotifyToStop();
    void TestCancel();

}; // class TestThreadBase

} // namespace brr

#endif // TEST_THREAD_BASE_H
