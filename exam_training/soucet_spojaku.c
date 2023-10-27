#ifndef __PROGTEST__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

typedef struct TItem {
    struct TItem * m_Next;
    char m_Digit;
} TITEM;

TITEM * createItem(char digit, TITEM * next) {
    TITEM *n = (TITEM *) malloc(sizeof(*n));
    n->m_Digit = digit;
    n->m_Next = next;
    return n;
}

void deleteList(TITEM * l) {
    while (l) {
        TITEM *tmp = l->m_Next;
        free(l);
        l = tmp;
    }
}

#endif /* __PROGTEST__ */

void printList(TITEM *final) {
    while(final) {
        printf("%c %s ", final->m_Digit, final->m_Next ? "->" : "");
        final = final->m_Next;
    }
    printf("\n");
}

int validityCheck(TITEM *a, TITEM *b) {
    int tmp = '1', flag = 0;

    while( a != NULL ) {
        if( a->m_Digit > 57 || a->m_Digit < 48 ) {
            return 0;
        }
        if( a->m_Digit == '0') {
            if(tmp == '0') {
                flag = 1;
            } else {
                tmp = '0';
            }
        } else {
            flag = 0;
            tmp = '1';
        }
        a = a->m_Next;
    }
    if (flag) return 0;
    tmp = '1';
    flag = 0;
    while( b != NULL ) {
        if( b->m_Digit > 57 || b->m_Digit < 48 ) {
            return 0;
        }
        if( b->m_Digit == '0') {
            if(tmp == '0') {
                flag = 1;
            } else {
                tmp = '0';
            }
        } else {
            flag = 0;
            tmp = '1';
        }
        b = b->m_Next;
    }
    return (flag == 1 ?  0 :  1);
}

TITEM * addList ( TITEM * a, TITEM * b ) {  //TODO zajistit, ze spojak nekonci na nuly
    TITEM *final = createItem('0', NULL);
    TITEM *head = final;
    TITEM *aHelp = a, *bHelp = b;
    int aNum, bNum, sum = 0, remainder = 0;
    if (aHelp == NULL || bHelp == NULL) {   // Validity check
        return NULL;
    }
    if( validityCheck(aHelp, bHelp) == 0 ) {
        return NULL;
    }

    while( (aHelp != NULL || bHelp != NULL) || remainder ) {
        aNum = bNum = '0';
        if(aHelp) {
            aNum = aHelp->m_Digit;
        }
        if(bHelp) {
            bNum = bHelp->m_Digit;
        }

        sum = (aNum + bNum ) - '0' + remainder;
        remainder = 0;

        if(sum > 57) {
            sum -= 10;
            remainder = 1;
        }
        final->m_Digit = sum;

        if(remainder) {
            final->m_Next = createItem('0', NULL);
            final = final->m_Next;
        } else {
            if( aHelp ) {
                if( aHelp->m_Next ) {
                    final->m_Next = createItem('0', NULL);
                    final = final->m_Next;
                }
            } else if( bHelp ) {
                final->m_Next = createItem('0', NULL);
                final = final->m_Next;
            }
        }
        if(aHelp) aHelp = aHelp->m_Next;
        if(bHelp) bHelp = bHelp->m_Next;
    }
    //printList(head);
    return head;
}

#ifndef __PROGTEST__

int main(int argc, char *argv[]) {
    TITEM * a, * b, * res;

    a = createItem('x', NULL);
    b = createItem('3', NULL);
    res = addList(a, b);
    assert (res == NULL);
    deleteList(a);
    deleteList(b);

    a = createItem('5',
                   createItem('0',
                              createItem('0', NULL)));
    b = createItem('3', NULL);
    res = addList(a, b);
    assert (res == NULL);
    deleteList(a);
    deleteList(b);

    a = createItem('3',
                   createItem('4',
                              createItem('5', NULL)));
    b = createItem('0', NULL);
    res = addList(a, b);
    assert (res->m_Digit == '3');
    assert (res->m_Next->m_Digit == '4');
    assert (res->m_Next->m_Next->m_Digit == '5');
    assert (res->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);

    a = createItem('2', createItem('3', createItem('3', NULL)));
    b = createItem('5', createItem('3', createItem('1', NULL)));
    res = addList(a, b);
    assert (res->m_Digit == '7');
    assert (res->m_Next->m_Digit == '6');
    assert (res->m_Next->m_Next->m_Digit == '4');
    assert (res->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);

    a = createItem('2', createItem('3', createItem('9', NULL)));
    b = createItem('5', createItem('3', createItem('1', createItem('9', createItem('2', createItem('6', createItem('1', NULL)))))));
    res = addList(a, b);
    assert (res->m_Digit == '7');
    assert (res->m_Next->m_Digit == '6');
    assert (res->m_Next->m_Next->m_Digit == '0');
    assert (res->m_Next->m_Next->m_Next->m_Digit == '0');
    assert (res->m_Next->m_Next->m_Next->m_Next->m_Digit == '3');
    assert (res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Digit == '6');
    assert (res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Digit == '1');
    assert (res->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next->m_Next == NULL);
    deleteList(res);
    deleteList(a);
    deleteList(b);
    return 0;
}

#endif /* __PROGTEST__ */