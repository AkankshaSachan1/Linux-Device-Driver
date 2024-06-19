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
    fd=open("/dev/operation0",O_RDWR);
    if(fd==-1)
    {
        perror("Error in opening device");
        exit(EXIT_FAILURE);
    }
    ssize_t rd_ret;
    printf("Enter the string\n");
    scanf("%[^\n]s",buff);
    rd_ret=write(fd,buff,sizeof(buff));
    if(rd_ret==-1)
    {
        perror("Error in eriting in file\n");
        exit(EXIT_FAILURE);
    }
    close(fd);
    return 0;
}