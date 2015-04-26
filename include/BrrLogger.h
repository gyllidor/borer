//! ************************************************************************************************
//! @file   BrrLogger.h
//! @brief  helpfull macroses for printf
//! @author gyllidor (gyllidor@ukr.net)
//! @date   24 Apr 2015
//! @link   https://github.com/gyllidor/borer
//! ************************************************************************************************
#ifndef BRR_LOGGER_H
#define BRR_LOGGER_H

// system
#include <errno.h>
#include <string.h>
#include <string>
#include <cstdio>

namespace brr
{

//! ************************************************************************************************
//! @brief  Get description of system error, stored in errno or returned by soome function, for
//! @brief  example pthread_cancel;
//! @param  [in] error number (errno for example);
//! @return description of system error;
//! ************************************************************************************************
std::string ErrnoDescription( error_t error )
{
    const size_t c_bufferLen = 256;
    char buffer[ c_bufferLen ] = { 0 };
    return strerror_r(error, buffer, c_bufferLen);
}

//! ************************************************************************************************
//! @brief  Get description of system error, stored in errno;
//! @return description of errno;
//! ************************************************************************************************
std::string ErrnoDescription()
{
    return ErrnoDescription( errno );
}

} // namespace brr

//! ************************************************************************************************
//! @brief escape codes for font colors (FC_);
//! ************************************************************************************************
#define BRR_FC_CYAN     "\033[36m"
#define BRR_FC_YELLOW   "\033[33m"
#define BRR_FC_RED      "\033[31m"
#define BRR_FC_WHITE    "\033[32m"
#define BRR_FC_RESET    "\033[0m"

//! ************************************************************************************************
//! @brief cut file name from file path;
//! ************************************************************************************************
#ifdef __FILE_NAME__
#warning macros __FILE_NAME__ already defined, you should change macros name
#else // __FILE_NAME__
#define  __FILE_NAME__ ( ( strrchr( __FILE__, '/' ) + 1 ) ? \
                           strrchr( __FILE__, '/' ) + 1 : __FILE__ )
#endif // __FILE_NAME__

#ifdef DEBUG_BUILD

//! ************************************************************************************************
//! @brief Print message to stderr with helpfull tags;
//! ************************************************************************************************
#define BRR_LOGI(format, arg...) fprintf(stderr, BRR_FC_CYAN   "[I][%s][%s][%d]: " BRR_FC_RESET \
                                         format ";\n", __FILE_NAME__, __FUNCTION__, __LINE__, ##arg)

#define BRR_LOGW(format, arg...) fprintf(stderr, BRR_FC_YELLOW "[W][%s][%s][%d]: " BRR_FC_RESET \
                                         format ";\n", __FILE_NAME__, __FUNCTION__, __LINE__, ##arg)

#define BRR_LOGE(format, arg...) fprintf(stderr, BRR_FC_RED    "[E][%s][%s][%d]: " BRR_FC_RESET \
                                         format ";\n", __FILE_NAME__, __FUNCTION__, __LINE__, ##arg)

#ifdef VERBOSE_LOGGER
#define BRR_LOGV(format, arg...) fprintf(stderr, BRR_FC_WHITE  "[V][%s][%s][%d]: " BRR_FC_RESET \
                                         format ";\n", __FILE_NAME__, __FUNCTION__, __LINE__, ##arg)
#else
#define BRR_LOGV
#endif // VERBOSE_LOGGER

#else // DEBUG_BUILD

#define BRR_LOGI(format, arg...) fprintf(stderr, BRR_FC_CYAN   "[I][%s][%s][%d]: " BRR_FC_RESET \
                                         format ";\n", __FILE_NAME__, __FUNCTION__, __LINE__, ##arg)
#define BRR_LOGW(format, arg...)
#define BRR_LOGE(format, arg...) fprintf(stderr, BRR_FC_RED    "[E][%s][%s][%d]: " BRR_FC_RESET \
                                         format ";\n", __FILE_NAME__, __FUNCTION__, __LINE__, ##arg)
#define BRR_LOGV(format, arg...)

#endif // DEBUG_BUILD

#endif // BRR_LOGGER_H
