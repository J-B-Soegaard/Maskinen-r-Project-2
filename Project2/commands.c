#include <stdio.h>

int LD(char fileName[])
{
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL){
        FILE *fp = fopen("unshuffled.txt", "r"); // hvis ikke den der er givet en rigtigt fil navn så tag den det deck der sorteret.
    }
}