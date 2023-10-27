#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MATRIX_MAX 100
//---------------------------------------------------------------------------------
/*
 * Reads data from the input and saves it into the matrix
 * m == number of rows in the matrix ( starting from 0 )
 * n == number of columns in the matrix ( starting from 0 )
 */
int readRow (int [MATRIX_MAX] [MATRIX_MAX], int *, int *, int *, int *);

/*
 * Checks if the given matrix is horizontally symmetrical
 * If the matrix has odd number of rows the middle row is being ignored
 * and only the other rows are being compared
 * Returns: 1 if symmetrical
 *          0 if different
 */
int horizontalSymmetry (int [MATRIX_MAX] [MATRIX_MAX], int *, int *);

/*
 * Checks if the matrix is vertically symmetrical
 * Similar to horizontalSymmetry
 */
int verticalSymmetry (int [MATRIX_MAX] [MATRIX_MAX], int *, int *);

/*
 * Checks if the matrix is symmetrical from middle
 * --> "cross" symmetry
 * If the matrix has odd number of rows and columns the middle number is being taken as the middle of the matrix
 * and it's being ignored
 * If the matrix has even odd numbers of rows and columns the middle of the matrix is the imaginary cross
 * int the middle of the matrix
 * Returns: 1 if symmetrical
 *          0 if different
 */
int midSymmetry (int [MATRIX_MAX] [MATRIX_MAX], int *, int *);

//--------------------------------------------------------------------------------------------------------
int main(void) {
    int m, n, flag, tmpN;
    m = n = tmpN = 0;
    flag = 1;
    int matrix [MATRIX_MAX] [MATRIX_MAX];

    printf("Matice:\n");
    while (  flag == 1 ) {                                      // Flag switches to 0 if the user is done with inputting the matrix
        if ( readRow(matrix, &m, &n, &flag, &tmpN) == 0 ) {     // --> EOF is on input
            printf("Nespravny vstup.\n");
            return 1;
        }
        if ( n != tmpN && n != 0 ) {        // Checks if the matrix has the shape of a square or rectangle
            printf("Nespravny vstup.\n");   // --> if the number of columns is the same in all rows
            return 1;
        } else {
            n = tmpN;
        }
        if ( m == 0 && n == 0) {
            return 0;
        }
    }

// Functions to check all 3 kinds of symetry
    printf("Symetrie podle horizontalni osy: ");
    if ( horizontalSymmetry(matrix, &m, &n) ) {
        printf("ano\n");
    } else {
        printf("ne\n");
    }
    printf("Symetrie podle vertikalni osy: ");
    if (verticalSymmetry(matrix, &m, &n) ) {
        printf("ano\n");
    } else {
        printf("ne\n");
    }
    printf("Symetrie podle stredu: ");
    if (midSymmetry(matrix, &m, &n) ) {
        printf("ano\n");
    } else {
        printf("ne\n");
    }

    return 0;
}

//--------------------------------------------------------------------------------------------------------
int readRow (int mat[MATRIX_MAX] [MATRIX_MAX], int *m, int *n, int *flag, int *tmpN) {
    int r, c;
    r = *m;
    c = 0;
    char znak;

    do {
        if (scanf(" %d%c", &mat[r][c], &znak) == 2) {
            if ( znak == '.' || isalpha(znak)) {
                return 0;
            }
            c++;
            *tmpN = c;
        } else {
            if (feof(stdin)) {
                if (*m == 0 && *tmpN == 0) {
                    return 0;
                } else {
                    *flag = 0;
                    return 1;
                }
            }
            if (!feof(stdin)) {
                return 0;
            }
        }

        if ( *m > MATRIX_MAX-1 || c > MATRIX_MAX) {
            return 0;
        }
    } while (znak != '\n');

    *m += 1;
    if ( *tmpN != *n && *n != 0 ) {
        return 0;
    } else {
        *n = *tmpN;
    }

    return 1;
}

int horizontalSymmetry (int mat[MATRIX_MAX] [MATRIX_MAX], int *m, int *n) {

    for (int i = 0, j = *m-1 ; i < *m ; i++, j--) {         // m - 1 because m starts from 0
        for (int k = 0 ; k < *n ; k++) {
            if ( mat[i][k] != mat[j][k]) {
                return 0;
            }
        }
    }
    return 1;
}

int verticalSymmetry (int mat[MATRIX_MAX] [MATRIX_MAX], int *m, int *n) {
    for (int j = 0, k = *n-1 ; j < *n ; j++, k--) {         // n - 1 because n starts from 0
        for (int i = 0 ; i < *m ; i++) {
            if ( mat[i][j] != mat[i][k]) {
                return 0;
            }
        }
    }
    return 1;
}

int midSymmetry (int mat[MATRIX_MAX] [MATRIX_MAX], int *m, int *n) {

    for (int i = 0, j = *m-1 ; i < *m ; i++, j--) {
        for (int k = 0, l = *n-1; k < *n ; k++, l--) {
            if ( mat[i][k] != mat[j][l]) {
                return 0;
            }
        }
    }
    return 1;
}
