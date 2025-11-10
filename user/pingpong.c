//
// Created by baijiajun on 25-11-10.
//
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    int p2c[2],c2p[2];                 //p2c 父-子  c2p 子-父
    pipe(p2c);
    pipe(c2p);
    if(fork() != 0){              //父
        write(p2c[1], "Hello World!\n", 13);
        close(p2c[1]);
        char buf[15];
        read(c2p[0], &buf, 13);
        printf("%d : %s\n", getpid(), buf);
        wait(0);
    }
    else {
        char buf[15];
        read(p2c[0], &buf, 13);
        printf("%d : %s\n", getpid(), buf);
        write(c2p[1],&buf,13);
        close(c2p[1]);
    }
    close(p2c[0]);
    close(c2p[0]);
    exit(0);
}