//
// Created by wings on 18-4-21.
//

#include "include/myshlib.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main()
{
    char buf[1024];
    char *cwd = my_getcwd(buf, sizeof(buf));
    if (NULL == cwd)
    {
        perror("Get current working directory fail.\n");
        exit(-1);
    }
    else
    {
        printf("%s\n", cwd);
    }
    return 0;
}