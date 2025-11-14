//
// Created by baijiajun on 25-11-12.
//

#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fs.h"

void find(char *path , char *target)
{
    char buf[512];
    char *p;
    int fd;
    struct dirent de;
    struct stat st;
    if ((fd = open(path,0)) < 0)
    {
        fprintf(2,"can't open %s\n",path);
        return;
    }
    if (fstat(fd,&st) <0)
    {
        fprintf(2,"can't fstat\n");
        close(fd);
        return;
    }
    switch (st.type)
    {
        case T_FILE:
        if (strcmp(path+strlen(path)-strlen(target),target) == 0)
        {
            fprintf(2,"%s\n",path);
        }
        break;
        case T_DIR:
        strcpy(buf,path);
        p = buf+strlen(buf);
        *p++ = '/';
        while (read(fd,&de,sizeof(de)) ==  sizeof(de))
        {
            if (de.inum ==0)
            {
                continue;
            }
            memmove(p,de.name,DIRSIZ);
            p[DIRSIZ] = 0;
            if (strcmp(buf+strlen(buf)-2,"/.")!=0 && strcmp(buf+strlen(buf)-3,"/..")!=0 )
            {
                find(buf,target);
            }
        }
        break;
    }
    close(fd);
}

int main(int argc, char *argv[])
{
    if (argc <3 )
    {
        printf("Usage: find <filename> <directory>\n");
        exit(0);
    }
    char target[512];
    target[0] = '/';
    strcpy(target+1, argv[2]);
    find(argv[1] , target);
    exit(0);
}
