/**
File:    error.wt.c
Author:  Lukas Reichmann
Version: 1.0.0.0

A test for the component error.

This test is the same as the test in the file error.wt.c, but it will be compiled using a C++ compiler. This
is to check that the library also works with C++.
*/

#include "nostrasocketwrapper/error.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // check if properly initialized
    if(nsw_get_error() != NSW_ESUCCESS)
    {
        printf("Failed in line: %d\n", __LINE__);
        exit(__LINE__);
    }

    // set new error code
    nsw_set_error(NSW_EACCES);

    // check if new error code was actually set
    if(nsw_get_error() != NSW_EACCES)
    {
        printf("Failed in line: %d\n", __LINE__);
        exit(__LINE__);
    }

    ///\todo add checks if the error code is actually thread local
}
