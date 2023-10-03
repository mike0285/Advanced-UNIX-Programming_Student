#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#define BUFFSIZE 4096

int main(int argc, char **argv){
    
    if(argc != 3){
        printf("Invalid syntax.\n");
        exit(1);
    }
    // Open source file
    int fd = open(argv[1], O_RDONLY);
    if(fd == -1){
        perror("open");
        close(fd);
        exit(1);
    }

    char buf[BUFFSIZE];
    struct stat file_stat;

    // Extract source file permission 
    if (fstat(fd, &file_stat) == -1) {
        perror("fstat");
        close(fd);
        exit(1);
    }
    /* else{
        printf("%o\n", file_stat.st_mode);
    } */

    // Start copying process
    int fd2 = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, file_stat.st_mode);
    int readLen;
    while((readLen = read(fd, buf, BUFFSIZE)) > 0){
        write(fd2, buf, readLen);
    }

}