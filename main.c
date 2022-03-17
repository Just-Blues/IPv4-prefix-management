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

void printIpAddress(struct prefix ip);
void printList();

unsigned int binarySearch(unsigned int base)
{
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

//will have most responsibilities and will decide whether prefix
//should be overwritten, extended or just new space should be created
int add(unsigned int base, char mask)
{
    /*
        TO DO
        1. INTEGER OVERFLOW PREVENTION
        2. ALL PREFIXES MUST BE UNIQUE, can't add the same thing twice
        3. Search Similar to check();
        Needs to compare raw values (base with base) and check if the new prefix is contained in the mask of the other one
        Or maybe just let them both stay, why not.
    */
    if(mask < 33 && mask >=0)
    {
        if(base <= 4294967295 && base >= 0)
        {
                if(size == 0 )
                {
                    list = calloc(1,sizeof(struct prefix));
                }
                else
                {
                    list = realloc(list, sizeof(struct prefix)*(size+1));
                }
                unsigned int position = binarySearch(base);

                if(size >= 2)
                {
                    if(list[position].base == base && list[position].mask == mask)
                    {
                        return -1;
                    }

                    while(list[position].mask < mask && list[position].base == base)
                    {
                        position++;
                    }
                    if(position > size)
                    {
                        list[size].base = base;
                        list[size].mask = mask;
                    }
                    else
                    {
                        struct prefix current = list[position];
                        struct prefix next;
                        next.base = 0;
                        next.mask = 0;
                        if((position+1) < size)
                        {
                            next = list[position+1];
                        }

                            list[position].base = base;
                            list[position].mask = mask;
                            while(position < size)
                            {
                                position++;
                                list[position] = current;
                                if((position +1) > size)
                                {
                                    break;
                                }
                                current = next;
                                next = list[position+1];
                            }
                    }
                }
                else
                {
                    list[size].base = base;
                    list[size].mask = mask;
                    if(size == 1)
                    {
                        if(list[0].base > list[1].base && list[0].mask != list[1].mask)
                        {
                            struct prefix temp = list[1];
                            list[1] = list[0];
                            list[0] = temp;
                        }
                    }
                }
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
    size++;
    return 1;
}


int del(unsigned int base, char mask)
{
    /*
        TO DO
        1. INTEGER OVERFLOW PREVENTION
        2. EXCEPTION HANDLING
        3. THINK ABOUT WHAT INFLUENCE MASK HAS
        Not exactly, all it has to do is compare raw base and mask values and delete
    */
    if(mask < 33 && mask >=0)
    {
        if(base <= 4294967295 && base >= 0)
        {
            unsigned int loc = binarySearch(base);
            if(list[loc].base == base && list[loc].mask == mask)
            {
                for(int i=loc;i<=size-1;i++)
                {
                    list[i] = list[i+1];
                }
                list = realloc(list, sizeof(struct prefix)*(size));
                size--;
                return 1;
            }
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
    return 0;
}

char check(unsigned int ip)
{
    unsigned int locate = binarySearch(ip);
    if(locate == 0 && size == 0)
    {
        return -1;
    }

    if(list[locate].base == ip)
    {
        return list[locate].mask;
    }

    else if (list[locate].base > ip)
    {
        locate--;
        unsigned int inverted = ~(~0 << (32 - list[locate].mask));
        inverted = list[locate].base ^ inverted;
        unsigned int i = locate;
        if(ip >= list[locate].base && ip <= inverted)
        {
            while(list[i].mask > list[i-1].mask && !(list[i].base < list[locate].base) &&  i!=0)
            {
                printf("Loop?\n");
                i--;
            }
            return list[i].mask;
        }

        return -1;
    }
    else if(list[locate].base < ip)
    {
        if(locate < 0)
        {
            return -1;
        }
        if(locate > size)
        {
            return -1;
        }
    }

    return 0;

}

struct prefix convertStringToPrefix(char* sourceString)
{
    /*
        TO DO
        EXCEPTION HANDLING
    */
    short len = 0;
    unsigned char oct[5]={0}, counter =0, counter1=0, i;
    char buffer[5];
    len = strlen(sourceString);

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
    struct prefix result;
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
    printf("Current size: %d\n", size);
    for(int i=0;i<size;i++)
    {
        printIpAddress(ptr[i]);
    }
}

int main(int argc, char *argv[2])
{
    size = 0;

    int result = 0;
    struct prefix test;

    // 10101010.00011100.11001100.01010101

    test = convertStringToPrefix("192.168.44.0/8"); // 19.168.44.0 - 19.168.44.255
    //3232246784
    result = add(test.base, test.mask);

    test = convertStringToPrefix("10.20.0.0/16"); // 10.20.0.0 - 10.20.255.255
    //169082880
    result = add(test.base, test.mask);

    //result = convertStringToPrefix("10.20.0.0");

    test = convertStringToPrefix("170.28.204.0/22"); // 170.28.204.0 - 170.28.255.255
    //2854013952
    result = add(test.base, test.mask);


    test = convertStringToPrefix("254.255.224.0/16"); // 10.20.0.0 - 10.20.255.255
    //169082880
    result = add(test.base, test.mask);
    //result = binarySearch(result)


    test = convertStringToPrefix("32.64.128.0/20"); // 32.64.128.0 - 32.64.143.255
    //541097984
    result = add(test.base, test.mask);

    test = convertStringToPrefix("1.252.0.0/14"); // 1.252.0.0 - 1.255.255.255
    //33292288
    result = add(test.base, test.mask);

    test = convertStringToPrefix("168.0.0.0/27"); // 168.0.0.0 - 168.0.0.31
    //2818572288
    result = add(test.base, test.mask);

    test = convertStringToPrefix("69.0.0.0/9"); // 69.0.0.0 - 69.127.255.255
    //1157627904
    result = add(test.base, test.mask);

    test = convertStringToPrefix("112.89.128.0/20"); // 112.89.128.0 - 112.89.135.255
    //1884913664
    result = add(test.base, test.mask);

    test = convertStringToPrefix("170.28.204.0/22"); // 170.28.204.0 - 170.28.255.255
    //2854013952
    result = add(test.base, test.mask);

    test = convertStringToPrefix("254.255.192.0/19"); // 254.255.192.0 - 254.255.223.255
    //4278173696
    result = add(test.base, test.mask);

    test = convertStringToPrefix("168.0.0.0/19");
    result = add(test.base, test.mask);

    test = convertStringToPrefix("1.252.0.0/12");

    result = add(test.base,test.mask);

    test = convertStringToPrefix("69.127.0.0/1");


    result = check(test.base);

    printf("END OF PROGRAM\n");
    printList();

    printf("Result of last function: %d\n", result);


    free(list);

    printf("Getchar() was used to halt the program, click anything");
    getchar();
    return 0;
}
