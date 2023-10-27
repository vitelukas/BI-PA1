#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define POINTS_MAX 1000000000
#define POINTS_MIN 0

//---------------------------------------------------------------------------------------

typedef struct points {
    int *data;
    int size;
    int capacity;
    int intervalStart;
    int intervalEnd;
    char startBracket;
    char endBracket;
}Tpoints;

int readPoints (Tpoints *);

int intCmp( const int *, const int * );

int readInterval(Tpoints *);

int searchInterval(Tpoints *);

//---------------------------------------------------------------------------------------

int main (void) {
    Tpoints pointsArr;
    pointsArr.size = 0, pointsArr.capacity = 5;
    pointsArr.data = (int*) malloc ( pointsArr.capacity * sizeof (int) );

    if ( readPoints(&pointsArr) == 0 ) {
        printf("Nespravny vstup.\n");
        free(pointsArr.data);
        return 0;
    }

    // Sort the array of student points
    qsort(pointsArr.data, pointsArr.size, sizeof(int), (int(*)(const void *, const void *))intCmp);

    if( readInterval(&pointsArr) == 0 ) {
        printf("Nespravny vstup.\n");
        free(pointsArr.data);
        return 0;
    }

    free(pointsArr.data);
    return 0;
}

//---------------------------------------------------------------------------------------

int intCmp( const int * x, const int * y ) {
    return ( *y < *x ) - ( *x < *y);
}

int readPoints (Tpoints *pointsArr) {
    char startBracket, comma_bracket;
    int points = 0;

    printf("Pocty bodu:\n");
    if( scanf(" %c %d %c", &startBracket, &points, &comma_bracket) !=3
        || startBracket != '{'
        || (points > POINTS_MAX && points < POINTS_MIN)
        || (comma_bracket != ',' && comma_bracket != '}') ) {
        return 0;
    }
    pointsArr->data[pointsArr->size] = points;
    pointsArr->size += 1;

    while (comma_bracket != '}') {
        if( scanf(" %d %c", &points, &comma_bracket) != 2
            || (points > POINTS_MAX && points < POINTS_MIN)
            || (comma_bracket != ',' && comma_bracket != '}') ) {
            return 0;
        }
        // Expand the array if needed
        if (pointsArr->size >= pointsArr->capacity) {
            pointsArr->capacity *= 1.5;
            pointsArr->data = (int*) realloc (pointsArr->data, pointsArr->capacity * sizeof(int));
        }
        pointsArr->data[pointsArr->size] = points;
        pointsArr->size += 1;
    }

    return 1;
}

int readInterval(Tpoints *pointsArr) {
    char semicolon;
    int load = 0;
    pointsArr->intervalStart = 0, pointsArr->intervalEnd = 0;

    printf("Intervaly:\n");
    while( (load = scanf(" %c %d %c %d %c", &pointsArr->startBracket, &pointsArr->intervalStart, &semicolon, &pointsArr->intervalEnd, &pointsArr->endBracket)) == 5 ) {
        if ( ( pointsArr->startBracket != '<' && pointsArr->startBracket != '(' )
        || ( pointsArr->endBracket != '>' && pointsArr->endBracket != ')' )
        || semicolon != ';' ) {
            return 0;
        }
        printf(" -> %d\n", searchInterval(pointsArr) );
    }
    if (pointsArr->endBracket != '>' && pointsArr->endBracket != ')') {
        return 0;
    }
    if ( ! feof(stdin) ) {
        return 0;
    }

    return 1;
}

int searchInterval(Tpoints *pointsArr) {
    int sum = 0, start = 0;

    if (pointsArr->intervalStart < pointsArr->data[start] && pointsArr->intervalEnd > pointsArr->data[pointsArr->size]) {
        return pointsArr->size;
    }

    for ( start = 0; pointsArr->startBracket == '<' ? pointsArr->data[start] < pointsArr->intervalStart : pointsArr->data[start] <= pointsArr->intervalStart ; start++) {
        if(start == pointsArr->size) {
            return 0;
            break;
        }
    }
    for ( int end = start; pointsArr->endBracket == '>' ? pointsArr->data[end] <= pointsArr->intervalEnd : pointsArr->data[end] < pointsArr->intervalEnd ; end++) {
        sum++;
    }

    return sum;
}