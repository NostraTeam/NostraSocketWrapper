#ifndef NSW_PLATDECT_H
#define NSW_PLATDECT_H

/**
\file nostrasocketwrapper/platdect.h

\author  Lukas Reichmann
\version 1.0.0.0
\since   1.0.0.0

\brief
A component that provides basic platform detection.

\note
This header is mostly for internal use by the library.

\par_example
\code{.cpp}
#ifdef NSW_POSIX
    // Code that uses POSIX specific features
#elif defined(NSW_WINSOCK)
    // Code that uses Windows specific features
#endif

// an #else directive would be useless, an #error directive will be
// triggered if neither NSW_POSIX nor NSW_WINSOCK is defined.
\endcode

For a more detailed example, see \link platdect.ex.c here\endlink.
*/

/**
\example platdect.ex.c

An example that demonstrates the usage of the functionality provided by the platdect component.
*/

// make sure not both overrides are defined
#if defined(NSW_LIB_OVERRIDE_POSIX) && defined(NSW_LIB_OVERRIDE_WINSOCK)
#    error "NSW_LIB_OVERRIDE_POSIX and NSW_LIB_OVERRIDE_WINSOCK can not be defined at the same time."
#endif

#ifndef _DOXYGEN_ // proper implementation without Doxygen

// use overrides
#    if defined(NSW_LIB_OVERRIDE_POSIX)
#        define NSW_POSIX
#    elif defined(NSW_LIB_OVERRIDE_WINSOCK)
#        define NSW_WINSOCK
#    endif

// if no overrides are defined, detect platform
#    if !defined(NSW_WINSOCK) && !defined(NSW_POSIX)
#        if defined(__unix__)
#            define NSW_POSIX
#        elif defined _WIN32
#            define NSW_WINSOCK
#        else
#            error "Operating system is not supported."
#        endif
#    endif
#else // Doxygen

// Empty definitions for Doxygen; only these need to be documented

/**
\brief
This macro is defined on systems that use the POSIX library.

\details
If this macro is defined, \ilc{NSW_WINSOCK} is not defined.

\author  Lukas Reichmann
\version 1.0.0.0
\since   1.0.0.0
*/
#    define NSW_POSIX

/**
\brief
This macro is defined on Windows systems that have access to the \ilc{Winsock.h} and  \ilc{Windows.h} headers.

\details
If this macro is defined, \ilc{NSW_POSIX} is not defined.

\author  Lukas Reichmann
\version 1.0.0.0
\since   1.0.0.0
*/
#    define NSW_WINSOCK

#endif

#endif