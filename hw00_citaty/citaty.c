#include <stdio.h>
#include <ctype.h>

int main (void) {

    int cislo = 0;

    printf("ml' nob:\n");

    while ( scanf(" %d", &cislo) == 1) {

        if  (getchar() !='\n') {
            printf("luj\n");
            return 1;
        }

        if (cislo == 1 ) {
            printf("Qapla'\nnoH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.\n");
            return 0;
        } else if (cislo == 2 ) {
            printf("Qapla'\nbortaS bIr jablu'DI' reH QaQqu' nay'.\n");
            return 0;
        } else if (cislo == 3 ) {
            printf("Qapla'\nQu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.\n");
            return 0;
        } else if (cislo == 4 ) {
            printf("Qapla'\nbISeH'eghlaH'be'chugh latlh Dara'laH'be'.\n");
            return 0;
        } else if (cislo == 5 ) {
            printf("Qapla'\nqaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.\n");
            return 0;
        } else if (cislo == 6 ) {
            printf("Qapla'\nSuvlu'taHvIS yapbe' HoS neH.\n");
            return 0;
        } else if (cislo == 7 ) {
            printf("Qapla'\nHa'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.\n");
            return 0;
        } else if (cislo == 8 ) {
            printf("Qapla'\nHeghlu'meH QaQ jajvam.\n");
            return 0;
        } else if (cislo == 9 ) {
            printf("Qapla'\nleghlaHchu'be'chugh mIn lo'laHbe' taj jej.\n");
            return 0;
        } else {
            printf("luj\n");
            return 1;
        }
    }

    if ( ! feof (stdin)) {
        printf("luj\n");
        return 1;
    }

    /*
    while ( scanf(" %d", &cislo) !=1 || cislo<1 || cislo>9 ) {
        printf("luj\n");
        while (getchar() != '\n') {}
    } */ // Moznost s opakovanim vstupu pri spatny odpovedi.

    return 0;
}