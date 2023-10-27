#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct {
    char *name;
} TNAME;

typedef struct {
    TNAME *names;
    size_t n, max;
    int type;
    char *originalName;
} TPERSON;

typedef struct {
    TPERSON *arr;
    size_t n, max;
} TPEOPLE_ARRAY;

typedef struct {
    TPEOPLE_ARRAY prisli;
    TPEOPLE_ARRAY registrovany;
} TZKOUSKA;


int loadName(TNAME *person) {

    size_t num = 0;
    size_t count = getline(&person->name, &num, stdin);

    if (person->name[count - 1] == '\n') {
        person->name[count - 1] = 0;
    }

    if (count > 60 || person->name == NULL) {
        return -1;
    }
    return 0;
}

void addToArr(TPERSON *arr, TNAME name) {
    if (arr->n == arr->max) {
        arr->max = arr->max * 2 + 1;
        arr->names = (TNAME *) realloc(arr->names, arr->max * sizeof(TNAME));
    }
    arr->names[arr->n++] = name;
}

void sepNames(TPERSON *list, TNAME *nam) {
    list->originalName = strdup(nam->name);
    char *token = strtok(nam->name, " ");
    while (token) {
        TNAME name = {strdup(token)};
        addToArr(list, name);
        token = strtok(NULL, " ");
    }
}

void addToNamesArr(TPEOPLE_ARRAY *list, TPERSON names) {
    if (list->n == list->max) {
        list->max = list->max * 2 + 1;
        list->arr = (TPERSON *) realloc(list->arr, list->max * sizeof(TPERSON));
    }
    list->arr[list->n++] = names;
}

int cmpFn(const void *a, const void *b) {
    TNAME *aPtr = (TNAME *) a;
    TNAME *bPtr = (TNAME *) b;
    if (strlen(aPtr->name) != strlen(bPtr->name)) {
        return strlen(aPtr->name) < strlen(bPtr->name) ? -1 : 1;
    }
    return strcasecmp(aPtr->name, bPtr->name);
}

int cmpFn2(const void *a, const void *b) {
    TPERSON *aPtr = (TPERSON *) a;
    TPERSON *bPtr = (TPERSON *) b;
    size_t min_size = (aPtr->n < bPtr->n) ? aPtr->n : bPtr->n;

    for (size_t i = 0; i < min_size; ++i) {
        int result = cmpFn(&aPtr->names[i], &bPtr->names[i]);
        if (result != 0) {
            return result;
        }
    }
    return (aPtr->n == bPtr->n) ? 0 : (aPtr->n > bPtr->n) ? -1 : 1;
}

int typ(TPERSON *person){
    char sign;
    scanf("%c:", &sign);
    if (sign == 'R') {
        person->names = 0;
    } else if (sign == 'P') {
        person->type = 1;
    } else {
        return -1;
    }
    return 0;
}

int readInput(TZKOUSKA *zk) {
    int checkR = 1;

    while (1) {
        if (feof(stdin)) {
            break;
        }

        TPERSON person = {};

        if(typ(&person)==-1){
            return -1;
        }

        TNAME name = {};
        int input = loadName(&name);


        if (input == -1) {
            return -1;
        }
        if (person.type == 0 && checkR == 1) {

            sepNames(&person, &name);
            free(name.name);
            qsort(person.names, person.n, sizeof(TNAME), cmpFn);
            addToNamesArr(&zk->registrovany, person);
        }
        if (person.type == 0 && checkR != 1) {
            return -1;
        }
        if (person.type == 1) {
            checkR = 0;

            sepNames(&person, &name);

            free(name.name);
            qsort(person.names, person.n, sizeof(TNAME), cmpFn);
            addToNamesArr(&zk->prisli, person);
        }
    }
    return 0;
}

void printList(TPEOPLE_ARRAY *l) {
    printf("[");
    for (size_t i = 0; i < l->n; ++i) {
        printf("%d->[", l->arr[i].type);
        for (size_t j = 0; j < l->arr[i].n; ++j) {
            printf("%s", l->arr[i].names[j].name);
            if (j != l->arr[i].n - 1) {
                printf(",");
            }
        }
        printf("]");
        if (i != l->n - 1) {
            printf(",");
        }
    }
    printf("]\n");
}

int areSame(TPERSON *a, TPERSON *b) {
    if (a->n != b->n) return 0;
    for (size_t i = 0; i < a->n; ++i) {
        if (strcasecmp(a->names[i].name, b->names[i].name) != 0) {
            return 0;
        }
    }
    return 1;
}

void printRes(TPEOPLE_ARRAY *lR, TPEOPLE_ARRAY *lD) {
    printf("Nepritomni:\n");
    for (size_t i = 0; i < lR->n; ++i) {
        if (lR->arr[i].type == 0) {
            printf("*%s\n", lR->arr[i].originalName);
        }
    }
    printf("Bez registrace:\n");
    for (size_t i = 0; i < lD->n; ++i) {
        if (lD->arr[i].type == 1) {
            printf("*%s\n", lD->arr[i].originalName);
        }
    }
}

void findRes(TPEOPLE_ARRAY *lR, TPEOPLE_ARRAY *lD) {
    for (size_t i = 0; i < lR->n; ++i) {
        for (size_t j = 0; j < lD->n; ++j) {
            if (areSame(&lR->arr[i], &lD->arr[j]) && (lR->arr[i].type != 2 && lD->arr[j].type != 2)) {
                lR->arr[i].type = 2;
                lD->arr[j].type = 2;
                break;
            }
        }
    }
}

void findResBin(TPEOPLE_ARRAY *lR, TPEOPLE_ARRAY *lD) {

    for (size_t i = 0; i < lR->n; ++i) {

        TPERSON *res = (TPERSON *) bsearch(&(lR->arr[i]), lD->arr, lD->n, sizeof(TPERSON), cmpFn2);

        if (res == NULL) {
            continue;
        }
        if (res == &lD->arr[0] && (lR->arr[i].type != 2 && res->type != 2)) {
            lR->arr[i].type = 2;
            res->type = 2;
            continue;
        } else {
            while (areSame(res, res - 1) == 1) {
                if (res == &lD->arr[0]) {
                    break;
                }
                res--;
            }
        }
        if (res != NULL && (lR->arr[i].type != 2 && res->type != 2)) {
            lR->arr[i].type = 2;
            res->type = 2;
        }
    }
}


void freeList(TPEOPLE_ARRAY *l) {
    for (size_t i = 0; i < l->n; ++i) {
        for (size_t j = 0; j < l->arr[i].n; ++j) {
            free(l->arr[i].names[j].name);
        }
        free(l->arr[i].originalName);
        free(l->arr[i].names);
    }
    free(l->arr);
}

int main(void) {

    TZKOUSKA zk = {};


    if (readInput(&zk) == -1) {
        printf("BAD\n");
        freeList(&zk.prisli);
        freeList(&zk.registrovany);
        return 1;
    }

    printList(&zk.registrovany);
    printList(&zk.prisli);

    printf("Po\n");
    qsort(zk.prisli.arr, zk.prisli.n, sizeof(TPERSON), cmpFn2);
    qsort(zk.registrovany.arr, zk.registrovany.n, sizeof(TPERSON), cmpFn2);
    printList(&zk.registrovany);
    printList(&zk.prisli);

    printf("Po findu:\n");
    findResBin(&zk.registrovany, &zk.prisli);
//    findRes(&listR, &listP);
    printList(&zk.registrovany);
    printList(&zk.prisli);

    printf("RESENI:\n");
    printRes(&zk.registrovany, &zk.prisli);

    freeList(&zk.registrovany);
    freeList(&zk.prisli);
    return 0;
}





