#ifndef AUXILLIARY_FUNCTIONS_H_INCLUDED
#define AUXILLIARY_FUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct prefix
{
    unsigned int base; //address stored as 32 bits
    char mask; //stored as char because it's size is 1 byte
};

struct prefix* list;
unsigned int size;

int add(unsigned int base, char mask);
int del(unsigned int base, char mask);
char check(unsigned int ip);

void createPrefixList();

struct prefix convertStringToPrefix(char* sourceString);
unsigned int binarySearch(unsigned int base);
void printIpAddress(struct prefix ip);
void printList();

#endif // AUXILLIARY_FUNCTIONS_H_INCLUDED
