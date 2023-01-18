#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x;
    do
    {
        x = get_int("Height of pyramid? ");
    }
    while ((x<1)||(x>8));

    for (int i = 1; i < x+1; i++)
    {

        //print spaces (x-i) times
        for (int k = 0; k < x-i; k++)
        printf(" ");
        //print # (i) times
        for (int k = 0; k < i; k++)
        printf("#");
        //print spaces (2) times
        printf("  ");
        for (int k = 0; k < i; k++)
        printf("#");
        //print new line
        printf("\n");
    }

}