//
// Created by baijiajun on 25-11-13.
//
#include "user.h"
#include "../kernel//stat.h"
#include "../kernel/types.h"
#include "../kernel//fs.h"

void run(char *pro , char*arg)
{
    if (fork() == 0)
    {
        exec(pro, arg);
        exit(0);
    }
    return;
}

int main(int argc , char * argv[])
{
    char buf[1024];
    char* p , *last_p;
    char *argsbuf[128];
    char **args = argsbuf;
    for (int i = 1; i< argc; i++)
    {
        *agrs = argv[i];
        args++;
    }
    char **pa = args;

    while (read(0,p,1) != 0)
    {
        if (*p == '' || *p == '\n')
        {
            *p = '\0';
            *(pa++) = last_p;
            last_p = p+1;
            if (*p == '\n')
            {
                *pa = 0;
                run(argv[1],argsbuf);
                pa = args;
            }
        }
        p++;
    }
    if (pa ！= args)
    {
        *p = '\0';
        *(pa++) = last_p;
        *pa = 0;
        run(argv[1],argsbuf);
    }
    while (wait(0) != -1);
    exit(0);
}