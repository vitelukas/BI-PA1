#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#endif /* __PROGTEST__ */

/* Takes decimal number converted to a string as an argument
 * if it's a palindrome return 1
 * else return 0
 */
int isPalindrome(char *);

/*
 * Takes a remainder after division as an int argumet
 * converts it into a charracter
 */
char valueToAscii(int);

/*
 * Takes a decimal number and converts it into a string
 */
char numToString (char *, unsigned long long, int);

/*
 * Main function
 * if radix or nextPalindrome in bigger than ULLONG_MAX
 *      --> return 0
 * else
 *      --> return 1
 *          and set the value of * next to decimal value of from(next palindrome)
 */
int nextPalindrome ( unsigned long long from, 
                     int radix,
                     unsigned long long * next )
{
    char toString[101];
    if ((radix < 2) || (radix > 36) || (from > 18446744073709551614LLu)) {
        return 0;
    }

    while (1) {
        from += 1;
        toString[100] = numToString(toString, from, radix);
        if (isPalindrome(toString)) {
            break;
        }
    }

    * next = from;
    return 1;
}

char numToString (char * toString, unsigned long long num, int base) {
    int position = 0;
    while (num!= 0) {
        toString[position++] = valueToAscii(num % base);
        num = num / base;
    }
    toString[position] = '\0';
    return * toString;
}

char valueToAscii(int val) {
    if (val >=0 && val <=9) {
        return (char)(val + '0');
    } else {
        return (char)(val + '7');
    }
}

int isPalindrome (char * numAsString) {
    int i = 0;
    int l = strlen(numAsString) -1;
    while (l>i) {
        if(numAsString[i++] != numAsString[l--]) {
            return 0;
        }
    }
    return 1;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  unsigned long long next;

  assert ( nextPalindrome ( 123, 10, &next ) == 1
           && next == 131 );
  assert ( nextPalindrome ( 188, 10, &next ) == 1
           && next == 191 );
  assert ( nextPalindrome ( 1441, 10, &next ) == 1
           && next == 1551 );
  assert ( nextPalindrome ( 95, 15, &next ) == 1
           && next == 96 ); /* 96 = 66 (radix 15) */
  assert ( nextPalindrome ( 45395, 36, &next ) == 1
           && next == 45431 ); /* 45431 = z1z (radix 36) */
  assert ( nextPalindrome ( 1027, 2, &next ) == 1
           && next == 1057 ); /* 1057 = 10000100001 (radix 2) */
  assert ( nextPalindrome ( 1000, 100, &next ) == 0
           && next == 1057 );
  assert ( nextPalindrome ( 18446744073709551614LLu, 2, &next ) == 1
           && next == 18446744073709551615LLu ); /* 18446744073709551615 = 1111111111111111111111111111111111111111111111111111111111111111 (radix 2) */
  assert ( nextPalindrome ( 18446744073709551615LLu, 2, &next ) == 0
           && next == 18446744073709551615LLu );
  return 0;
}
#endif /* __PROGTEST__ */