#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_LEN 64

typedef struct{
    int array[4];
    char name[NAME_LEN];
}TTILE;

typedef struct{
    TTILE *data;
    int max;
    int n;
}TDOMINO;


void appendToArray(TDOMINO *domino,TTILE tile){
    if(domino->n == domino->max){
        domino->max = domino->max*2 +1;
        domino->data = (TTILE*) realloc(domino->data, domino->max*sizeof(TTILE));
    }
    domino->data[domino->n++] = tile;
}

int readInput(TDOMINO *pole_domin){

    while(!feof(stdin)){
        TTILE tile;
        char bracket;
        int input = scanf("%63[^\n\t [] [ %d , %d , %d , %d %c ",tile.name,&tile.array[0],&tile.array[1],
                          &tile.array[2],&tile.array[3], &bracket);

        if(6!=input ||  bracket != ']'){
            return -1;
        }
        appendToArray(pole_domin, tile);
    }
    return 0;
}

void printDomino(TDOMINO *pole_domin){
    for (int i = 0; i < pole_domin->n; ++i) {
        printf("%s [",pole_domin->data[i].name);
        for (int j = 0; j < 4; ++j) {
            printf("%d",pole_domin->data[i].array[j]);
            if(j!=3){
                printf(",");
            }
        }
        printf("]\n");
    }
}

int cmpLex(const void *a, const void *b){
    TTILE *aPtr = (TTILE*)a;
    TTILE *bPtr = (TTILE*)b;

    for (int i = 0; i < 4; ++i) {
        if(aPtr->array[i] < bPtr->array[i]) return -1;
        if(aPtr->array[i] > bPtr->array[i]) return 1;
    }
    return 0;
}

TTILE sortTile(TTILE *tile){

    TTILE perm[4] = {};
    for (int i = 0; i < 4; ++i) {
        TTILE tmp ={};
        for (int j = 0; j < 4; ++j) {
             tmp.array[(j+i)%4] = tile->array[j];
        }
        perm[i] = tmp;
    }

    qsort(perm,4,sizeof(TTILE),cmpLex);

    TTILE min = perm[0];
    strncpy(min.name,tile->name, NAME_LEN);

    return min;
}
void sortDominos(TDOMINO *pole_domin){

    for (int i = 0; i < pole_domin->n; ++i) {
        pole_domin->data[i] = sortTile(&pole_domin->data[i]);
    }

    qsort(pole_domin->data,pole_domin->n,sizeof(TTILE),cmpLex);
}
int isSame(TTILE *a, TTILE *b){
    for (int i = 0; i < 4; ++i) {
        if(a->array[i]==b->array[i]){
            continue;
        }else{
            return 0;
        }
    }
    return 1;
}

void printDuplicates(TDOMINO *pole_domin){
    int count = 0;
    for (int i = 0; i < pole_domin->n-1; ++i) {
        if(isSame(&pole_domin->data[i],&pole_domin->data[i+1])){
            if(count==0){
                printf("%s == %s",pole_domin->data[i].name,pole_domin->data[i+1].name);
                count++;
            }
            else{
                printf(" == %s",pole_domin->data[i+1].name);
            }
        }
        else{
            if(count!=0) printf("\n");
            else{
                printf("%s\n",pole_domin->data[i].name);
            }
            count = 0;
        }
    }
    if(count==0){
        printf("%s\n",pole_domin->data[pole_domin->n-1].name);
    }
}
int main(void){

    TDOMINO pole_domin ={};
    if(readInput(&pole_domin)==-1){
        printf("ERROR\n");
        free(pole_domin.data);
        return 1;
    }

    printf("Pred sortem:\n");
    printDomino(&pole_domin);


    printf("Po sortu:\n");
    sortDominos(&pole_domin);
    printDomino(&pole_domin);

    printDuplicates(&pole_domin);
    free(pole_domin.data);
    return 0;
}