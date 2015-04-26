//! ************************************************************************************************
//! @file   BrrTestBase.cpp
//! @brief  simple base class for unit tests; Just implement tests what you need and call them
//! @brief  in method Run;
//! @author gyllidor (gyllidor@ukr.net)
//! @date   24 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
// local
#include "BrrTestBase.h"
#include "BrrLogger.h"

//! ************************************************************************************************
//!
//! ************************************************************************************************
brrut::BrrTestBase::BrrTestBase()
    : m_poolTests()
{
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
brrut::BrrTestBase::~BrrTestBase()
{
    std::vector <BrrTestBase*>::iterator itTest = m_poolTests.begin();
    for (; itTest != m_poolTests.end(); ++itTest)
    {
        delete *itTest;
        *itTest = NULL;
    }

    m_poolTests.clear();
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::BrrTestBase::Run()
{
    std::vector <BrrTestBase*>::iterator itTest = m_poolTests.begin();
    for (; itTest != m_poolTests.end(); ++itTest)
        (*itTest)->Tests();
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::BrrTestBase::Push(brrut::BrrTestBase *pTest)
{
    m_poolTests.push_back(pTest);
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void brrut::BrrTestBase::Tests()
{
    BRR_LOGE("<tests not implemented>");
}
