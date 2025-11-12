//
// Created by baijiajun on 25-11-12.
//
#include <stdio.h>
#include <stdlib.h>

#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/types.h"

void sieve(int left_pipe)            //进行质数筛选
{
    int p;
    read(left_pipe[0],&p,sizeof(p));
    if ( p == -1)
    {
        exit(0);
    }
    printf("primes %d\n",p);

    int right_pipe[2];
    pipe(right_pipe);

    if (fork() == 0)
    {
        close(right_pipe[1]);
        close(left_pipe[0]);
        sieve(right_pipe[0]);
    }
    else
    {
        close(right_pipe[0]);
        int buf;
        while (read(left_pipe[0],&buf,sizeof(buf)) && buf != -1)
        {
            if (buf % p != 0)
            {
                write(right_pipe[1],&buf,sizeof(buf));
            }
        }
        buf = -1;
        write(right_pipe[1],&buf,sizeof(buf));
        wait(0);
        exit(0);
    }
}

int main(int argc, char **argv)
{
    int input_pipe[2];
    pipe(input_pipe);

    if (fork() == 0)    //子  读
    {
        close(input_pipe[1]);
        sieve(input_pipe);
        exit(0);
    }
    else
    {
        close(input_pipe[0]);
        for (int i =2 ;i<= 35;i++)
        {
            write(input_pipe[1],&i,sizeof(i));
        }
        int i =-1;
        write(input_pipe[1],&i,sizeof(i));
    }
    wait(0);            //等待子进程，不能等待间接子进程，只能在子进程中设置wait(0)等待！！！！！！！
    exit(0);

}