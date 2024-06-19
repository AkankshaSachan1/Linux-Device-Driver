#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>

#include"myioctl.h"

int rd_buff;
int main(){
    int ch;
    int time;

    int fd = open("/dev/ioctldevice",O_RDWR);
    if(fd == -1)
    {
        perror("device file not opened\n");
        exit(1);
    }
   while(1){
    printf("enter your choice\n1.enter timer value\n2.output\n3.exit\n");
    scanf("%d",&ch);

    switch(ch){

        case 1: printf("enter the timer value\n");
                scanf("%d",&time);
                ioctl(fd,cmd_1,&time);
                break;

        case 2: printf("Reading data\n");
                ioctl(fd,cmd_2,rd_buff);
                printf("data = %d\n",rd_buff);
                break;

        case 3:close(fd);
                exit(1);
    }
   } 
close(fd);
return 0;
}