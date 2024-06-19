#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    int num[2],res;
    printf("Enter two numbers\n");
    for(int i=0;i<2;i++)
    {
        scanf("%d",&num[i]);
    }
    int fd=open("/dev/Calculator3",O_RDWR);
    if(fd==-1)
    {
        perror("File not opened\n");
        exit(1);
    }
    if(write(fd,&num,sizeof(num))<0)
    {
        perror("Error inwriting file\n");
        return -1;
    }
    printf("Write function completed\nnum1=%d\tnum2=%d",num[0],num[1]);

     if(read(fd,&res,sizeof(res))<0)
    {
        perror("error in reading\n");
        exit(EXIT_FAILURE);
    }
     printf("\nresult=%d\n",res);
    printf("Read function completed\n");
    close(fd);
    return 0;
}