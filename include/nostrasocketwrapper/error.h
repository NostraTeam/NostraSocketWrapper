#ifndef NSW_ERROR_H
#define NSW_ERROR_H

#ifndef NSW_EXPORT_H
#    include "nostrasocketwrapper/export.h"
#endif

#define NSW_ERR_SUCCESS 0
#define NSW_ERR_SUCCESS_NAME "NSW_ERR_SUCCESS"
#define NSW_ERR_SUCCESS_TEXT "No error happened."

#define NSW_ERR_UNKNOWN 1
#define NSW_ERR_UNKNOWN_NAME "NSW_ERR_UNKNOWN"
#define NSW_ERR_UNKNOWN_TEXT "An unknown error happened."

// EINVAL
#define NSW_ERR_INVALID_PARAMETER 2
#define NSW_ERR_INVALID_PARAMETER_NAME "NSW_ERR_INVALID_PARAMETER"
#define NSW_ERR_INVALID_PARAMETER_TEXT "An invalid parameter was passed to a function."

// EACCESS
#define NSW_ERR_ACCESS_DENIED 3
#define NSW_ERR_ACCESS_DENIED_NAME "NSW_ERR_ACCESS_DENIED"
#define NSW_ERR_ACCESS_DENIED_TEXT "The access to a resource was denied by the operating system."

// EAFNOSUPPORT
#define NSW_ERR_FAMILY_NOT_SUPPORTED 4
#define NSW_ERR_FAMILY_NOT_SUPPORTED_NAME "NSW_ERR_FAMILY_NOT_SUPPORTED"
#define NSW_ERR_FAMILY_NOT_SUPPORTED_TEXT "The system does not support the provided protocol family."

// EMFILE
#define NSW_ERR_TOO_MANY_PROCESS_FILES 5
#define NSW_ERR_TOO_MANY_PROCESS_FILES_NAME "NSW_ERR_TOO_MANY_PROCESS_FILES"
#define NSW_ERR_TOO_MANY_PROCESS_FILES_TEXT "The process has too many opened files."

// ENFILE
#define NSW_ERR_TOO_MANY_SYSTEM_FILES 6
#define NSW_ERR_TOO_MANY_SYSTEM_FILES_NAME "NSW_ERR_TOO_MANY_SYSTEM_FILES"
#define NSW_ERR_TOO_MANY_SYSTEM_FILES_TEXT "The operating system has too many opened files."

// ENOBUFS | ENOMEM
#define NSW_OUT_OF_MEMORY 7
#define NSW_OUT_OF_MEMORY_NAME "NSW_OUT_OF_MEMORY"
#define NSW_OUT_OF_MEMORY_TEXT "The process has run out of memory."

// EPROTONOSUPPORT
#define NSW_ERR_UNSUPPORTED_PROTOCOL 8
#define NSW_ERR_UNSUPPORTED_PROTOCOL_NAME "NSW_ERR_UNSUPPORTED_PROTOCOL"
#define NSW_ERR_UNSUPPORTED_PROTOCOL_TEXT "A network protocol or protocol type is not supported."

#define NSW_INTERNAL_ERR_UNKNOWN_ERROR_CODE_NAME "<the code passed to nsw_errorName() was invalid>"
#define NSW_INTERNAL_ERR_UNKNOWN_ERROR_CODE_TEXT "<the code passed to nsw_errorText() was invalid>"

#define NSW_INTERNAL_THREAD_LOCAL __thread

#ifdef __cplusplus
extern "C"
{
#endif

    typedef int nsw_error_t;
    typedef int nsw_reterr_t;

    NSW_EXPORT extern NSW_INTERNAL_THREAD_LOCAL nsw_error_t nsw_internal_error;

    static inline nsw_error_t nsw_getError()
    {
        return nsw_internal_error;
    }

    static inline void nsw_setError(nsw_error_t error)
    {
        nsw_internal_error = error;
    }

    NSW_EXPORT const char *nsw_errorName(nsw_error_t error);
    NSW_EXPORT const char *nsw_errorText(nsw_error_t error);

#ifdef __cplusplus
}
#endif

#endif