#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct domino {
    char * name;
    int values[4];
} domino;

typedef struct dominoArr {
    domino * data;
    size_t cap;
    size_t len;
} dominoArr;

void freeDom(domino d) {
    free(d.name);
}

void freeDomArr(dominoArr arr) {
    for(size_t i = 0; i < arr.len; i++) {
        freeDom(arr.data[i]);
    }
    free(arr.data);
}

int domCmp(const void * p1, const void * p2) {
    domino * dp1 = (domino *)p1;
    domino * dp2 = (domino *)p2;

    for(int i = 0; i < 4; i++) {
        if (dp1->values[i] < dp2->values[i]) return -1;
        if (dp1->values[i] > dp2->values[i]) return  1;
    }

    return 0;
}

void printDom(domino * d) {
    printf("%s [ %d, %d, %d, %d ]\n", d->name, d->values[0], d->values[1],
                d->values[2], d->values[3]);
}

domino loadDom(int * succ) {
    domino d = {};
    size_t cap = 0;
    
    size_t strsize = getdelim(&(d.name), &cap, ' ', stdin);

    if(strsize == 0) {
        *succ = 0;
        free(d.name);
        return d;
    }

    d.name[strsize-1] = '\0';

    char lastChar;
    int s = scanf(" [ %d , %d , %d , %d %c", 
            d.values+0, &d.values[1], d.values+2, d.values+3,
            &lastChar);

    if(s != 5 || lastChar != ']') {
        *succ = 0;
        free(d.name);
        return d;
    }

    *succ = 1;
    return d;
}

dominoArr loadAllDoms() {
    dominoArr arr = {};
    while(!feof(stdin)) {
        int succ = 1;
        domino d = loadDom(&succ);
        // todo: kontrola vstupu
        scanf(" ");
        
        if (arr.len + 1 >= arr.cap) {
            arr.data = (domino *)realloc(arr.data, sizeof(domino) * (arr.cap * 2 + 4));
            arr.cap = arr.cap * 2 + 4;
        }

        arr.data[arr.len++] = d;
    }

    return arr;
}

int main(void) {
    dominoArr arr = loadAllDoms();
    qsort(arr.data, arr.len, sizeof(domino), domCmp);
    printf("%ld\n", arr.len);
    freeDomArr(arr);
}
