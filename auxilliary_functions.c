#include "auxilliary_functions.h"

unsigned int binarySearch(unsigned int base)
{
    /*
        Ordinary Binary Search algorithm
    */
    unsigned int low = 0;
    if(base <= list[0].base)
    {
        return low;
    }
    else
    {
        unsigned int high = size;
        int mid = 0;
        while(low <= high)
        {
            mid = low+(high-low)/2;
            if(base == list[mid].base)
            {
                return mid;
            }
            else if(base > list[mid].base)
            {
                low = mid+1;
            }
            else
            {
                high = mid-1;
            }
        }
    }
    return low;
}

struct prefix convertStringToPrefix(char* sourceString)
{
    /*
        This function allows user to enter prefixes as x.x.x.x/x
        and converts them to struct prefix
    */
    short len = 0;
    unsigned char oct[5]={0}, counter =0, counter1=0, i;
    char buffer[5];
    len = strlen(sourceString);
    struct prefix result;

    for(i=0;i<len;i++)
    {
        if(sourceString[i]!='.')
        {
            buffer[counter++] = sourceString[i];
        }
        if(sourceString[i]=='.' || i==len-1)
        {
            buffer[counter]='\0';
            counter=0;
            oct[counter1++] = atoi(buffer);
        }
        if(sourceString[i]=='/')
        {
            buffer[counter]='\0';
            counter=0;
            oct[counter1++] = atoi(buffer);
        }
    }
    if(oct[4] > 32)
    {
        printf("Subnet mask is too large, select between 0 and 32\n");
        result.base = 0;
        result.mask = 42;
        return result;
    }
    result.base = (256*256*256)*oct[0] + (256*256)*oct[1] + (256)*oct[2] + oct[3];
    result.mask = oct[4];
    return result;
}

void printIpAddress(struct prefix ip)
{
    unsigned char bytes[4];
    bytes[0] = ip.base & 0xFF;
    bytes[1] = (ip.base >> 8) & 0xFF;
    bytes[2] = (ip.base >> 16) & 0xFF;
    bytes[3] = (ip.base >> 24) & 0xFF;
    printf("%u.%u.%u.%u/%d\n", bytes[3], bytes[2], bytes[1], bytes[0], ip.mask);
}

void printList()
{
    struct prefix* ptr = list;
    //printf("Current size: %d\n", size);
    for(int i=0;i<size;i++)
    {
        printIpAddress(ptr[i]);
    }
}

void createPrefixList()
{
    /*
        Used for testing and presentation
    */
    // 10101010.00011100.11001100.01010101
    struct prefix newPrefix;
    newPrefix = convertStringToPrefix("192.168.44.0/8"); // 19.168.44.0 - 19.168.44.255
    //3232246784
    add(newPrefix.base, newPrefix.mask);

    newPrefix = convertStringToPrefix("10.20.0.0/16"); // 10.20.0.0 - 10.20.255.255
    //169082880
    add(newPrefix.base, newPrefix.mask);

    newPrefix = convertStringToPrefix("170.28.204.0/22"); // 170.28.204.0 - 170.28.255.255
    //2854013952
    add(newPrefix.base, newPrefix.mask);

    newPrefix = convertStringToPrefix("254.255.224.0/16"); // 10.20.0.0 - 10.20.255.255
    //169082880
    add(newPrefix.base, newPrefix.mask);

    newPrefix = convertStringToPrefix("32.64.128.0/20"); // 32.64.128.0 - 32.64.143.255
    //541097984
    add(newPrefix.base, newPrefix.mask);

    newPrefix = convertStringToPrefix("1.252.0.0/14"); // 1.252.0.0 - 1.255.255.255
    //33292288
    add(newPrefix.base, newPrefix.mask);

    newPrefix = convertStringToPrefix("168.0.0.0/24"); // 168.0.0.0 - 168.0.0.31
    //2818572288
    add(newPrefix.base, newPrefix.mask);

    newPrefix = convertStringToPrefix("69.0.0.0/9"); // 69.0.0.0 - 69.127.255.255
    //1157627904
    add(newPrefix.base, newPrefix.mask);

    newPrefix = convertStringToPrefix("112.89.128.0/20"); // 112.89.128.0 - 112.89.135.255
    //1884913664
    add(newPrefix.base, newPrefix.mask);

    newPrefix = convertStringToPrefix("254.255.192.0/19"); // 254.255.192.0 - 254.255.223.255
    //4278173696
    add(newPrefix.base, newPrefix.mask);

    newPrefix = convertStringToPrefix("168.0.0.0/16");

    add(newPrefix.base, newPrefix.mask);

    newPrefix = convertStringToPrefix("1.252.0.0/16");

    add(newPrefix.base,newPrefix.mask);

    newPrefix = convertStringToPrefix("168.0.0.0/20");

    add(newPrefix.base, newPrefix.mask);
}
