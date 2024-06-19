#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    int num1,num2,fd;
    
    printf("Inside wr_1\n");
    printf("Enter two number for addition\n");
    scanf("%d %d",&num1,&num2);
     int num[2]={num1,num2};
    fd=open("/dev/WR1",O_RDWR,0777);
    if(fd==-1)
    {
        perror("Error opening file\n");
        exit(EXIT_FAILURE);
    }
    printf("File opened successfully\n");

    int result=write(fd,&num,sizeof(num));
    if(result<0)
    {
        perror("Error in witing to kernel\n");
    }
    printf("Succssfully written to kernel\n");
    close(fd);
    return 0;
}