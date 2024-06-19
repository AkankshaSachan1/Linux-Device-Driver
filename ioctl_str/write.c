#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#define size 50

int main()
{
    
    char buffer[size];
    int fd=open("/dev/driver0",O_RDWR);
    if(fd==-1)
    {
        perror("Error opening file\n");
        exit(EXIT_FAILURE);
    }
    ssize_t rd_ret;
    printf("Enter the string\n");
    scanf("%[^\n]s",buffer);

    rd_ret=write(fd,buffer,sizeof(buffer));
    if(rd_ret==-1)
    {
        perror("Error in eriting in file\n");
        exit(EXIT_FAILURE);
    }
    printf("Data written %s\n",buffer);
    close(fd);
    return 0;

}