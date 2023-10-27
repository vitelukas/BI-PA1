#include <stdio.h>
#include <math.h>

int main (void) {

    double kreditniUrok, debetniUrok;
    int den = 0, puvodniDen = 0, castka = 0, zustatek=0, puvodniZustatek=0;

    zustatek *= 100;

    printf("Zadejte kreditni urok [%%]:\n");
    if (scanf("%lf", &kreditniUrok) !=1) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Zadejte debetni urok [%%]:\n");
    if (scanf("%lf", &debetniUrok) !=1) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Zadejte transakce:\n");
    do {
        if (scanf("%d, %d", &den, &castka) !=2 || (den<puvodniDen) ) {  /* If days aren't in ascensional order the program crashes */
            printf("Nespravny vstup.\n");
            return 1;
        }

        /* Decides if given amount is positive or negative and adds its ammount to the balance */
        if (zustatek>0) {
            for ( int i = puvodniDen; i < den; i++) {
                zustatek = zustatek * (1 + (kreditniUrok/100));
            }
        } else {
            for ( int i = puvodniDen; i < den; i++) {
                zustatek = zustatek * (1 + (debetniUrok/100));
            }
        }
        puvodniZustatek = zustatek;
        zustatek = puvodniZustatek + castka*100;
        puvodniDen = den;

    } while (castka !=0);

    printf("Zustatek: %.2f\n", (double)zustatek/100);

    return 0;
}