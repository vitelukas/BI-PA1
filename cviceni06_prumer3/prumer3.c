#ifndef __PROGTEST__
#include <stdio.h>
#include <limits.h>
#include <assert.h>
#include <stdint.h>
#include <math.h>
#endif /* __PROGTEST__ */

long long avg3 ( long long a, long long b, long long c )
{
    long long prumer=0;
    if (a==LLONG_MAX || b==LLONG_MAX || c==LLONG_MAX) {
        prumer = LLONG_MAX;
    } else {
        prumer = (a+b+c)/3;
    }
    printf("%lld\n", prumer);
    return prumer;
}

#ifndef __PROGTEST__
int main (int argc, char * argv [])
{
  assert ( avg3 ( 1, 2, 3 ) == 2 );
  assert ( avg3 ( -100, 100, 30 ) == 10 );
  assert ( avg3 ( 1, 2, 2 ) == 1 );
  assert ( avg3 ( -1, -2, -2 ) == -1 );
  assert ( avg3 ( LLONG_MAX, LLONG_MAX, LLONG_MAX ) == LLONG_MAX );
  assert ( avg3 ( 9223372036854775800, 9223372036854775800, 9223372036854775800 ) == 9223372036854775800 );
  assert ( avg3 ( -4278251607398731776, -8934156317761273792, -2636318835240348672 ) == -5282908920133451413 );

  return 0;
}
#endif /* __PROGTEST__ */

