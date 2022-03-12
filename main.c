#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//base address and mask are enough to store all necessary information about prefix
struct prefix
{
    unsigned int base; //address stored as 32 bits
    char mask; //stored as char because it's size is 1 byte
};

//int add(unsigned int base, char mask)
//will have most responsibilities and will decide whether prefix
//should be overwritten, extended or just new space should be created

//int del(unsigned int base, char mask)
//provided that add function is created properly this function will only
//handle memory space after deleted prefixes

//char check(unsigned int ip)
//this will depend on how the data structure itself will be implemented
//tree? where "small" ip address are on the left side and big on the right side?
//tree would require two additional pointers in struct prefix


int main(int argc, char *argv[2])
{
    printf("Kiss the cook\n");
    //In order to be able to enter ip address as xxx.xxx.xxx.xxx format
    //create buffer unsigned(?) char[4] and function that will "translate" buffer to proper internal addressing mode
    //


    getchar();
    return 0;
}
