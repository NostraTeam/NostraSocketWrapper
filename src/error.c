#include "nostrasocketwrapper/error.h"

#ifdef __cplusplus
extern "C"
{
#endif
    NSW_INTERNAL_THREAD_LOCAL nsw_error_t nsw_internal_error = NSW_ERR_SUCCESS;

    const char *nsw_errorName(nsw_error_t error)
    {
        switch(error)
        {
            case NSW_ERR_SUCCESS:
                return NSW_ERR_SUCCESS_NAME;

            case NSW_ERR_UNKNOWN:
                return NSW_ERR_UNKNOWN_NAME;

            case NSW_ERR_INVALID_PARAMETER:
                return NSW_ERR_INVALID_PARAMETER_NAME;

            case NSW_ERR_ACCESS_DENIED:
                return NSW_ERR_ACCESS_DENIED_NAME;

            case NSW_ERR_FAMILY_NOT_SUPPORTED:
                return NSW_ERR_FAMILY_NOT_SUPPORTED_NAME;

            case NSW_ERR_TOO_MANY_PROCESS_FILES:
                return NSW_ERR_TOO_MANY_PROCESS_FILES_NAME;

            case NSW_ERR_TOO_MANY_SYSTEM_FILES:
                return NSW_ERR_TOO_MANY_SYSTEM_FILES_NAME;

            case NSW_OUT_OF_MEMORY:
                return NSW_OUT_OF_MEMORY_NAME;

            case NSW_ERR_UNSUPPORTED_PROTOCOL:
                return NSW_ERR_UNSUPPORTED_PROTOCOL_NAME;

            default:
                nsw_setError(NSW_ERR_INVALID_PARAMETER);
                return NSW_INTERNAL_ERR_UNKNOWN_ERROR_CODE_NAME;
        }
    }

    const char *nsw_errorText(nsw_error_t error)
    {
        switch(error)
        {
            case NSW_ERR_SUCCESS:
                return NSW_ERR_SUCCESS_TEXT;

            case NSW_ERR_UNKNOWN:
                return NSW_ERR_UNKNOWN_TEXT;

            case NSW_ERR_INVALID_PARAMETER:
                return NSW_ERR_INVALID_PARAMETER_TEXT;

            case NSW_ERR_ACCESS_DENIED:
                return NSW_ERR_ACCESS_DENIED_TEXT;

            case NSW_ERR_FAMILY_NOT_SUPPORTED:
                return NSW_ERR_FAMILY_NOT_SUPPORTED_TEXT;

            case NSW_ERR_TOO_MANY_PROCESS_FILES:
                return NSW_ERR_TOO_MANY_PROCESS_FILES_TEXT;

            case NSW_ERR_TOO_MANY_SYSTEM_FILES:
                return NSW_ERR_TOO_MANY_SYSTEM_FILES_TEXT;

            case NSW_OUT_OF_MEMORY:
                return NSW_OUT_OF_MEMORY_TEXT;

            case NSW_ERR_UNSUPPORTED_PROTOCOL:
                return NSW_ERR_UNSUPPORTED_PROTOCOL_TEXT;

            default:
                nsw_setError(NSW_ERR_INVALID_PARAMETER);
                return NSW_INTERNAL_ERR_UNKNOWN_ERROR_CODE_TEXT;
        }
    }

#ifdef __cplusplus
}
#endif