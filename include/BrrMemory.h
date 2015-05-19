//! ************************************************************************************************
//! @file   BrrMemory.h
//! @brief  defines for new and delete;
//! @author gyllidor (gyllidor@ukr.net)
//! @date   26 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
#ifndef BRR_MEMORY_H
#define BRR_MEMORY_H

//! ************************************************************************************************
//! @brief This macroses are more obviously than clear new/delete and will help you in desision
//! @brief to call delete or delete[] and etc.
//! ************************************************************************************************
#define BRR_NEW                 new
#define BRR_NEW_ARRAY           new
#define BRR_NEW_NOTHROW         new (std::nothrow)
#define BRR_NEW_NOTHROW_ARRAY   new (std::nothrow)
#define BRR_DELETE              delete
#define BRR_DELETE_ARRAY        delete []

#endif // BRR_MEMORY
