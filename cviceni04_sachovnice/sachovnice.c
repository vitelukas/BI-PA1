#include <stdio.h>

int main (void) {

    int pocet=0, velikost=0, sloupecSachovnice=0, radekSachovnice=0;

    printf("Zadejte pocet poli:\n");
    if (scanf("%d", &pocet) !=1 || (pocet <= 0)) {
        printf("Nespravny vstup.\n");
        return 1;
    }
    printf("Zadejte velikost pole:\n");
    if (scanf("%d", &velikost) !=1 || (velikost <= 0)) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("+");
    for (int sloupec = 0; sloupec < pocet * velikost; ++sloupec) {
        printf("-");
    }
    printf("+\n");


    for (int sloupec = 0; sloupec < pocet * velikost; ++sloupec) {
        sloupecSachovnice = sloupec / velikost;
        printf("|");
        for (int radek = 0; radek < pocet * velikost; ++radek) {
            radekSachovnice = radek / velikost;
            if (radekSachovnice % 2 == 0 && sloupecSachovnice % 2 == 0) {
                printf(" ");
            }
            if (radekSachovnice % 2 == 0 && sloupecSachovnice % 2 == 1) {
                printf("X");
            }
            if (radekSachovnice % 2 == 1 && sloupecSachovnice % 2 == 0) {
                printf("X");
            }
            if (radekSachovnice % 2 == 1 && sloupecSachovnice % 2 == 1) {
                printf(" ");
            }
        }
        printf("|\n");
    }

    printf("+");
    for (int sloupec = 0; sloupec < pocet * velikost; ++sloupec) {
        printf("-");
    }
    printf("+\n");


    return 0;
}
