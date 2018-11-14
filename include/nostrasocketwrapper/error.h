#ifndef NSW_ERROR_H
#define NSW_ERROR_H

/**
\file nostrasocketwrapper/error.h

\author  Lukas Reichmann
\version 1.0.0.0
\since   1.0.0.0

\brief
A component that provides the error handling system of NSW.

\details
None of the error codes (the macros \ilc{NSW_ERR_*}) in this component are documented, because they may have
slightly different meanings in different contexts. However, the functions in which the errors are set will
have information on when certain errors will be set.

Additionally, each error code consists of three parts:
<table>
    <tr>
        <td>
            The code macro.
        </td>
        <td>
            The code macro holds the actual, numeric error code.
        </td>
    </tr>
    <tr>
        <td>
            The name macro.
        </td>
        <td>
            The name macro holds the name of the code macro as a string. E.g.: The name macro if
            \ilc{NSW_ERR_SUCCESS} expands to \ilc{"NSW_ERR_SUCCESS"}. These are used by nsw_errorName().
        </td>
    </tr>
    <tr>
        <td>
            The text macro.
        </td>
        <td>
            The text macro holds a short text that describes the error. These are used by nsw_errorText().
        </td>
    </tr>
</table>

\par_example
\code{.cpp}
\todo <EXAMPLE HERE>
\endcode

For a more detailed example, see \link error.ex.c here\endlink.
*/

/**
\example error.ex.c

An example that demonstrates the usage of the functionality provided by the error component.
*/

#ifndef NSW_EXPORT_H
#    include "nostrasocketwrapper/export.h"
#endif

#define NSW_ERR_SUCCESS 0
#define NSW_ERR_SUCCESS_NAME "NSW_ERR_SUCCESS"
#define NSW_ERR_SUCCESS_TEXT "No error happened."

#define NSW_ERR_UNKNOWN 1
#define NSW_ERR_UNKNOWN_NAME "NSW_ERR_UNKNOWN"
#define NSW_ERR_UNKNOWN_TEXT "An unknown error happened."

#define NSW_ERR_INVALID_PARAMETER 2
#define NSW_ERR_INVALID_PARAMETER_NAME "NSW_ERR_INVALID_PARAMETER"
#define NSW_ERR_INVALID_PARAMETER_TEXT "An invalid parameter was passed to a function."

#define NSW_ERR_ACCESS_DENIED 3
#define NSW_ERR_ACCESS_DENIED_NAME "NSW_ERR_ACCESS_DENIED"
#define NSW_ERR_ACCESS_DENIED_TEXT "The access to a resource was denied by the operating system."

#define NSW_ERR_FAMILY_NOT_SUPPORTED 4
#define NSW_ERR_FAMILY_NOT_SUPPORTED_NAME "NSW_ERR_FAMILY_NOT_SUPPORTED"
#define NSW_ERR_FAMILY_NOT_SUPPORTED_TEXT "The system does not support the provided protocol family."

#define NSW_ERR_TOO_MANY_PROCESS_FILES 5
#define NSW_ERR_TOO_MANY_PROCESS_FILES_NAME "NSW_ERR_TOO_MANY_PROCESS_FILES"
#define NSW_ERR_TOO_MANY_PROCESS_FILES_TEXT "The process has too many opened files."

#define NSW_ERR_TOO_MANY_SYSTEM_FILES 6
#define NSW_ERR_TOO_MANY_SYSTEM_FILES_NAME "NSW_ERR_TOO_MANY_SYSTEM_FILES"
#define NSW_ERR_TOO_MANY_SYSTEM_FILES_TEXT "The operating system has too many opened files."

#define NSW_OUT_OF_MEMORY 7
#define NSW_OUT_OF_MEMORY_NAME "NSW_OUT_OF_MEMORY"
#define NSW_OUT_OF_MEMORY_TEXT "The process has run out of memory."

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

    /**
    \brief
    The type that is used for errors.

    \author  Lukas Reichmann
    \version 1.0.0.0
    \since   1.0.0.0
    */
    typedef int nsw_error_t;

    /**
    \brief
    The type that is used when returning a success or error state.

    \details
    When this type is the return type of a function, the returned value will either be \ilc{0} when the
    function succeeded or \ilc{-1} when it failed.

    \warning
    The values returned using this type are not error codes. For error codes, the type \ilc{new_error_t} is
    used.

    \author  Lukas Reichmann
    \version 1.0.0.0
    \since   1.0.0.0
    */
    typedef int nsw_reterr_t;

    /**
    \brief
    Stores the current error code.

    \details
    Before an error code is set by a function, the error code will be initialized with \ilc{NSW_ERR_SUCCESS}.

    \note
    This variable is thread local.

    \author  Lukas Reichmann
    \version 1.0.0.0
    \since   1.0.0.0
    */
    ///\todo perhaps remove NSW_EXPORT; should not be accessible from the outside
    NSW_EXPORT extern NSW_INTERNAL_THREAD_LOCAL nsw_error_t nsw_internal_error;

    /**
    \return
    The current error code.

    \brief
    Returns the current error code.

    \details
    Since the error codes are specific to each thread, the result of this function may vary from thread to
    thread.

    \author  Lukas Reichmann
    \version 1.0.0.0
    \since   1.0.0.0
    */
    static inline nsw_error_t nsw_getError()
    {
        return nsw_internal_error;
    }

    /**
    \param error
    The new error code.

    \brief
    Sets the error code of the calling thread.

    \author  Lukas Reichmann
    \version 1.0.0.0
    \since   1.0.0.0
    */
    static inline void nsw_setError(nsw_error_t error)
    {
        nsw_internal_error = error;
    }

    /**
    \param error
    The error code to get the name of.

    \brief
    Returns the name of \ilc{error} as a string.

    \author  Lukas Reichmann
    \version 1.0.0.0
    \since   1.0.0.0
    */
    NSW_EXPORT const char *nsw_errorName(nsw_error_t error);

    /**
    \param error
    The error code to get the description text of.

    \brief
    Returns a short description text for \ilc{error}.

    \author  Lukas Reichmann
    \version 1.0.0.0
    \since   1.0.0.0
    */
    NSW_EXPORT const char *nsw_errorText(nsw_error_t error);

#ifdef __cplusplus
}
#endif

#endif