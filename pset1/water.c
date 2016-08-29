#include <stdio.h>
#include <cs50.h>

int main(void) 
{
    int minutes;
    printf("minutes: ");
    minutes = GetInt();
    printf("bottles: %i\n", 12 * minutes);
}