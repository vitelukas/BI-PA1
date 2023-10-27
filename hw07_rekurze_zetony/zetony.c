#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CAPACITY 32

//----------------------------------------------------------------------------------------------------

int readInput(int[4][CAPACITY], int[], int *);

int readFurther(char, int[4][CAPACITY], int[], int **);

//----------------------------------------------------------------------------------------------------

int main(void) {
    // cross[0] = North     cross[1] = South    cross[2] = East     cross[3] = West
    int cross[4][CAPACITY], allSides[4], numOfTokens = 0;

    printf("Zetony:\n");

    for (int i = 0; i < 4; i++) {
        if (readInput(cross, allSides, &numOfTokens) == 0) {
            printf("Nespravny vstup.\n");
            return 1;
        }
    }

    for( int i = 0; i < 4; i++) {
        if ( allSides[i] != 1 ) {
            printf("Nespravny vstup.\n");
            return 1;
        }
    }

    printf("hodnota north[4] = %d\n", cross[0][4]);
    printf("numOfTokens = %d\n", numOfTokens);
    //printf("Vstup OK\n");

    return 0;
}

//----------------------------------------------------------------------------------------------------

int readInput(int cross[4][CAPACITY], int allSides[], int * numOfTokens ) {
    char side, colon, curlyBracket;

    if ( scanf(" %c %c %c", &side, &colon, &curlyBracket) != 3
         || (side != 'N' && side != 'S' && side != 'E' && side != 'W' )
         || colon != ':'
         || curlyBracket != '{' ) {
        return 0;
    }
    if (readFurther(side, cross, allSides, &numOfTokens) == 0) {
        return 0;
    }

    return 1;
}

int readFurther( char side, int cross[4][CAPACITY], int allSides[], int ** numOfTokens ) {
    char comma_bracket;
    int n, s, e, w, valueOfToken;
    n = s = e = w = 0;

    do {
        if ( scanf(" %d %c", &valueOfToken, &comma_bracket) != 2
             || (comma_bracket != ',' && comma_bracket != '}') ) {
            return 0;
        }

        switch (side) {
            case 'N':
                cross[0][n] = valueOfToken;
                n++;
                allSides[0] = 1;
                break;
            case 'S':
                cross[1][s] = valueOfToken;
                s++;
                allSides[1] = 1;
                break;
            case 'E':
                cross[2][e] = valueOfToken;
                e++;
                allSides[2] = 1;
                break;
            case 'W':
                cross[3][w] = valueOfToken;
                w++;
                allSides[3] = 1;
                break;
        }
        if ( n > 32 || s > 32 || e > 32 || w > 32 ) {
            return 0;
        }

    } while ( comma_bracket != '}' );

    ** numOfTokens += n + s + e + w;
    return 1;
}
