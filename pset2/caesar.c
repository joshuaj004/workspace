#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char charConvert(char c, int key);

int main(int argc, string argv[])
{
    if (argc != 2) 
    {
        printf("Stop breaking things...");
        return 1;
    }
    int key = atoi(argv[1]);
    string p = GetString();
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        char newChar = charConvert(p[i], key);
        printf("%c", newChar);
    }
    printf("\n");
}

char charConvert(char c, int key)
{
    int newKey = key % 26;
    if (isupper(c))
    {
        unsigned char tempChar = c + newKey;
        if (tempChar > 90)
        {
            tempChar = tempChar % 90 + 64;
        }
        return tempChar;
    }
    else if (islower(c)) 
    {
        unsigned char tempChar = c + newKey;
        if (tempChar > 122)
        {
            tempChar = tempChar % 122 + 96;
        }
        return tempChar;
    }
    else 
    {
        return c;
    }
}