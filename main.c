#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


unsigned int convertBaseToInt(char* sourceString)
{
    /*
        CREATE
        EXCEPTION HANDLING
    */
    short len = 0;
    unsigned char oct[4]={0}, counter =0, counter1=0, i;
    char buffer[4];
    len = strlen(sourceString);

    for(i=0;i<len;i++)
    {
        if(sourceString[i]!='.'){
            buffer[counter++] =sourceString[i];
        }
        if(sourceString[i]=='.' || i==len-1){
            buffer[counter]='\0';
            counter=0;
            oct[counter1++]=atoi(buffer);
        }
    }
    unsigned int result = (256*256*256)*oct[0] + (256*256)*oct[1] + (256)*oct[2] + oct[3];
    return result;
}



void printIpAddress(struct prefix ip)
{
    unsigned char bytes[4];
    bytes[0] = ip.base & 0xFF;
    bytes[1] = (ip.base >> 8) & 0xFF;
    bytes[2] = (ip.base >> 16) & 0xFF;
    bytes[3] = (ip.base >> 24) & 0xFF;
    printf("%d.%d.%d.%d/%d\n", bytes[3], bytes[2], bytes[1], bytes[0], ip.mask);
}


int main(int argc, char *argv[2])
{
    printf("Kiss the cook\n");
    //In order to be able to enter ip address as xxx.xxx.xxx.xxx format
    //create buffer unsigned(?) char[4] and function that will "translate" buffer to proper internal addressing mode
    char* base1 = "10.0.5.9";
    char* base2 = "255.255.255.255";
    char* base3 = "0.0.0.49";
    char* base4 = "123.54.0.99";

    struct prefix pre1;
    struct prefix pre2;
    struct prefix pre3;
    struct prefix pre4;

    pre1.base = convertBaseToInt(base1);
    pre2.base = convertBaseToInt(base2);
    pre3.base = convertBaseToInt(base3);
    pre4.base = convertBaseToInt(base4);

    pre1.mask = 16;
    pre2.mask = 0;
    pre3.mask = 2;
    pre4.mask = 24;

    printf("Result: %d\n", pre1.base);
    printf("Result: %d\n", pre2.base);
    printf("Result: %d\n", pre3.base);
    printf("Result: %d\n", pre4.base);

    printIpAddress(pre1);
    printIpAddress(pre2);
    printIpAddress(pre3);
    printIpAddress(pre4);


    //getchar();
    return 0;
}
