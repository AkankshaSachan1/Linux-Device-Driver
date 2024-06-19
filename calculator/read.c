#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    int res;
    int fd =open("/dev/Calculator4",O_RDWR);
    if(fd==-1)
    {
        perror("File not opened\n");
        exit(EXIT_FAILURE);
    }
    if(read(fd,&res,sizeof(res))<0)
    {
        perror("error in reading\n");
        exit(EXIT_FAILURE);
    }
    printf("%d\n",res);
    printf("Read function completed\n");
    close(fd);
    return 0;
}