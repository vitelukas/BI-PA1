#include <stdio.h>
#include <math.h>
#include <float.h>

// Porovna, jestli jsou si obe strany rovnice rovny ( a == b ) --> return 1 do volajici fce, kdyz ano
int equal (double a, double b) {
    return (fabs(a-b) <= 100 * DBL_EPSILON * fabs(b) );
}

// Zjisti, jestli je sklon dvojice dvou libovolnych bodu je stejny --> pokud ano, body lezi na stejne primce --> return 1
int slope (double xa, double ya, double xb, double yb, double xc, double yc) {
    double AB = (yb - ya) / (xb - xa);
    double BC = (yc - yb) / (xc - xb);
    return (equal(AB, BC) || (equal(xa, xb) && equal(xa, xc)) || (equal(ya, yb) && equal(ya, yc)));
}

int splyvaji (double xa, double ya, double xb, double yb, double xc, double yc) {
    return ( ((xa==xb) && (ya==yb)) || ((xa==xc) && (ya==yc)) || ((xb==xc) && (yb==yc)) );
}

// Urci prostredni bod a vrati ho volajici funkci
int prostredni (double xa, double ya, double xb, double yb, double xc, double yc) {
    double A = xa + ya;
    double B = xb + yb;
    double C = xc + yc;
    char bod=A;

    if ( B < A && A < C ) {
        bod='A';
    } else if ( C < A && A < B) {
        bod='A';
    } else if ( A < B && B < C ) {
        bod='B';
    } else if ( C < B && B < A ) {
        bod='B';
    } else if ( A < C && C < B ) {
        bod='C';
    } else if ( B < C && C < A ) {
        bod='C';
    }

    return bod;
}


int main (void) {

    double xa, ya, xb, yb, xc, yc;
    xa = ya = xb = yb = xc = yc = 0;

    printf("Bod A:\n");
    if (scanf(" %lf %lf", &xa, &ya) !=2) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Bod B:\n");
    if (scanf(" %lf %lf", &xb, &yb) !=2) {
        printf("Nespravny vstup.\n");
        return 1;
    }

    printf("Bod C:\n");
    if ( scanf(" %lf %lf", &xc, &yc) !=2) {
        printf("Nespravny vstup.\n");
        return 1;
    }


// 3 ruzne typy reseni

// Reseni 1: body splyvaji
    if ( splyvaji(xa/10,ya/10,xb/10,yb/10,xc/10,yc/10) ) {
        printf("Nektere body splyvaji.\n");
        return 0;
    }
// Reseni 2: Body lezi na jedne primce
    if ( slope(xa/10,ya/10,xb/10,yb/10,xc/10,yc/10) ) {
        printf("Body lezi na jedne primce.\n");
        printf("Prostredni je bod %c.\n", prostredni(xa/10,ya/10,xb/10,yb/10,xc/10,yc/10));
        return 0;
    } else {    // Reseni 3: Body nesplyvaji, ale ani nelezi na jedne primce
        printf("Body nelezi na jedne primce.\n");
        return 0;
    }

    return 0;
}