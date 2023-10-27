#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 33

//----------------------------------------------------------------------------------------------------------------------
typedef struct student {
    char name[3][NAME_LEN];
    int status;
    int numOfNames;
}TSTUDENT;

typedef struct registeredStud {
    TSTUDENT *data;
    int capacity;
    int n;  // number of students
}TREGISTERED;

typedef struct presentStud {
    TSTUDENT *data;
    int capacity;
    int n;
}TPRESENT;

//----------------------------------------------------------------------------------------------------------------------
void readStudent(TREGISTERED *registeredStudents, TPRESENT *presentStudents, char letter, int *flag) {
    char newline;
    char name[35];
    int count = 0;

    if(letter == 'R') {
        while (scanf(" %33s%c", name, &newline) == 2 && registeredStudents->data[registeredStudents->n].numOfNames < 3) {
            if(registeredStudents->n >= registeredStudents->capacity) {
                registeredStudents->capacity *= 1.5;
                registeredStudents->data = (TSTUDENT*) realloc (registeredStudents->data, registeredStudents->capacity * sizeof(TSTUDENT) );
            }

            strcpy(registeredStudents->data[registeredStudents->n].name[count], name);

            count++;
            if (newline == '\n') break;
        }
        registeredStudents->data[registeredStudents->n].status = 1;
        registeredStudents->data[registeredStudents->n].numOfNames = count;
        registeredStudents->n += 1;
    } else {
        *flag = 1;
        while (scanf(" %33s%c", name, &newline) == 2 && presentStudents->data[presentStudents->n].numOfNames < 3) {
            if(presentStudents->n >= presentStudents->capacity) {
                presentStudents->capacity *= 1.5;
                presentStudents->data = (TSTUDENT*) realloc (presentStudents->data, presentStudents->capacity * sizeof(TSTUDENT) );
            }

            strcpy(presentStudents->data[presentStudents->n].name[count], name);

            count++;
            if (newline == '\n') break;
        }
        presentStudents->data[presentStudents->n].status = 1;
        presentStudents->data[presentStudents->n].numOfNames = count;
        presentStudents->n += 1;
    }
}

int isPresent(TREGISTERED *registeredStudents, TPRESENT *presentStudents, int i, int j) {
    if(registeredStudents->data[i].numOfNames == presentStudents->data[j].numOfNames) {
        int sameName;
        int names = registeredStudents->data[i].numOfNames;
        for (int k = 0; k < names; ++k) {
            sameName = 0;
            for (int l = 0; l < names; ++l) {
                if (strcasecmp(registeredStudents->data[i].name[k], presentStudents->data[j].name[l]) == 0) {
                    sameName = 1;
                }
            }
            if(!sameName) return 0;
        }
        if(presentStudents->data[j].status == 1) {
            presentStudents->data[j].status = 0;
            return 1;
        }
    }
    return 0;
}

int isRegistered(TREGISTERED *registeredStudents, TPRESENT *presentStudents, int i, int j) {
    if(registeredStudents->data[i].numOfNames == presentStudents->data[j].numOfNames) {
        int sameName;
        int names = registeredStudents->data[i].numOfNames;
        for (int k = 0; k < names; ++k) {
            sameName = 0;
            for (int l = 0; l < names; ++l) {
                if (strcasecmp(registeredStudents->data[i].name[k], presentStudents->data[j].name[l]) == 0) {
                    sameName = 1;
                }
            }
            if(!sameName) return 0;
        }
        if(registeredStudents->data[i].status == 1) {
            registeredStudents->data[i].status = 0;
            return 1;
        }
    }
    return 0;
}

void printStudents(TREGISTERED *registeredStudents, TPRESENT *presentStudents) {
    int flag;
    printf("\nNepritomni:\n");
    for(int i = 0; i < registeredStudents->n; ++i) {  // For each registered student
        flag = 0;
        for (int j = 0; j < presentStudents->n; ++j) {  // Check each present student
            if(isPresent(registeredStudents, presentStudents, i, j) == 1) {
                flag = 1;
                break;
            }
        }
        if(!flag) {
            printf("*");
            printf(" %s %s %s\n", registeredStudents->data[i].name[0], registeredStudents->data[i].name[1], registeredStudents->data[i].name[2]);
        }
    }

    printf("Bez registrace:\n");
    for(int i = 0; i < (presentStudents->n)-1; ++i) {  // For each registered student
        flag = 0;
        for (int j = 0; j < registeredStudents->n; ++j) {  // Check each present student
            if(isRegistered(registeredStudents, presentStudents, j, i) == 1) {
                flag = 1;
                break;
            }
        }
        if(!flag) {
            printf("*");
            printf(" %s %s %s\n", presentStudents->data[i].name[0], presentStudents->data[i].name[1], presentStudents->data[i].name[2]);
        }
    }
}


int readInput(TREGISTERED *registeredStudents, TPRESENT *presentStudents) {
    printf("Studenti:\n");
    int flag = 0;

    while( !feof(stdin) ) {
        char letter;
        int loaded;

        loaded = scanf(" %c:", &letter);
        if(loaded != -1) {
            if ( loaded != 1 || (letter != 'R' && letter != 'P') ) {
                return 0;
            }
        }

        if(letter == 'R' && flag) {
            return 0;
        } else {
            readStudent(registeredStudents, presentStudents, letter, &flag);
        }
    }

    printStudents(registeredStudents, presentStudents);

    return 1;
}


//----------------------------------------------------------------------------------------------------------------------
int main(void) {
    TREGISTERED registered;
    TPRESENT present;

    registered.n = 0;
    registered.capacity = 10;
    registered.data = (TSTUDENT*) malloc(registered.capacity * sizeof(TSTUDENT) );

    present.n = 0;
    present.capacity = 10;
    present.data = (TSTUDENT*) malloc(present.capacity * sizeof(TSTUDENT) );

    if( readInput(&registered, &present) == 0 ) {
        printf("Nespravny vstup\n");
        return 1;
    }

    return 0;
}