#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//base address and mask are enough to store all necessary information about prefix
struct prefix
{
    unsigned int base; //address stored as 32 bits
    char mask; //stored as char because it's size is 1 byte
};

struct prefix* list;
unsigned int size;

int binarySearch(unsigned int base)
{
    unsigned int low = 0;
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
    return low;
}

//will have most responsibilities and will decide whether prefix
//should be overwritten, extended or just new space should be created
int add(unsigned int base, char mask)
{
    /*
        TO DO
        1. INTEGER OVERFLOW PREVENTION
        2. CREATE SMARTER SORTING
        3. ALL PREFIXES MUST BE UNIQUE, can't add the same thing twice
    */
    if(mask < 33 && mask >=0)
    {
        if(base <= 4294967295 && base >= 0)
        {
                list = realloc(list, sizeof(struct prefix)*(size+1));//allocate new space
                list[size].base = base;
                list[size].mask = mask;
                if(size >=1)
                {
                    for(int i=0;i<=size;i++)
                    {
                        for(int j=i+1;j<=size;j++)
                        {
                            if(list[i].base > list[j].base)
                            {
                                struct prefix temp = list[i];
                                list[i] = list[j];
                                list[j] = temp;
                            }
                        }
                    }
                }
                else
                {
                    if(list[0].base > list[1].base)
                    {
                        struct prefix temp = list[1];
                        list[1] = list[0];
                        list[0] = temp;
                    }
                }
                size++;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return -1;
    }

    return 1;
}

int del(unsigned int base, char mask)
{
    /*
        TO DO
        1. INTEGER OVERFLOW PREVENTION
        2. EXCEPTION HANDLING
        3. THINK ABOUT WHAT INFLUENCE MASK MIGHT HAVE
    */
    if(mask < 33 && mask >=0)
    {
        if(base <= 4294967295 && base >= 0)
        {
            unsigned int loc = binarySearch(base);
            for(int i=loc;i<=size-1;i++)
            {
                list[i] = list[i+1];
            }
            list = realloc(list, sizeof(struct prefix)*(size));
            size--;
            return 2;
        }
        else
        {
            return 0;
        }
    }
    else
    {
         return -1;
    }
}

char check(unsigned int ip)
{

    return 'A';
}


unsigned int convertBaseToInt(char* sourceString)
{
    /*
        TO DO
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
            oct[counter1++] = atoi(buffer);
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
    printf("%u.%u.%u.%u/%d\n", bytes[3], bytes[2], bytes[1], bytes[0], ip.mask);
}

void printList()
{
    struct prefix* ptr = list;
    printf("Current size: %d\n", size);
    for(int i=0;i<size;i++)
    {
        printIpAddress(ptr[i]);
    }
}


int main(int argc, char *argv[2])
{

    printf("Kiss the cook\n");

    list = calloc(1,sizeof(struct prefix));
    size = 0;
    int result = 0;

    result = add(42949629, 31);
    result = add(31772344, 21);
    result = add(29496725, 14);
    result = add(0, 32);
    result = add(3329496725, 5);
    result = add(57, 9);
    result = add(317744, 11);
    result = add(22222222,22);
    result = add(4294967295,0);
    printList();


    result = del(4294967295,0);
    printf("Result of last function: %d, Final size: %d\n", result, size);
    printList();

    /*
    char* base1 = "255.256.256.256";

    struct prefix pre1;

    pre1.base = convertBaseToInt(base1);

    pre1.mask = 16;

    printf("Result: %u\n", pre1.base);

    printIpAddress(pre1);
    */

    free(list);
    //getchar();
    return 0;
}
