#include <stdio.h>

int main (void) {

    int x, y, z = 0;
    char zavorka;

    printf("Zadejte barvu v RGB formatu:\n");

    if (scanf(" rgb ( %d , %d , %d %c", &x, &y, &z, &zavorka)
           != 4 || zavorka != ')' || ((x | y | z) < 0) || ((x | y | z) > 255)) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    /*
    while (scanf(" rgb ( %d , %d , %d %c", &x, &y, &z, &zavorka)
           != 4 || zavorka != ')' || ((x | y | z) < 0) || ((x | y | z) > 255)) {
        printf("Nespravny vstup.\n");
        while (getchar() != '\n') {}
    } */ //Moznost s opakovanim pri spatnym vstupu

    if (getchar() != '\n') {
        printf("Nespravny vstup.\n");
    }

    printf("#%02X%02X%02X\n", x, y, z);

    return 0;
}