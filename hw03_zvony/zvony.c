#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */


// Decides whether the given year is leap or not --> this decides if February has 28 or 29 days
int leapYear (int y) {
    if ( y % 4 == 0
         && ( y % 100 != 0 || (y % 400 == 0 && y % 4000 != 0 ) ) ) {
        return 1; // Is leap year
    } else {
        return 0;
    }
}

/*
int year (int y) {

}
*/

// If number of month is even it has 30 days, if it's odd it has 31 days --> this changes after 7th month
// If the month is July, it has 28(non leap year) or 29(leap year) days
int month (int m, int y) {
    int daysAmmount=0;
    if ( (m < 7) && (m % 2 == 0) ) {
        daysAmmount = 30;
    } else if ( (m > 7) && (m % 2 == 0) ) {
        daysAmmount = 31;
    }
    if (m == 2) {
        if (leapYear(y)) {
            daysAmmount = 29;
        } else {
            daysAmmount = 28;
        }
    }
    return daysAmmount;
}

int monthDiff (int y1, int m1, int m2, int d1, int d2) {
    int monthDiffDays=0;

    if (d2 < d1) {
        for (int i = m1; i < m2 - 1; i++) {
            if (month(m1, y1) == 31) {
                monthDiffDays += 31;
            } else if (month(m1, y1) == 30) {
                monthDiffDays += 30;
            } else if (month(m1, y1) == 29) {
                monthDiffDays += 29;
            } else {
                monthDiffDays += 28;
            }
        }
    } else {
        for (int i = m1; i < m2; i++) {
            if (month(m1, y1) == 31) {
                monthDiffDays += 31;
            } else if (month(m1, y1) == 30) {
                monthDiffDays += 30;
            } else if (month(m1, y1) == 29) {
                monthDiffDays += 29;
            } else {
                monthDiffDays += 28;
            }
        }
    }

    return monthDiffDays;
}

/*
int day (int d) {
    ...
}
*/

// Returns the amount of bell rings to the calling function
// h == amount of bell rings
int hour (int h) {
    if (h > 12) { // Set afternoon hours to work the same as morning hours --> bell rings only 1x at 13:00pm, 2x at 14:00pm etc.
        h = h - 12;
    } else if (h == 0) {
        h = 12;
    }
    return h;
}

// i == starting amount of bell1 rings
int minute (int i) {
    if ((i>=0) && (i<15)) {
        i = 4;
        return i;
    } else if ((i>=15) && (i<30)) {
        i = 1;
        return i;
    } else if ((i>=30) && (i<45)) {
        i = 2;
        return i;
    } else if ((i>=45) && (i<60)) {
        i = 3;
        return i;
    } else {
        return 0;
    }
}

int bells ( int y1, int m1, int d1, int h1, int i1,
            int y2, int m2, int d2, int h2, int i2,
            long long int * b1, long long int * b2 )
{
    int months, days, hours, minutes, daysDiff = 0, Sundays;

    /*
    years = y2-y1;
    months = m2 - m1;
    */

    days = ((y2-y1) * 365);
    if (d2 < d1) {                          //Counts days if it overflows into the next month
        for ( int i = d2; i < d1 ; i--) {
            if (i==1) {
                i = month(m2-1, y2);
                d2 = month(m2-1, y2);
            }
            daysDiff += 1;
        }
        days += (d2-d1) + daysDiff + monthDiff(y1, m1, m2, d1, d2);
    }
    else {
        days += (d2-d1) + monthDiff(y1, m1, m2, d1, d2);
    }

    /*
    if (years >= 1) {
        months = fabs();
    } else {
        months = m2-m1;
    }
    */ //If given interval is bigger than 1 year



    * b1= 240 * days;
    * b2 = 156 * days;

    return 1;

}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  long long int b1, b2;

  assert ( bells ( 2022, 10,  1, 13, 15,
                   2022, 10,  1, 18, 45, &b1, &b2 ) == 1
           && b1 == 56
           && b2 == 20 );
  assert ( bells ( 2022, 10,  3, 13, 15,
                   2022, 10,  4, 11, 20, &b1, &b2 ) == 1
           && b1 == 221
           && b2 == 143 );
  assert ( bells ( 2022, 10,  1, 13, 15,
                   2022, 10,  2, 11, 20, &b1, &b2 ) == 1
           && b1 == 106
           && b2 == 65 );
  assert ( bells ( 2022, 10,  2, 13, 15,
                   2022, 10,  3, 11, 20, &b1, &b2 ) == 1
           && b1 == 115
           && b2 == 78 );
  assert ( bells ( 2022, 10,  1, 13, 15,
                   2022, 10,  3, 11, 20, &b1, &b2 ) == 1
           && b1 == 221
           && b2 == 143 );
  assert ( bells ( 2022,  1,  1, 13, 15,
                   2022, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 56861
           && b2 == 36959 );
  assert ( bells ( 2019,  1,  1, 13, 15,
                   2019, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 57101
           && b2 == 37115 );
  assert ( bells ( 2024,  1,  1, 13, 15,
                   2024, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 57341
           && b2 == 37271 );
  assert ( bells ( 1900,  1,  1, 13, 15,
                   1900, 10,  5, 11, 20, &b1, &b2 ) == 1
           && b1 == 57101
           && b2 == 37115 );
  assert ( bells ( 2022, 10,  1,  0,  0,
                   2022, 10,  1, 12,  0, &b1, &b2 ) == 1
           && b1 == 124
           && b2 == 90 );
  assert ( bells ( 2022, 10,  1,  0, 15,
                   2022, 10,  1,  0, 25, &b1, &b2 ) == 1
           && b1 == 1
           && b2 == 0 );
  assert ( bells ( 2022, 10,  1, 12,  0,
                   2022, 10,  1, 12,  0, &b1, &b2 ) == 1
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2022, 11,  1, 12,  0,
                   2022, 10,  1, 12,  0, &b1, &b2 ) == 0
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2022, 10, 32, 12,  0,
                   2022, 11, 10, 12,  0, &b1, &b2 ) == 0
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2100,  2, 29, 12,  0,
                   2100,  2, 29, 12,  0, &b1, &b2 ) == 0
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2000,  2, 29, 12,  0,
                   2000,  2, 29, 12,  0, &b1, &b2 ) == 1
           && b1 == 4
           && b2 == 12 );
  assert ( bells ( 2004,  2, 29, 12,  0,
                   2004,  2, 29, 12,  0, &b1, &b2 ) == 1
           && b1 == 0
           && b2 == 0 );
  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
