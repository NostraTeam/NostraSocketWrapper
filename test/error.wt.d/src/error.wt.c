/**
File:    error.wt.c
Author:  Lukas Reichmann
Version: 1.0.0.0

A test for the component error.
*/

#include "nostrasocketwrapper/error.h"

#include <stdio.h>
#include <stdlib.h>

/* a giant switch with all available error codes */
/* if this function compiles, there are no overlapping error codes and all codes are valid integer numbers */
void check_error_codes()
{
    nsw_error_t error = NSW_ESUCCESS; /* value does not matter */

    /*switch(error)
    {
        case NSW_EACCES:
            break;
        case NSW_EADDRINUSE:
            break;
        case NSW_EADDRNOTAVAIL:
            break;
        case NSW_EAFNOSUPPORT:
            break;
        case NSW_EAGAIN:
            break;
        case NSW_EALREADY:
            break;
        case NSW_EBADF:
            break;
        case NSW_ECONNABORTED:
            break;
        case NSW_ECONNREFUSED:
            break;
        case NSW_ECONNRESET:
            break;
        case NSW_EDESTADDRREQ:
            break;
        case NSW_EFAULT:
            break;
        case NSW_EINPROGRESS:
            break;
        case NSW_EINTR:
            break;
        case NSW_EINVAL:
            break;
        case NSW_EISCONN:
            break;
        case NSW_ELOOP:
            break;
        case NSW_EMFILE:
            break;
        case NSW_EMSGSIZE:
            break;
        case NSW_ENAMETOOLONG:
            break;
        case NSW_ENETUNREACH:
            break;
        case NSW_ENFILE:
            break;
        case NSW_ENOBUFS:
            break;
        case NSW_ENOENT:
            break;
        case NSW_ENOMEM:
            break;
        case NSW_ENOTCONN:
            break;
        case NSW_ENOTDIR:
            break;
        case NSW_ENOTSOCK:
            break;
        case NSW_EOPNOTSUPP:
            break;
        case NSW_EPERM:
            break;
        case NSW_EPIPE:
            break;
        case NSW_EPROTO:
            break;
        case NSW_EPROTONOSUPPORT:
            break;
        case NSW_EPROTOTYPE:
            break;
        case NSW_EROFS:
            break;
        case NSW_ETIMEDOUT:
            break;
#ifndef NSW_POSIX /* Same as NSW_EAGAIN on POSIX */
    /*        case NSW_EWOULDBLOCK:
                break;
    #endif
            case NSW_ESYSNOTREADY:
                break;
            case NSW_EVERNOTSUPPORTED:
                break;
            case NSW_EPROCLIM:
                break;
            case NSW_ENNOTINITIALIZED:
                break;
            case NSW_ENETDOWN:
                break;
        }*/
}

int main(void)
{
    check_error_codes();

    /* check if properly initialized */
    if(nsw_get_error() != NSW_ESUCCESS)
    {
        printf("Failed in line: %d\n", __LINE__);
        exit(__LINE__);
    }

    /* set new error code */
    nsw_set_error(NSW_EACCES);

    /* check if new error code was actually set */
    if(nsw_get_error() != NSW_EACCES)
    {
        printf("Failed in line: %d\n", __LINE__);
        exit(__LINE__);
    }

    nsw_error_t err = NSW_ESUCCESS; /* it does not matter what error this is */

    /* set new error code */
    nsw_internal_set_errno(err);

    /* check if new error code was actually set */
    if(nsw_internal_get_errno() != err)
    {
        printf("Failed in line: %d\n", __LINE__);
        exit(__LINE__);
    }

    /**\todo add checks if the error code is actually thread local */

    return 0;
}
