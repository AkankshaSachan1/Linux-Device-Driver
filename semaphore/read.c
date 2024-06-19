#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

char buff[50];
int main()
{
    int fd;
    fd=open("/dev/operation1",O_RDWR);
    if(fd==-1)
    {
        perror("Error opening file\n");
        exit(EXIT_FAILURE);
    }
    ssize_t rd_ret;
    rd_ret=read(fd,buff,sizeof(buff));
    if(rd_ret==-1)
    {
        perror("Error in reading\n");
        exit(EXIT_FAILURE);
    }
     else
     {
        printf("Read Data =%s\n",buff);
     }
     close(fd);
     return 0;
}