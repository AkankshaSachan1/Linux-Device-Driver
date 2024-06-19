#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<stdlib.h>
#include<sys/ioctl.h>

#include"myioctl.h"

int main(){
int ch,rd,k_buff;
int fd = open("/dev/ioctlfile",O_RDWR);
if(fd==-1)
{
    perror("File not opened\n");
    exit(1);
}
while(1)
{
    printf("Enter the choice\n1.SET\n2.GET\n3.Clear\n4.Exit\n");
    scanf("%d",&ch);
    switch(ch)
    {
        case 1: printf("Enter value to be set");
        	scanf("%d",&k_buff);
        	ioctl(fd,cmd_1,&k_buff);
                break;
        case 2:printf("Reading Data\n");
        	ioctl(fd,cmd_2,&rd);
        	printf("Data Read is %d\n",rd);
                break;
        case 3:
                ioctl(fd,cmd_3);
                ioctl(fd,cmd_2,&rd);
                printf("Data Read is %d\n",rd);
                break;
        case 4:
                exit(1);
                break;
    }
}
close(fd);
return 0;
}
