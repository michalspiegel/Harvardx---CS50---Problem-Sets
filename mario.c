//A program that prints out pyramids out of #hashes, takes a height of the pyramid as an input

#include <stdio.h>
#include <cs50.h>

int get_suitable_int(void);

int main(void)
{

    int height = get_suitable_int();

    for (int i = 1; i < height + 1; i++)
    {
        for (int s = 1; s < ((height + 1) - i); s++)
        {
            printf(" ");
        }

        
        for (int w = 1; w < (i + 1); w++)
        {
            printf("#");
        }
    
        printf("  ");
        
        for (int d = 1; d < (i + 1); d++)
        {
            printf("#");
        }
        
        printf("\n");
    }



}

int get_suitable_int(void)
{
    int n;
    do
    {
        n = get_int("suitable integer:");
    }
    while ( ! (n > 0 && n < 9));
    return n;

}
