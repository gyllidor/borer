//! ************************************************************************************************
//! @file   BrrFinalize.h
//! @brief  use this class for forbidance of inheritance
//! @author gyllidor (gyllidor@ukr.net)
//! @date   29 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
#ifndef BRR_FINALIZER_H
#define BRR_FINALIZER_H

namespace brr
{

//! ************************************************************************************************
//! @brief  use this class for forbidance of inheritance.
//! ************************************************************************************************
template <typename Type>
class Finalizer
{
    Finalizer() {}
    Finalizer(const Finalizer& rhs) {}
    friend Type;

}; // class Finalizer

} // namespace brr

//! ************************************************************************************************
//! @brief you can use this macros instead "public virtual brr::Finalizer <CLASS_NAME>".
//! ************************************************************************************************
#define FINALIZE(CLASS_NAME) public virtual brr::Finalizer <CLASS_NAME>

//! ************************************************************************************************
//! @brief ATTENTION you must use virtual inheritance otherwise it will not work.
//! @brief ATTENTION compilation error will occur when variable(with wrong inheritance)
//! @brief will be declared.
//! ************************************************************************************************
/*
class First : public virtual Finalizer <First>
{
};

class Second : public First
{
};

Second sec; // compilation error will occur;
*/

#endif // BRR_FINALIZER_H
