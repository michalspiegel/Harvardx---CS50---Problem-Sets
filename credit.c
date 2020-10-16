// Takes a credit card number as an input and outputs whether it is a valid number (using luhn´s algorithm) and if it is VISA, AMEX or MASTERCARD

#include <stdio.h>
#include <cs50.h>
#include <math.h>


int main(void)
{
    bool boolean = true;
    long long cardnumber = 0;
    int count = 0;


    // GET INPUT
    do
    {
        cardnumber = get_long_long("What is your number?");
        long long digits = cardnumber;
        while (digits > 0)
        {
            digits = digits/10;
            count++;
        }
        if (count != 13 && count != 15 && count != 16)
        {
            cardnumber = 0;
        }
   
    }
    while (cardnumber < 0);
   
    
    //LUHN´s ALGORITHM
    //GET A LIST OUT OF THE CARDNUMBER
    int numbers[count];
    
    for (int i = count - 1; i >= 0; i--)
    {
        numbers[i] = cardnumber % 10;
        cardnumber /= 10;
    }
   
   
    //DETERMINE IF THE NUMBER OF DIGITS IS ODD OR EVEN, THEN SET STARTING VAR FOR THE FOR LOOPS BELOW
    int a = 0;
    int b = 1;
    if (count % 2 != 0)
    {
        a = 1;
        b = 0;
    }
   
   
    //SUM OF THE ODD DIGITS
    int sum1 = 0;
    for (int i = a; i <=count - a; i += 2)
    {
        if (numbers[i]*2 > 9)
        {
            sum1 += 1;
            sum1 += numbers[i]*2 % 10;
        }
        else
        {
            sum1 += numbers[i]*2;
        }
        
    }
    
    
    //SUM OF THE EVEN NUMBERS
    int sum2 = 0;
    for (int i = b; i <= count - b ; i += 2)
    {
        sum2 += numbers[i];
       
    }
   
    
    
    //HAS THE SUM OF BOTH SUMs A ZERO AS THE LAST DIGIT?
    if ((sum1 + sum2) % 10 != 0)
    {
        boolean = false;
    }
    
    
    //DETERMINE WHAT KIND OF CREDIT CARD IT IS
    int two_digs = numbers[0]*10 + numbers[1];
    if (boolean != true)
    {
        printf("INVALID\n");
    }
    else if ((count == 15) && (two_digs == 34 || two_digs == 37))
    {
        printf("AMEX\n");
    }
    else if ((count == 16) && (two_digs == 51 || two_digs == 52 || two_digs == 53 || two_digs == 54 || two_digs == 55 ))
    {
        printf("MASTERCARD\n");
    }
    else if ((count == 13 || count == 16) && (numbers[0] == 4))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
    return 0
}
