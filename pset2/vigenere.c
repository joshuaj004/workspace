#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int letterToNumber(char c);
char numberToLetter(int num, bool upper);
char vigenereHelper(char c, char keyLetter);
int getNextCharPlace(char c, string keyword, int currentPlace);

int main(int argc, string argv[])
{
    if (argc != 2) 
    {
        printf("Rabble rabble rabble");
        return 1;
    }
    string keyword = (argv[1]);
    for (int i = 0; i < strlen(keyword); i++)
    {
        if (!isalpha(keyword[i]))
        {
            printf("Rabble rabble rabble");
            return 1;
        }
    }
    
    string p = GetString();
    int currentPlace = -1;
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        currentPlace = getNextCharPlace(p[i], keyword, currentPlace);
        char newChar = vigenereHelper(p[i], keyword[currentPlace]);
        printf("%c", newChar);
    }
    printf("\n");
}

int getNextCharPlace(char c, string keyword, int currentPlace)
{
    if (!isalpha(c)) {
        return currentPlace;
    }
    else
    {
        currentPlace++;
        return currentPlace % strlen(keyword);
    }
}

char vigenereHelper(char c, char keyLetter)
{
    if (!isalpha(c)) {
        return c;
    }
    return numberToLetter(((letterToNumber(c) + letterToNumber(keyLetter)) % 26), isupper(c));
}

int letterToNumber(char c)
{
    if (isupper(c))
    {
        return c - 65;
    }
    else {
        return c - 97;
    }
}

char numberToLetter(int num, bool upper)
{
    if (upper) 
    {
        return num + 65;
    }
    else 
    {
        return num + 97;
    }
}