#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------------------------------------------------------------------------------
typedef struct node {
    int num;
    struct node *n_next;
}TNODE;

//----------------------------------------------------------------------------------------------------------------------
// Create a new node of a linked list (this function doesn't link the node to the linked list)
TNODE *createItem(int number, TNODE *nextItem) {
    TNODE *newItem = (TNODE *) malloc (sizeof(*newItem));
    newItem->num = number;
    newItem->n_next = nextItem;
    return newItem;
}

// Print the linked list
void printList(TNODE *l) {
    while(l) {
        printf("%d %s", l->num, l->n_next ? "-> " : "" );
        l = l->n_next;
    }
    printf("\n");
}

// Destroy(free) the whole linked list
void destroyList(TNODE *list) {
    if(list) {
        TNODE *tmp = list;
        while (list) {
            tmp = list->n_next;
            free(list);
            list = tmp;
        }
    }
}

// Send back the lenght of the linked list
int listLenght(TNODE *list){
    int lenght = 0;

    while(list) {
        lenght++;
        list = list->n_next;
    }

    return lenght;
}

// Insert an item at the beginning of the linked list
void push(int number, TNODE **head) {
    TNODE *newStart = createItem(number, NULL);
    newStart->n_next = *head;
    *head = newStart;
}

// Insert an item at the end of the linked list
void pushBack(int number, TNODE *list) {
    while(list->n_next){
        list = list->n_next;
    }

    TNODE *backItem = createItem(number, NULL);
    list->n_next = backItem;
}

// Delete the first element of a linked list
void deleteFirst(TNODE **head) {
    if (*head) {
        if((*head)->n_next) {
            TNODE *tmp = *head;
            *head = (*head)->n_next;
            free(tmp);
        } else {
            free((*head)->n_next);
            *head = NULL;
        }
    }
}

// Delete the first occurrence of a given element
void deleteElement(int number, TNODE **head_ref) {
    TNODE *temp = *head_ref, *prev;

    if (temp && temp->num == number) {
        *head_ref = temp->n_next;
        free(temp);
        return;
    }

    while (temp && temp->num != number) {
        prev = temp;
        temp = temp->n_next;
    }

    if (temp == NULL) {
        printf("Element %d is not in the list.\n", number);
        return;
    }

    prev->n_next = temp->n_next;
    free(temp);
}

// Delete the last node of the linked list
void deleteBottom(TNODE **head) {
    if(*head) {
        if((*head)->n_next == NULL) {
            free((*head)->n_next);
            *head = NULL;
        } else {
            TNODE *tmp = *head;
            TNODE *previous = NULL;
            while (tmp->n_next->n_next) {
                tmp = tmp->n_next;
            }
            previous = tmp;
            tmp = tmp->n_next;
            previous->n_next = NULL;
            free(tmp);
        }
    }
}

void insertElement(int position, int number, TNODE **head) {
    if(*head) {
        int numOfNode = 0;
        TNODE *tmp = *head;
        while(tmp && (numOfNode < position-2)) {
            tmp = tmp->n_next;
            numOfNode++;
        }
        if( (numOfNode == position - 2) && tmp) {
            if (tmp) {
                TNODE *newElement = createItem(number, NULL);
                newElement->n_next = tmp->n_next;
                tmp->n_next = newElement;
            } else {
                TNODE *newElement = createItem(number, NULL);
                tmp = newElement;
            }
        } else {
            printf("List is too short.\n");
        }
    }
}

void reverseList(TNODE **head) {
    if(*head) {
        if( (*head)->n_next) {
            TNODE *curr = (*head)->n_next->n_next;
            TNODE *prev = (*head)->n_next;
            (*head)->n_next = NULL;
            while (curr) {
                prev->n_next = *head;
                *head = prev;
                prev = curr;
                curr = curr->n_next;
            }
            prev->n_next = *head;
            free(curr);
            *head = prev;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------
int main(void) {
    printf("Vytvoreni noveho spojoveho seznamu:\n");
    TNODE *list = createItem(5, createItem(2, NULL));
    printList(list);

    printf("\nPridani prvku na konec seznamu:\n");
    pushBack(8, list);
    printList(list);

    printf("\nPridani prvku na zacatek seznamu:\n");
    push(42, &list);
    printList(list);

    printf("\nOdstraneni prvku x ze seznamu:\n");
    deleteElement(2, &list);
    printList(list);

    printf("\nOdstraneni posledniho prvku ze seznamu:\n");
    deleteBottom(&list);
    printList(list);

    printf("\nOdstraneni prvniho prvku ze seznamu:\n");
    deleteFirst(&list);
    printList(list);

    printf("\nVlozeni prvku do seznamu na pozici x:\n");
    insertElement(5,69,&list);
    printList(list);

    printf("\nOtoceni spojoveho seznamu:\n");
    reverseList(&list);
    printList(list);

    printf("Delka spojoveho seznamu = %d\n", listLenght(list));

    destroyList(list);
    return 0;
}
