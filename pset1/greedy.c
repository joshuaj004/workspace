#import <stdio.h>
#import <cs50.h>
#import <math.h>

int main(void)
{
    printf("O hai! How much change is owed?\n");
    float f = GetFloat();
    while (f < 0)
    {
        printf("How much change is owed?\n");
        f = GetFloat();
    }
    int cents = roundf(f * 100);
    int coins = 0;
    while (cents >= 25) 
    {
        cents -= 25;
        coins++;
    }
    while (cents >= 10) 
    {
        cents -= 10;
        coins++;
    }
    while (cents >= 5) 
    {
        cents -= 5;
        coins++;
    }
    while (cents >= 1) 
    {
        cents -= 1;
        coins++;
    }
    printf("%i\n", coins);
}