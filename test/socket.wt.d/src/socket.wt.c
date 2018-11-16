/**
File:    socket.wt.c
Author:  Lukas Reichmann
Version: 1.0.0.0

A test for the component socket.
*/

#include "nostrasocketwrapper/socket.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef NSW_POSIX
#    include <sys/socket.h>
#    include <sys/types.h> /* for old BSD */
#elif defined(NSW_WINSOCK)
#    include <WinSock2.h>
#endif

void test_constants()
{
    if(NSW_AF_INET != AF_INET)
    {
        printf("Failed in line: %d\n", __LINE__);
        exit(__LINE__);
    }

    if(NSW_AF_INET6 != AF_INET6)
    {
        printf("Failed in line: %d\n", __LINE__);
        exit(__LINE__);
    }

    if(NSW_SOCK_STREAM != SOCK_STREAM)
    {
        printf("Failed in line: %d\n", __LINE__);
        exit(__LINE__);
    }

    if(NSW_SOCK_DGRAM != SOCK_DGRAM)
    {
        printf("Failed in line: %d\n", __LINE__);
        exit(__LINE__);
    }
}

void test_socket(void)
{
    {
        /* IPv4; TCP */
        nsw_socket_t sock = nsw_socket(NSW_AF_INET, NSW_SOCK_STREAM, 0);

        if(sock == -1)
        {
            printf("Failed in line: %d\n", __LINE__);
            exit(__LINE__);
        }
        else
        {
            nsw_reterr_t err = nsw_close(sock);

            if(err == -1)
            {
                printf("Failed in line: %d\n", __LINE__);
                exit(__LINE__);
            }
        }
    }

    {
        /* IPv4; UDP */
        nsw_socket_t sock = nsw_socket(NSW_AF_INET6, NSW_SOCK_STREAM, 0);

        if(sock == -1)
        {
            printf("Failed in line: %d\n", __LINE__);
            printf("errno: %d", nsw_get_error());
            exit(__LINE__);
        }
        else
        {
            nsw_reterr_t err = nsw_close(sock);

            if(err == -1)
            {
                printf("Failed in line: %d\n", __LINE__);
                exit(__LINE__);
            }
        }
    }

    {
        /* IPv6; TCP */
        nsw_socket_t sock = nsw_socket(NSW_AF_INET, NSW_SOCK_DGRAM, 0);

        if(sock == -1)
        {
            printf("Failed in line: %d\n", __LINE__);
            exit(__LINE__);
        }
        else
        {
            nsw_reterr_t err = nsw_close(sock);

            if(err == -1)
            {
                printf("Failed in line: %d\n", __LINE__);
                exit(__LINE__);
            }
        }
    }

    {
        /* IPv6; UDP */
        nsw_socket_t sock = nsw_socket(NSW_AF_INET6, NSW_SOCK_DGRAM, 0);

        if(sock == -1)
        {
            printf("Failed in line: %d\n", __LINE__);
            exit(__LINE__);
        }
        else
        {
            nsw_reterr_t err = nsw_close(sock);

            if(err == -1)
            {
                printf("Failed in line: %d\n", __LINE__);
                exit(__LINE__);
            }
        }
    }
}

void test_close(void)
{
    {
        nsw_socket_t sock = nsw_socket(NSW_AF_INET, NSW_SOCK_STREAM, 0);

        if(sock == -1)
        {
            printf("Failed in line: %d\n", __LINE__);
            exit(__LINE__);
        }
        else
        {
            /* close proper socket */
            nsw_reterr_t err = nsw_close(sock);

            if(err == -1)
            {
                printf("Failed in line: %d\n", __LINE__);
                exit(__LINE__);
            }
        }
    }

    {
        nsw_socket_t sock = -5; /* invalid socket ID */

        /* close proper socket */
        nsw_reterr_t err = nsw_close(sock);

        if(err != -1)
        {
            printf("Failed in line: %d\n", __LINE__);
            exit(__LINE__);
        }
    }
}

int main(void)
{
    if(nsw_initialize() == -1)
    {
        printf("Failed in line: %d\n", __LINE__);
        exit(__LINE__);
    }

    test_constants();

    test_socket();
    test_close();

    if(nsw_terminate() == -1)
    {
        printf("Failed in line: %d\n", __LINE__);
        exit(__LINE__);
    }
}
