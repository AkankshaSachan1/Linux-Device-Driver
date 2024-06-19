#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
    int fd,op_result;
    
    printf("Inside rd\n");
    fd=open("/dev/rd",O_RDWR,0777);
    if(fd==-1)
    {
        perror("Error opening file\n");
        exit(EXIT_FAILURE);
    }
    printf("File opened successfully\n");

    int result = read(fd,&op_result,sizeof(op_result));
    if(result<0)
    {
        printf("Error in reading a file\n");
        exit(EXIT_FAILURE);
    }
    printf("Data read from kernel\n");
    close(fd);
    return 0;
}