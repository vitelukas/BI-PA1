#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REG_PLATE_LENGHT 10

//----------------------------------------------------------------------------------------------------------------------
typedef struct parkingPlace {
    char RP[REG_PLATE_LENGHT];
    int parking;
}TPARKINGPLACE;

typedef struct building {
    TPARKINGPLACE **data;
    int floors;
    int places;
}TBUILDING;

//----------------------------------------------------------------------------------------------------------------------
int initGarage(TBUILDING *garage);

int readInput(TBUILDING *garage);

int parkingRequest(TBUILDING *garage);

int leavingRequest(TBUILDING *garage);

//----------------------------------------------------------------------------------------------------------------------
int main(void) {
    TBUILDING garage;

    if ( initGarage(&garage) == 0) {
        printf("Nespravny vstup\n");
        return 0;
    }

    if ( readInput(&garage) == 0 ) {
        printf("Nespravny vstup\n");
        return 0;
    }

    return 0;
}

//----------------------------------------------------------------------------------------------------------------------
int initGarage(TBUILDING *garage) {
    printf("Velikost:\n");
    if( scanf(" %d %d", &garage->floors, &garage->places) !=2
        || garage->floors < 0 || garage->places < 0) {
        return 0;
    }
    garage->data = (TPARKINGPLACE**) malloc(garage->floors * sizeof(TPARKINGPLACE));
    for(int i = 0; i < garage->floors; i++) {
        garage->data[i] = (TPARKINGPLACE*) malloc (garage->places * sizeof(TPARKINGPLACE));
    }
    return 1;
}

int readInput(TBUILDING *garage){
    char request;
    int loaded;

    printf("Pozadavky:\n");
    while( (loaded = scanf(" %c", &request)) == 1 ) {
        if (request != '+' && request != '-') {
            return 0;
        }
        if (request == '+') {
            if (parkingRequest(garage) == 0) {
                return 0;
            }
        } else {
            leavingRequest(garage);
        }
    }
    if(!feof(stdin) && loaded !=1  && loaded != -1) {
        return 0;
    }

    return 1;
}

int parkingRequest(TBUILDING *garage) {
    char carPlate[11];
    int floor, place;

    if( scanf(" %d %d %10s", &floor, &place, carPlate) != 3
        || floor >= garage->floors || place >= garage->places ) {
        return 0;
    }

    if( garage->data[floor][place].parking != 0 ) {
        printf("Obsazeno %s\n", garage->data[floor][place].RP );
        return 1;
    } else{
        garage->data[floor][place].parking = 1;
        strcpy(garage->data[floor][place].RP, carPlate);
        printf("OK\n");
    }
    return 1;
}

int leavingRequest(TBUILDING *garage) {
    char carPlate[11];

    if( scanf(" %10s", carPlate) != 1 ) {
        return 0;
    }
    for (int i = 0; i < garage->floors; ++i) {
        for (int j = 0; j < garage->places; ++j) {
            if(strcmp(carPlate, garage->data[i][j].RP) == 0) {
                garage->data[i][j].parking = 0;
                garage->data[i][j].RP[0] = '\0';
                printf("OK\n");
                return 1;
            }
        }
    }
    printf("Nenalezeno\n");
    return 0;
}