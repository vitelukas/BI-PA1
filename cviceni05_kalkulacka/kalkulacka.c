#include <stdio.h>
#include <math.h>

int main (void) {

    long  double a = 0, b = 0, vysledek = 0;
    char operace, rovnase;

    printf("Zadejte vzorec:\n");
    if (scanf(" %Lf %c %Lf %c", &a, &operace, &b, &rovnase) != 4 || (rovnase != '=') ) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    switch (operace) {
        case '+':
            vysledek = a + b;
            break;
        case '-':
            vysledek = a - b;
            break;
        case '*':
            vysledek = a * b;
            break;
        case '/':
            if (b == 0) {
                printf("Nespravny vstup.\n");
                return 1;
            } else {
                (vysledek = a / b);
                vysledek = truncl(vysledek);    // trunc rounds the number toward zero to the closest integer
            }
            break;
        default:
            printf("Nespravny vstup.\n");
            return 1;
    }

    printf("%Lg\n", vysledek);

    return 0;
}