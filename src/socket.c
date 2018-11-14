#include "nostrasocketwrapper/socket.h"

#ifndef NSW_ERROR_H
#    include "nostrasocketwrapper/error.h"
#endif

#ifdef NSW_POSIX
#    include <errno.h>
#    include <sys/stat.h>
#    include <unistd.h>
#endif

#include <string.h>

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

    struct nsw_sockaddr_t *nsw_clear_sockaddr(struct nsw_sockaddr_t *sockaddr)
    {
        memset(sockaddr, 0, sizeof(struct nsw_sockaddr_t));
        return sockaddr;
    }

    nsw_reterr_t nsw_connect(nsw_socket_t socket, const struct nsw_sockaddr_t *addr)
    {
#ifdef NSW_RESTORE_ERRNO
        errno_t oldErrno = errno;
#endif

        int err = connect(socket, (struct sockaddr *)addr, sizeof(struct nsw_sockaddr_t));

        if(err == -1)
        {
            switch(errno)
            {
                case EACCES:
                    nsw_setError(NSW_ERR_ACCESS_DENIED);
                    break;

                    // TODO

                    // EINTR is possible, but missing in this switch
            }

#ifdef NSW_RESTORE_ERRNO
            errno = oldErrno;
#endif

            return -1;
        }

        return 0;
    }

    nsw_reterr_t nsw_bind(nsw_socket_t socket, const struct nsw_sockaddr_t *addr)
    {
#ifdef NSW_RESTORE_ERRNO
        errno_t oldErrno = errno;
#endif

        int err = bind(socket, (struct sockaddr *)addr, sizeof(struct nsw_sockaddr_t));

        if(err == -1)
        {
            switch(errno)
            {
                case EACCES:
                    nsw_setError(NSW_ERR_ACCESS_DENIED);
                    break;

                    // TODO

                    // EINTR is possible, but missing in this switch
            }

#ifdef NSW_RESTORE_ERRNO
            errno = oldErrno;
#endif

            return -1;
        }

        return 0;
    }

    nsw_reterr_t nsw_listen(nsw_socket_t socket, int backlog)
    {
#ifdef NSW_RESTORE_ERRNO
        errno_t oldErrno = errno;
#endif

        int err = listen(socket, backlog);

        if(err == -1)
        {
            switch(errno)
            {
                case EACCES:
                    nsw_setError(NSW_ERR_ACCESS_DENIED);
                    break;

                    // TODO

                    // EINTR is possible, but missing in this switch
            }

#ifdef NSW_RESTORE_ERRNO
            errno = oldErrno;
#endif

            return -1;
        }

        return 0;
    }

    nsw_reterr_t nsw_accept(nsw_socket_t socket, struct nsw_sockaddr_t *addr)
    {
#ifdef NSW_RESTORE_ERRNO
        errno_t oldErrno = errno;
#endif

        socklen_t len = sizeof(struct nsw_sockaddr_t);
        int err       = accept(socket, (struct sockaddr *)addr, &len);

        if(err == -1)
        {
            switch(errno)
            {
                case EACCES:
                    nsw_setError(NSW_ERR_ACCESS_DENIED);
                    break;

                    // TODO

                    // EINTR is possible, but missing in this switch
            }

#ifdef NSW_RESTORE_ERRNO
            errno = oldErrno;
#endif

            return -1;
        }

        return 0;
    }

    nsw_ssize_t nsw_send(nsw_socket_t socket, const void *data, size_t len, unsigned int flags)
    {
#ifdef NSW_RESTORE_ERRNO
        errno_t oldErrno = errno;
#endif

        int err = send(socket, data, len, flags);

        if(err == -1)
        {
            switch(errno)
            {
                case EACCES:
                    nsw_setError(NSW_ERR_ACCESS_DENIED);
                    break;

                    // TODO

                    // EINTR is possible, but missing in this switch
            }

#ifdef NSW_RESTORE_ERRNO
            errno = oldErrno;
#endif

            return -1;
        }

        return err;
    }

    nsw_ssize_t nsw_recv(nsw_socket_t socket, void *data, size_t len, unsigned int flags)
    {
#ifdef NSW_RESTORE_ERRNO
        errno_t oldErrno = errno;
#endif

        int err = recv(socket, data, len, flags);

        if(err == -1)
        {
            switch(errno)
            {
                case EACCES:
                    nsw_setError(NSW_ERR_ACCESS_DENIED);
                    break;

                    // TODO

                    // EINTR is possible, but missing in this switch
            }

#ifdef NSW_RESTORE_ERRNO
            errno = oldErrno;
#endif

            return -1;
        }

        return err;
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
                case EIO: // it is not documented when this occurs
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
