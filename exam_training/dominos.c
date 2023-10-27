#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <math.h>

#define NAME_LENGHT 65

//----------------------------------------------------------------------------------------------------------------------
typedef struct tile {
    char name[NAME_LENGHT];
    int values[4];
    int duplicates[500] = {0};

}TTILE;

typedef struct domino {
    TTILE * data;
    int size;
    int capacity;
}TDOMINO;

//----------------------------------------------------------------------------------------------------------------------
int readInput(TDOMINO * dominos);

void appendToArray(TDOMINO * dominos, TTILE tile);

void alignTiles(TDOMINO * dominos);

void rotateTile(TDOMINO * dominos, int tile, int rotate);

void printDomino(TDOMINO *dominos);

int isSame(TTILE *a, TTILE *b);

void countDuplicates(TDOMINO *dominos);

void printDuplicates(TDOMINO *dominos);

int intCmp(TTILE *a, TTILE *b) {
    for (int i = 0; i < 4; ++i) {
        if ( a->values[i] < b->values[i])
            return -1;
        if ( a->values[i] > b->values[i])
            return 1;
    }
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------
int main(void)
{
    TDOMINO dominos;
    dominos.size = 0, dominos.capacity = 5;
    dominos.data = (TTILE*) malloc (dominos.capacity * sizeof(TTILE) );

    if (readInput(&dominos) == 0) {
        printf("Nespravny vstup.\n");
        free(dominos.data);
        return 1;
    }

    alignTiles(&dominos);
    qsort(dominos.data, dominos.size, sizeof(TTILE), (int(*)(const void *, const void *))intCmp );

    //printf("\ndomino po sesorteni:\n");
    //printDomino(&dominos);

    countDuplicates(&dominos);
    printDuplicates(&dominos);

    free(dominos.data);
    return 0;
}

//----------------------------------------------------------------------------------------------------------------------

int readInput(TDOMINO *dominos) {
    TTILE tile;
    char closing_bracket;
    int loaded;

    printf("Napis domina:\n");
    while( (loaded = scanf("%64s [ %d , %d , %d , %d %c", tile.name, &tile.values[0], &tile.values[1], &tile.values[2], &tile.values[3], &closing_bracket)) == 6) {
        if( closing_bracket != ']' ) {
            return 0;
        }
        appendToArray(dominos, tile);
    }
    // TODO: osetreni nedokoncenyho vstupu
    if ( !feof(stdin) ){
        return 0;
    }
    return 1;
}

void appendToArray(TDOMINO * dominos, TTILE tile) {
    // Check the size of dominos array --> realloc if needed
    if(dominos->size >= dominos->capacity) {
        dominos->capacity *= 1.5;
        dominos->data = (TTILE*) realloc (dominos->data, dominos->capacity * sizeof(TTILE) );
    }
    dominos->data[dominos->size++] = tile;
}

void alignTiles(TDOMINO * dominos) {
    for(int l = 0; l < dominos->size; l++) {    // For each tile
        int min = dominos->data[l].values[0];
        int rotate = 0;
        for(int i = 1; i < 4; i++) {            // For each value
            if(dominos->data[l].values[i] < min) {
                rotate = i;
                min = dominos->data[l].values[i];
            } else if (dominos->data[l].values[i] == min) { // If there are two same numbers in the tile, which are both equal to the min
                int tmp = (i == 3 ? -1 : i);
                if(dominos->data[l].values[tmp+1] < dominos->data[l].values[rotate+1]) {
                    rotate = i;
                    min = dominos->data[l].values[i];
                }
            }
        }
        if (rotate) {
            rotateTile(dominos, l, rotate);
        }
    }
}

void rotateTile(TDOMINO * dominos, int tile, int rotate) {
    for(int i = 0; i < rotate; i++) {
        int tmp = dominos->data[tile].values[0];
        dominos->data[tile].values[0] = dominos->data[tile].values[1];
        dominos->data[tile].values[1] = dominos->data[tile].values[2];
        dominos->data[tile].values[2] = dominos->data[tile].values[3];
        dominos->data[tile].values[3] = tmp;
    }
}

void printDomino(TDOMINO *dominos){
    for (int i = 0; i < dominos->size; ++i) {
        printf("%s [",dominos->data[i].name);
        for (int j = 0; j < 4; ++j) {
            printf("%d",dominos->data[i].values[j]);
            if(j!=3){
                printf(",");
            }
        }
        printf("]\n");
    }
}

void countDuplicates(TDOMINO *dominos) {
    int l, k, unique = dominos->size, duplicate;

    for (int i = 0; i < dominos->size-1; i += duplicate+1 ) {
        k = 0;
        l = i + 1;
        duplicate = 0;
        while( (isSame(&dominos->data[i], &dominos->data[l])) && (l <= dominos->size) ) {
            dominos->data[i].duplicates[k++] = l;
            l++;
            duplicate++;
            unique--;
        }
    }
    printf("\nUnikatnich kostek: %d\n", unique);

}

int isSame(TTILE *a, TTILE *b) {
    int same = 1;
    for (int i = 0; i < 4; i++) {
        if(a->values[i] != b->values[i]) {
            same = 0;
            break;
        }
    }
    return same;
}

void printDuplicates(TDOMINO *dominos) {
    int dupl, tile;

    printf("Duplikaty:\n");
    for (int i = 0; i < dominos->size; i += dupl+1) {
        dupl = 0;
        for (int j = 0; dominos->data[i].duplicates[j] != 0 ; j++) {
            tile = dominos->data[i].duplicates[j];
            if (!dupl) {
                printf("%s = %s", dominos->data[i].name, dominos->data[tile].name );
            } else {
                printf(" = %s", dominos->data[tile].name);
            }
            dupl++;
        }
        if(dupl) printf("\n");
    }
}