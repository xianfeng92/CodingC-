#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    char ch;
    int in, out;
    in = open("file.txt", O_RDONLY);
    out = open("fileout.txt", O_WRONLY|O_CREAT,S_IRUSR|S_IWGRP);
    while(read(in,&ch,1) == 1) 
    {
        write(out,&ch,1);
    }
    exit(0);
}