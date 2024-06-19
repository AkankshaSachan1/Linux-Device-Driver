#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    char buffer[100];
    int fd=open("/dev/driver1",O_RDWR);
    if(fd==-1)
    {
        perror("Eeor in opening file");
        exit(EXIT_FAILURE);
    }
    if(read(fd,buffer,sizeof(buffer))<0)
    {
        perror("Fail to read\n");
        exit(EXIT_FAILURE);
    }
    printf("Data read =%s\n",buffer);
    close(fd);
    return 0;
}

