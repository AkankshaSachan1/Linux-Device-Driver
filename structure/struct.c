#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#define size 10
struct student{
        char name[size];
        int roll_no;
};

struct student std[3];


static int struct_init(void){

}
