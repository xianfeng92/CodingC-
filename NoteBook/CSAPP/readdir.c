
#include "csapp.h"
#include <sys/types.h>
#include <dirent.h>


int main(int argc, char **argv) {
    DIR *streamp;
    struct dirent *dep;

    streamp = opendir(argv[1]);

    error = 0;

    while ((dep = readdir(streamp)) != NULL) {
        printf("Found file %s\n", dep->d_name);
    }

    if(error != 0) {
        unix_error("readdir error");
    }
    closedir(streamp);
    exit(0);
}