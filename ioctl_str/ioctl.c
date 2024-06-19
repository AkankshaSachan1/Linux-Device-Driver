#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include"myioctl.h"
int main()
{
    int fd=open("/dev/driver2",O_RDWR);
    if(fd==-1)
    {
        perror("Error opening file\n");
        exit(EXIT_FAILURE);
    }
    if(ioctl(fd,cmd_1,&device_stats)<0)
    {
        perror("Failed to get stats\n");
        return -1;
    }
    printf("DEVICE STATS\n");
    printf("Size=%d\n",device_stats.size);
    printf("Buffer=%s\n",device_stats.buffer);
    printf("Read/Write=%s\n",device_stats.rw?"Write":"Read");
    
    close(fd);
    return 0;

}