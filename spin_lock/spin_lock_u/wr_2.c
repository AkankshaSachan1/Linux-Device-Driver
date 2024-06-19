#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    int size,i,fd,sum=0;
    
    printf("Inside wr_1\n");
    printf("Enter the size of the array\n");
    scanf("%d",&size);
    int num[size];
    printf("Enter elements of the array\n");
    for(i=0;i<size;i++)
    {
        scanf("%d ",num[i]);
    }
    for(i=0;i<size;i++)
    {
        sum=sum+num[i];
    }
     
    fd=open("/dev/WR1",O_RDWR,0777);
    if(fd==-1)
    {
        perror("Error opening file\n");
        exit(EXIT_FAILURE);
    }
    printf("File opened successfully\n");

    int result=write(fd,&sum,sizeof(sum));
    if(result<0)
    {
        perror("Error in witing to kernel\n");
    }
    printf("Succssfully written to kernel\n");
    close(fd);
    return 0;
}