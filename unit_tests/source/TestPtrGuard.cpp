//! ************************************************************************************************
//! @file   TestPtrGuard.cpp
//! @brief  unit tests for BrrPtrGuard
//! @author gyllidor (gyllidor@ukr.net)
//! @date   14 May 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
// local
#include "TestPtrGuard.h"

// project
#include "BrrTypes.h"
#include "BrrMemory.h"
#include "BrrPtrGuard.h"

//! ************************************************************************************************
//!
//! ************************************************************************************************
struct Additional
{
    bool funcTrue()  { return true; }
    bool funcFalse() { return false; }
};

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::TestPtrGuard::Run()
{
    BRRUT_ADD_TEST(TestDereferencePtr);
    BRRUT_ADD_TEST(TestDereferenceArrayPtr);
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::TestPtrGuard::TestDereferencePtr()
{
    brr::PtrGuard <uint>       ptrGuardUint(BRR_NEW_NOTHROW uint(5));
    brr::PtrGuard <Additional> ptrGuardAddit(BRR_NEW_NOTHROW Additional());

    BRRUT_ASSERT(*ptrGuardUint == 5);
    BRRUT_ASSERT(ptrGuardAddit->funcTrue() == true);
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::TestPtrGuard::TestDereferenceArrayPtr()
{
    uint* pUintArray = BRR_NEW_NOTHROW_ARRAY uint[2];
    pUintArray[0] = 1;
    pUintArray[1] = 255;

    brr::PtrArrayGuard <uint> ptrGuardUintArray(pUintArray);
    BRRUT_ASSERT(ptrGuardUintArray[0] == 1);
    BRRUT_ASSERT(ptrGuardUintArray[1] == 255);
    BRRUT_ASSERT(ptrGuardUintArray.Data()[0] == 1);
    BRRUT_ASSERT(ptrGuardUintArray.Data()[1] == 255);

    Additional* pAddit = BRR_NEW_NOTHROW_ARRAY Additional[2];
    brr::PtrArrayGuard <Additional> ptrGuardAdditionalArray(pAddit);
    BRRUT_ASSERT(ptrGuardAdditionalArray[0].funcTrue() == true);
    BRRUT_ASSERT(ptrGuardAdditionalArray[1].funcFalse() == false);
    BRRUT_ASSERT(ptrGuardAdditionalArray.Data()[0].funcTrue() == true);
    BRRUT_ASSERT(ptrGuardAdditionalArray.Data()[1].funcFalse() == false);
}
