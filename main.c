#include "auxilliary_functions.h"

int add(unsigned int base, char mask)
{
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

                    while(list[position].mask > mask && list[position].base == base)
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
            return -1;
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
    if(size == 0)
    {
        return 0;
    }
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
            return -1;
        }
    }
    else
    {
         return -1;
    }
    return -1;
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
        unsigned int j = locate;

        if(ip >= list[locate].base && ip <= inverted)
        {
            j--;
            inverted = ~(~0 << (32 - list[j].mask));
            inverted = list[j].base ^ inverted;

            while(ip >= list[j].base && ip <= inverted)
            {
                inverted = ~(~0 << (32 - list[j].mask));
                inverted = list[j].base ^ inverted;
                if(!(ip >= list[j].base && ip <= inverted))
                {
                    break;
                }
                j--;
            }
            j++;
            printIpAddress(list[locate - (locate-j)]);
            return list[locate - (locate-j)].mask;
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

    return -1;

}

int main(int argc, char *argv[2])
{
    size = 0;//"Initializes" program
    int status = 0;
    struct prefix test;

    printf("Add test 1, entry: 192.168.44.0/8\n");
    test = convertStringToPrefix("192.168.44.0/8");
    status = add(test.base, test.mask);
    if(status == 1)
    {
        printf("New prefix added\n");
        printList();
    }
    else
    {
        return 1;
    }

    printf("___________________________\n");
    printf("Add test 2, entry: 170.28.204.0/22\n");
    test = convertStringToPrefix("170.28.204.0/22");
    status = add(test.base, test.mask);
    if(status == 1)
    {
        printf("Second prefix added\n");
        printList();
    }
    else
    {
        return 1;
    }

    printf("___________________________\n");
    printf("Add test 3, entry: 170.28.204.0/22\n");
    test = convertStringToPrefix("170.28.204.0/22");
    status = add(test.base, test.mask);
    if(status == -1)
    {
        printf("Prefix is not unique\n");
        printList();
    }
    else
    {
        return 1;
    }

    printf("___________________________\n");
    printf("Del test 1, entry: 170.28.204.0/22\n");
    status = del(test.base, test.mask);
    if(status == 1)
    {
        printf("Prefix deleted\n");
        printList();
    }
    else
    {
        return 1;
    }

    printf("___________________________\n");
    printf("Del test 2, entry: 254.255.224.0/16\n");
    test = convertStringToPrefix("254.255.224.0/16");
    status = del(test.base, test.mask);
    if(status == -1)
    {
        printf("No such prefix found\n");
        printList();
    }
    else
    {
        printf("Status: %d", status);
        return 1;
    }

    printf("___________________________\n");
    printf("Del test 3, entry: 192.168.44.0/8\n");
    test = convertStringToPrefix("192.168.44.0/8");
    status = del(test.base, test.mask);
    if(status == 1)
    {
        printf("Prefix deleted\n");
        printList();
    }
    else
    {
        printf("Status: %d", status);
        return 1;
    }

    printf("___________________________\n");
    printf("Del test 4, entry: 254.255.224.0/16\n");
    test = convertStringToPrefix("254.255.224.0/16");
    status = del(test.base, test.mask);
    if(status == 0)
    {
        printf("The list is empty\n");
        printList();
    }
    else
    {
        return 1;
    }


    printf("___________________________\n");
    printf("Creating list of prefixes:\n");
    createPrefixList();
    printList();

    printf("___________________________\n");
    printf("Check test 1, entry: 32.64.133.249\n");
    test = convertStringToPrefix("32.64.133.249");
    status = check(test.base);
    if(status == 20)
    {
        printf("Mask found: %d\n", status);
    }
    else
    {
        return 1;
    }


    printf("___________________________\n");
    printf("Check test 2, entry: 1.252.56.34\n");
    test = convertStringToPrefix("1.252.56.34");
    status = check(test.base);
    if(status == 16)
    {
        printf("Mask found: %d\n", status);
    }
    else
    {
        return 1;
    }


    printf("___________________________\n");
    printf("Check test 3, entry: 168.0.1.22\n");
    test = convertStringToPrefix("168.0.1.22");
    status = check(test.base);
    if(status == 20)
    {
       printf("Mask found: %d\n", status);
    }
    else
    {
        return 1;
    }

    free(list);
    printf("Getchar() was used to halt the program, click anything: \n");
    getchar();
    return 0;
}
