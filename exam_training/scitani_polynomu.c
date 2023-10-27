#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct TItem
{
    struct TItem * m_Next;
    int m_Mul;
    int m_Pow;
} TITEM;

TITEM * createItem ( int mul, int pow, TITEM * next )
{
    TITEM * n = (TITEM *) malloc (sizeof ( *n ));
    n -> m_Mul = mul;
    n -> m_Pow = pow;
    n -> m_Next = next;
    return n;
}

void deleteList (TITEM * l)
{
    while (l)
    {
        TITEM * tmp = l -> m_Next;
        free (l);
        l = tmp;
    }
}
#endif /* __PROGTEST__ */

void printList(TITEM *l) {
    while (l) {
        printf("%d^%d %s", l->m_Mul, l->m_Pow, l->m_Next ? "-> " : "");
        l = l->m_Next;
    }
    printf("\n");
}

int validityCheck(TITEM *a, TITEM *b) {
    int prev = a->m_Pow;
    int numOfNode = 0;

    if(numOfNode == 0 && a->m_Pow == 0 && a->m_Mul == 0 && a->m_Next != NULL) {
        return 0;
    }
    if(numOfNode == 0 && b->m_Pow == 0 && b->m_Mul == 0 && b->m_Next != NULL) {
        return 0;
    }

    while(a) {
        if(numOfNode) {
            if(a->m_Pow == 0 && a->m_Mul == 0) {
                return 0;
            }
        }
        if( prev >= a->m_Pow && numOfNode) return 0;
        prev = a->m_Pow;
        a = a->m_Next;
        numOfNode++;
    }
    numOfNode = 0;
    while(b) {
        if(numOfNode) {
            if(b->m_Pow == 0 && b->m_Mul == 0) {
                return 0;
            }
        }
        if( prev >= b->m_Pow && numOfNode) return 0;
        prev = b->m_Pow;
        b = b->m_Next;
        numOfNode++;
    }
    return 1;
}

TITEM * addPoly ( TITEM * a , TITEM * b )
{
    if( a == NULL || b == NULL ) {
        return NULL;
    }
    if ( !validityCheck(a, b) ) {
        return NULL;
    }
    int numSum = 0;

    if( a->m_Pow == 0 && a->m_Mul == 0 ) {
        TITEM *head = createItem(0,0,NULL);
        TITEM *final = head;
        while (b) {
            final->m_Mul = b->m_Mul;
            final->m_Pow = b->m_Pow;
            if(b->m_Next) {
                final->m_Next = createItem(0, 0, NULL);
                final = final->m_Next;
                b = b->m_Next;
            } else {
                return head;
            }
        }
        return head;
    } else if (b->m_Pow == 0 && b->m_Mul == 0) {
        TITEM *head = createItem(0,0,NULL);
        TITEM *final = head;
        while (a) {
            final->m_Mul = a->m_Mul;
            final->m_Pow = a->m_Pow;
            if(a->m_Next) {
                final->m_Next = createItem(0, 0, NULL);
                final = final->m_Next;
                a = a->m_Next;
            } else {
                return head;
            }
        }
        return head;
    }
    TITEM *head = createItem(0,0,NULL);
    TITEM *final = head;
    int numOfNode = 0;
    while ( a || b ) {
        if(!a) {
            if(numOfNode) {
                final->m_Next = createItem(0, 0, NULL);
                final = final->m_Next;
            }
            final->m_Pow = b->m_Pow;
            final->m_Mul = b->m_Mul;
            b = b->m_Next;
            numOfNode++;
        } else if(!b){
            if(numOfNode) {
                final->m_Next = createItem(0, 0, NULL);
                final = final->m_Next;
            }
            final->m_Pow = a->m_Pow;
            final->m_Mul = a->m_Mul;
            a = a->m_Next;
            numOfNode++;
        } else if(a->m_Pow == b->m_Pow) {
            numSum = a->m_Mul + b->m_Mul;

            if(numSum == 0) {
                a = a->m_Next;
                b = b->m_Next;
            } else {
                if(numOfNode) {
                    final->m_Next = createItem(0, 0, NULL);
                    final = final->m_Next;
                }
                final->m_Pow = a->m_Pow;
                final->m_Mul = numSum;

                a = a->m_Next;
                b = b->m_Next;
                numOfNode++;
            }
        } else if(a->m_Pow < b->m_Pow) {
            if(numOfNode) {
                final->m_Next = createItem(0, 0, NULL);
                final = final->m_Next;
            }
            final->m_Pow = a->m_Pow;
            final->m_Mul = a->m_Mul;

            a = a->m_Next;
            numOfNode++;
        } else if(b->m_Pow < a->m_Pow) {
            if(numOfNode) {
                final->m_Next = createItem(0, 0, NULL);
                final = final->m_Next;
            }
            final->m_Pow = b->m_Pow;
            final->m_Mul = b->m_Mul;

            b = b->m_Next;
            numOfNode++;
        }
    }

    return head;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    TITEM * a, * b;
    TITEM * res;

    a = createItem (2,1,NULL);
    b = createItem (0,0,NULL);
    res = addPoly(a,b);
    assert ( res -> m_Mul == 2 );
    assert ( res -> m_Pow == 1 );
    assert ( res -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
    //printf("assert 1 ok\n");

    a = createItem (2,1,NULL);
    b = createItem (3,1,createItem (4,2,createItem (2,3,createItem(1,0,NULL))));
    res = addPoly(a,b);
    assert ( res == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
    //printf("assert 2 ok\n");

    a = createItem (2,1,NULL);
    b = createItem (3,1,createItem (4,1,NULL));
    res = addPoly(a,b);
    assert ( res == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
    //printf("assert 3 ok\n");

    a = createItem (3,0,createItem (2,1,createItem (9,3,NULL)));
    b = createItem (0,0,createItem (4,2,createItem (-1,3,NULL)));
    res = addPoly(a,b);
    assert ( res == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
    //printf("assert 4 ok\n");

    a = createItem (3,0,createItem (2,1,createItem (5,3,NULL)));
    b = createItem (-7,0,createItem (-2,1,createItem (-5,3,NULL)));
    res = addPoly(a,b);
    assert ( res -> m_Mul == -4 );
    assert ( res -> m_Pow == 0 );
    assert ( res -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
    //printf("assert 5 ok\n");

    a = createItem (3,1,createItem (-2,2,createItem (4,3,NULL)));
    b = createItem (-3,1,createItem (2,2,createItem (-4,3,NULL)));
    res = addPoly(a,b);
    assert ( res -> m_Mul == 0 );
    assert ( res -> m_Pow == 0 );
    assert ( res -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
    //printf("assert 6 ok\n");

    a = createItem (3,1,createItem (-2,2,createItem (4,3,NULL)));
    b = createItem (-3,1,createItem (2,2,createItem (-4,3,createItem (69,4,createItem (8,6,NULL)))));
    res = addPoly(a,b);
    assert ( res -> m_Mul == 69 );
    assert ( res -> m_Pow == 4 );
    assert ( res -> m_Next -> m_Mul == 8 );
    assert ( res -> m_Next -> m_Pow == 6 );
    assert ( res -> m_Next -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
    //printf("assert 8 ok\n");

    a = createItem (-3,1,createItem (2,2,createItem (-4,3,createItem (69,4,createItem (8,6,NULL)))));
    b = createItem (3,1,createItem (-2,2,createItem (4,3,NULL)));
    res = addPoly(a,b);
    assert ( res -> m_Mul == 69 );
    assert ( res -> m_Pow == 4 );
    assert ( res -> m_Next -> m_Mul == 8 );
    assert ( res -> m_Next -> m_Pow == 6 );
    assert ( res -> m_Next -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
    //printf("assert 9 ok\n");

    a = createItem (-3,1,createItem (2,2,createItem (-4,3,createItem (69,4,createItem (8,6,NULL)))));
    b = createItem (14,1,NULL);
    res = addPoly(a,b);
    assert ( res -> m_Mul == 11 );
    assert ( res -> m_Pow == 1 );
    assert ( res -> m_Next -> m_Mul == 2 );
    assert ( res -> m_Next -> m_Pow == 2 );
    assert ( res -> m_Next -> m_Next -> m_Mul == -4 );
    assert ( res -> m_Next -> m_Next -> m_Pow == 3 );
    assert ( res -> m_Next -> m_Next -> m_Next -> m_Mul == 69 );
    assert ( res -> m_Next -> m_Next -> m_Next -> m_Pow == 4 );
    assert ( res -> m_Next -> m_Next -> m_Next -> m_Next -> m_Mul == 8 );
    assert ( res -> m_Next -> m_Next -> m_Next -> m_Next -> m_Pow == 6 );
    assert ( res -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
    deleteList ( a );
    deleteList ( b );
    deleteList ( res );
    //printf("assert 10 ok\n");

    return 0;
}
#endif /* __PROGTEST__ */