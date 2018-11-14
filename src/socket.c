#include "nostrasocketwrapper/socket.h"

#ifndef NWS_ERROR_H
#    include "nostrasocketwrapper/error.h"
#endif

#ifdef NSW_POSIX
#    include <errno.h>
#    include <sys/stat.h>
#    include <unistd.h>
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    nsw_socket_t nsw_socket(nsw_address_family_t af, nsw_socket_type_t type, nsw_socket_protocol_t protocol)
    {
#ifdef NSW_RESTORE_ERRNO
        errno_t oldErrno = errno;
#endif

        nsw_socket_t ret = (nsw_socket_t)socket(af, type, protocol);

        if(ret == -1) // error
        {
            switch(errno)
            {
                case EACCES:
                    nsw_setError(NSW_ERR_ACCESS_DENIED);
                    break;
                case EAFNOSUPPORT:
                    nsw_setError(NSW_ERR_FAMILY_NOT_SUPPORTED);
                    break;
                case EINVAL:
                    nsw_setError(NSW_ERR_INVALID_PARAMETER);
                    break;
                case EMFILE:
                    nsw_setError(NSW_ERR_TOO_MANY_PROCESS_FILES);
                    break;
                case ENFILE:
                    nsw_setError(NSW_ERR_TOO_MANY_SYSTEM_FILES);
                    break;
                case ENOBUFS: // fall-through
                case ENOMEM:
                    nsw_setError(NSW_OUT_OF_MEMORY);
                    break;
                case EPROTONOSUPPORT:
                    nsw_setError(NSW_ERR_UNSUPPORTED_PROTOCOL);
                    break;
                default:
                    nsw_setError(NSW_ERR_UNKNOWN);
                    break;
            }

#ifdef NSW_RESTORE_ERRNO
            errno = oldErrno;
#endif

            return -1;
        }
        return ret;
    }

    nsw_reterr_t nsw_close(nsw_socket_t socket)
    {
#ifdef NSW_RESTORE_ERRNO
        errno_t oldErrno = errno;
#endif

        int err = close(socket);

        if(err == -1)
        {
            switch(errno)
            {
                case EBADF:
                    nsw_setError(NSW_ERR_INVALID_PARAMETER);
                    break;
                case EIO: //it is not documented when this occurs
                    nsw_setError(NSW_ERR_UNKNOWN);
                    break;
                default:
                    nsw_setError(NSW_ERR_UNKNOWN);
                    break;

                    // EINTR is possible, but missing in this switch
            }

#ifdef NSW_RESTORE_ERRNO
            errno = oldErrno;
#endif

            return -1;
        }

        return 0;
    }

    bool nsw_isSocket(nsw_socket_t socket)
    {
#ifdef NSW_RESTORE_ERRNO
        errno_t oldErrno = errno;
#endif

        struct stat statbuf;
        int err = fstat(socket, &statbuf);

        if(err == -1)
        {
#ifdef NSW_RESTORE_ERRNO
            errno = oldErrno;
#endif
            return false;
        }

        return (bool)(S_ISSOCK(statbuf.st_mode) != 0);
    }

#ifdef __cplusplus
}
#endif
