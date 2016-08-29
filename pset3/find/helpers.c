/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorith
    if (n < 0)
    {
        return false;
    }
    int jumpVal = n / 2;
    int place = n / 2;
    while (jumpVal != 0) 
    {
        int midElement = values[place];
        if (midElement == value || (place > 0 && value == values[place - 1]) || (place < n && value == values[place + 1]))
        {
            return true;
        }
        jumpVal = jumpVal / 2;
        if (midElement > value)
        {
            place = place - jumpVal;    
        } 
        else
        {
            place = place + jumpVal;   
        }
        //printf("place: %i. midElement: %i, jumpVal: %i", place, midElement, jumpVal);
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    bool fullSorted = false;
    while (!fullSorted)
    {
        fullSorted = true;
        for (int i = 0; i < n - 1; i++)
        {
            if (values[i] > values[i + 1])
            {
                int temp = values[i + 1];
                values[i+1] = values[i];
                values[i] = temp;
                fullSorted = false;
            }
        }
    }
    return;
}