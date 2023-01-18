#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    string word = get_string("string please \n");
    //char hashvalue = toupper(s[0])

    int s = strlen(word);
    int hashvalue = toupper(word[0]);
    int hashvalue2 = toupper(word[s-1]);
    int a = 1;
    int b = 1;
    int * aptr = &a;
    int * bptr = &b;

    if ((hashvalue < 123) && (hashvalue > 64))
    {
        *aptr = hashvalue - 'A';
    }

    if ((hashvalue2 < 123) && (hashvalue2 > 64))
    {
        *bptr = hashvalue2 - 'A';
    }
    printf("%i\n",a);
    printf("%i\n",b);
    int c = a * b;
    printf("%i\n",c);





}