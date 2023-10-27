#ifndef __PROGTEST__
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>
#endif /* __PROGTEST__ */

//---------------------------------------------------------------------------------------------

/*
 * Urceni jednoznacnosti seznamu
 * Kdyz se v seznamu vyskytuje slovo, ktere je prefixem nektereho jineho slova v tabulce --> vrati 0 == neplatna tabulka
 */
int validityOfList ( const char * (*replace)[2] ) {
    int row = 0, rowIndex = 0;

    while (replace[row][0] != NULL) {
        const char *expression = replace[row][0];
        rowIndex = 0;
        while (replace[rowIndex][0] != NULL) {
            const char *control = strstr(replace[rowIndex][0], expression);
            if ( control != NULL) {
                if ( strcmp(control, replace[rowIndex][0]) == 0 ) {
                    if (rowIndex != row) {
                        return 0;    // --> Seznam neni jednoznacny
                    }
                }
            }
            rowIndex++;
        }
        row++;
    }
    return 1;
}

//---------------------------------------------------------------------------------------------

char * newSpeak ( const char * text, const char * (*replace)[2] ) {
    int row = 0,
            i = 0,
            j = 0,
            old_lenght = 0,
            currentSize = 0,
            capacity = 15,
            lenghtOfNewString = 0,
            doNotAdd = 0,
            new_lenght = 0;

    // Kontrola validity seznamu pro nahrazovani slov
    if (validityOfList(replace) == 0) {
        return NULL;
    }

    char *replacedText = (char*) malloc( capacity * sizeof(char) );
    char *textOrigin = strdup(text);          // Vytvoreni pomocneho stringu, do ktereho je nakopirovany puvodni text -> pro snadnejsi manipulaci se stringem
    int textOriginLenght = strlen(textOrigin);

    // Precti cely puvodni string, char po charu, dokud nenarazis na konec stringu
    while ( i < textOriginLenght+1 ) {
        int helpVar = 1;
        row = 0;

        // Pro kazdy jeden char zkontroluj, jestli se na danem miste(urcuje index i) vyskytuje nektery ze stringu, ktery mame nahradit
        // Kdyz najdeme na danem miste string --> helpVar = 0 --> ukonceni vnoreneho cyklu while
        // --> posunuti indexu o odpovidajici delku stringu
        while (helpVar) {
            doNotAdd = 0;
            const char *oldString = replace[row][0];
            const char *newString = replace[row][1];
            old_lenght = strlen(oldString);
            new_lenght = strlen(newString);
            lenghtOfNewString = new_lenght;
            while ( ( currentSize + lenghtOfNewString ) >= capacity) {
                capacity = capacity * 2;
                replacedText = (char*) realloc(replacedText, ( capacity ) * sizeof(char) );
            }
            if (strstr(&textOrigin[i], oldString) == &textOrigin[i]) {
                strcpy(&replacedText[j], newString);
                i += old_lenght;
                j += lenghtOfNewString;
                currentSize += new_lenght;
                helpVar = 0;
                doNotAdd = 1;   // Pomocna promena, ktera zajistuje, ze pokud se nahrazovany string nachazi uplne na konci seznamu,
                                // tak k indexu pricteme pouze delku daneho stringu a uz k indexu dale nepricitame +1, viz pozn. nize ↓↓
            }
            row++;
            if (doNotAdd == 0 ) {
                // Kdyz dojdeme v seznamu az na posledni radku(NULL) a jeste jsme nenasli zadne slovo ze seznamu, ktere by se na aktualni pozici nachazelo
                // --> pricti k aktualnimu indexu +1 a zkopiruj dany char, na kterem se zrovna nachazime, z originalniho textu do nahrazovaneho textu
                if (replace[row][0] == NULL) {
                    replacedText[j] = textOrigin[i];
                    i++;
                    j++;
                    currentSize++;
                    helpVar = 0;
                }
            }
        }
    }
    replacedText[j] = '\0';

    free(textOrigin);
    return replacedText;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    char * res;

    const char * d1 [][2] =
            {
                    { "murderer", "termination specialist" },
                    { "failure", "non-traditional success" },
                    { "specialist", "person with certified level of knowledge" },
                    { "dumb", "cerebrally challenged" },
                    { "teacher", "voluntary knowledge conveyor" },
                    { "evil", "nicenest deprived" },
                    { "incorrect answer", "alternative answer" },
                    { "student", "client" },
                    { NULL, NULL }
            };

    const char * d2 [][2] =
            {
                    { "fail", "suboptimal result" },
                    { "failure", "non-traditional success" },
                    { NULL, NULL }
            };

    res = newSpeak ( "Everybody is happy.", d1 );
    assert ( ! strcmp ( res, "Everybody is happy." ) );
    free ( res );

    res = newSpeak ( "The student answered an incorrect answer.", d1 );
    assert ( ! strcmp ( res, "The client answered an alternative answer." ) );
    free ( res );

    res = newSpeak ( "He was dumb, his failure was expected.", d1 );
    assert ( ! strcmp ( res, "He was cerebrally challenged, his non-traditional success was expected." ) );
    free ( res );

    res = newSpeak ( "The evil teacher became a murderer.", d1 );
    assert ( ! strcmp ( res, "The nicenest deprived voluntary knowledge conveyor became a termination specialist." ) );
    free ( res );

    res = newSpeak ( "Devil's advocate.", d1 );
    assert ( ! strcmp ( res, "Dnicenest deprived's advocate." ) );
    free ( res );

    res = newSpeak ( "Hello.", d2 );
    assert ( ! res );

    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */

