#include<stdio.h>
#include<string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<stdlib.h>

#define size 100

int write_buff[size];
int read_buff[size];

int main(){
int ch;
int fd = open("/dev/USER_MAIN_DRIVER",O_RDWR);
if(fd==-1)
{
    perror("File not opened\n");
    exit(1);
}
while(1)
{
    printf("Enter the choice\n1.Write\n2.Read\n3.Exit\n");
    scanf("%d",&ch);
    switch(ch)
    {
            case 1: printf("Enter the string\n");
                    scanf("%s",write_buff);
                    write(fd,write_buff,size);
                    printf("write function completed\n");
                    break;
            
            case 2:printf("read start\n");
                   read(fd,read_buff,size);
                   printf("%s\n",read_buff);
                   printf("read completed\n");
                   break;

            case 3:close(fd);
                    exit(1);
        
    }
}
close(fd);
return 0;
}
