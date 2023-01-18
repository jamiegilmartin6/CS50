#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long x = get_long("Enter Credit Card Number ");
    long y = x;

    long d1 = (x % 100)/10;
    long d1x = d1 * 2;
    long d1x1 = d1x % 10;
    long d1x2 = (d1x % 100)/10;

    long d2 = (x % 10000)/1000;
    long d2x = d2 * 2;
    long d2x1 = d2x % 10;
    long d2x2 = (d2x % 100)/10;

    long d3 = (x % 1000000)/100000;
    long d3x = d3 * 2;
    long d3x1 = d3x % 10;
    long d3x2 = (d3x % 100)/10;

    long d4 = (x % 100000000)/10000000;
    long d4x = d4 * 2;
    long d4x1 = d4x % 10;
    long d4x2 = (d4x % 100)/10;

    long d5 = (x % 10000000000)/1000000000;
    long d5x = d5 * 2;
    long d5x1 = d5x % 10;
    long d5x2 = (d5x % 100)/10;

    long d6 = (x % 1000000000000)/100000000000;
    long d6x = d6 * 2;
    long d6x1 = d6x % 10;
    long d6x2 = (d6x % 100)/10;

    long d7 = (x % 100000000000000)/10000000000000;
    long d7x = d7 * 2;
    long d7x1 = d7x % 10;
    long d7x2 = (d7x % 100)/10;

    long d8 = (x % 10000000000000000)/1000000000000000;
    long d8x = d8 * 2;
    long d8x1 = d8x % 10;
    long d8x2 = (d8x % 100)/10;

    long d9 = (x % 10)/1;

    long d10 = (x % 1000)/100;

    long d11 = (x % 100000)/10000;

    long d12 = (x % 10000000)/1000000;

    long d13 = (x % 1000000000)/100000000;

    long d14 = (x % 100000000000)/10000000000;

    long d15 = (x % 10000000000000)/1000000000000;

    long d16 = (x % 1000000000000000)/100000000000000;

    long sum1 = d1x1 + d1x2 + d2x1 + d2x2 + d3x1 + d3x2 + d4x1 + d4x2 + d5x1 + d5x2 + d6x1 + d6x2 + d7x1 + d7x2 + d8x1 + d8x2 + d9 + d10 + d11 + d12 + d13 + d14 + d15 + d16;
    long sum2 = sum1 % 10;

    //if (sum2 == 0)

    //{
     //   printf("Valid");

    //}
    //else
    //{
    //    printf("Invalid");
    //}

    //printf("\n");

//get length of credit card number

    long len = 0;
    while (x>0)
    {
        x=x/10;
        len++;
    }
    //printf("%li",len);
    //printf("\n");
//use credit card number length (len) to pick first and second digits

    long digit1 = len;
    long digit2 = len-1;
    //printf("%li",digit1);
    //printf("\n");
    //printf("%li",digit2);
    //printf("\n");

    long digit1pow = pow(10,digit1);
    long digit2pow = pow(10,digit1-1);
    long digit3pow = pow(10,digit1-1);
    long digit4pow = pow(10,digit1-2);
    //printf("%li",digit1pow);
    //printf("\n");
    //printf("%li",digit2pow);
    //printf("\n");

    long checkd1 = (y % digit1pow)/digit2pow;
    long checkd2 = (y % digit3pow)/digit4pow;
    //printf("%li",checkd1);
    //printf("\n");
    //printf("%li",checkd2);
    //printf("\n");

//If statements for AMEX Mastercard Visa or Invalid

    if ((sum2 == 0)&&(len == 15)&&((checkd2 == 4)||(checkd2 == 7))&&(checkd1 == 3))

    {
        printf("AMEX\n");
    }

    else if ((sum2 == 0)&&(len == 16)&&(checkd1 == 5)&&((checkd2 == 1)||(checkd2 == 2)||(checkd2 == 3)||(checkd2 == 4)||(checkd2 == 5)))
    {
        printf("MASTERCARD\n");
    }

    else if ((sum2 == 0)&&((len == 13)||(len == 16))&&(checkd1 == 4))
    {
        printf("VISA\n");
    }

    else
    {
        printf("INVALID\n");
    }


}