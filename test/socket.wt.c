/**
File:    socket.wt.c
Author:  Lukas Reichmann
Version: 1.0.0.0

A test for the component socket.
*/

#include "nostrasocketwrapper/socket.h"

#include <stdio.h>
#include <stdlib.h>

void test_socket()
{
    {
        // IPv4; TCP
        nsw_socket_t sock = socket(NSW_AF_INET, NSW_SOCK_STREAM, 0);

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
        // IPv4; UDP
        nsw_socket_t sock = socket(NSW_AF_INET6, NSW_SOCK_STREAM, 0);

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
        // IPv6; TCP
        nsw_socket_t sock = socket(NSW_AF_INET, NSW_SOCK_DGRAM, 0);

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
        // IPv6; UDP
        nsw_socket_t sock = socket(NSW_AF_INET6, NSW_SOCK_DGRAM, 0);

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

void test_close()
{
    {
        nsw_socket_t sock = socket(NSW_AF_INET, NSW_SOCK_STREAM, 0);

        if(sock == -1)
        {
            printf("Failed in line: %d\n", __LINE__);
            exit(__LINE__);
        }
        else
        {
            // close proper socket
            nsw_reterr_t err = nsw_close(sock);

            if(err == -1)
            {
                printf("Failed in line: %d\n", __LINE__);
                exit(__LINE__);
            }
        }
    }

    {
        nsw_socket_t sock = -5; // invalid socket ID

        // close proper socket
        nsw_reterr_t err = nsw_close(sock);

        if(err != -1)
        {
            printf("Failed in line: %d\n", __LINE__);
            exit(__LINE__);
        }
    }
}

int main()
{
    test_socket();
    test_close();
}
