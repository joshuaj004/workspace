#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;
    do 
    {
       printf("height: ");
       height = GetInt();
    } while (height < 0 || height > 23);
    for (int lines = 1; lines <= height; lines++)
    {
        int spaces = 0;
        for (spaces = 0; spaces < height - lines; spaces++) 
        {
            printf(" ");
        }
        for (int hashes = 0; hashes <= height - spaces; hashes++) 
        {
            printf("#");
        }
        printf("\n");
    }
}