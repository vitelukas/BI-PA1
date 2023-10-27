#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define string char *

typedef struct TDick
{
    string name;
    int count;
} TDICK;

void printStringArr(string *array, int size)
{
    printf("vypis stringu:\n");
    for (int i = 0; i < size; i++)
    {
        printf("string: %s\n", array[i]);
    }
    return;
}

void printFullDick(TDICK *array, int size)
{
    printf("vypis dick:\n");
    for (int i = 0; i < size; i++)
    {
        printf("count %dx: %s\n", array[i].count, array[i].name);
    }
    return;
}

void printAnswer(TDICK *array, int size)
{
    int max = 0;
    for (int i = 0; i < size; i++)
    {
        if (array[i].count > max)
        {
            max = array[i].count;
        }
    }
    printf("Nejcastejsi jmeno: %dx\n", max);
    for (int i = 0; i < size; i++)
    {
        if (array[i].count == max)
        {
            printf("%s\n", array[i].name);
        }
    }
}

void freeStringArr(string *strArr, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(strArr[i]);
    }
    free(strArr);
}

void freeDickArr(TDICK *dickArr, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(dickArr[i].name);
    }
    free(dickArr);
}

string *splitLine(string line, int *strArrSize)
{
    if (line == NULL || line[0] == '\0' || line[0] == '\n')
    {
        return NULL;
    }
    int capacity = 1;
    string *stringArr = (string *)malloc(capacity * (sizeof(string *)));
    string lmao = strtok(line, " ");
    string tmpch = (string)malloc(strlen(lmao) + 1);
    strcpy(tmpch, lmao);
    stringArr[(*strArrSize)++] = tmpch;
    while (1)
    {
        if ((lmao = strtok(NULL, " ")) == NULL)
        {
            break;
        }
        if (*strArrSize == capacity)
        {
            capacity += 5;
            capacity *= 2;
            stringArr = (string *)realloc(stringArr, capacity * sizeof(string));
        }
        string tmpch2 = (string)malloc(strlen(lmao) + 1);
        strcpy(tmpch2, lmao);
        stringArr[(*strArrSize)++] = tmpch2;
    }
    printStringArr(stringArr, *strArrSize);
    return stringArr;
}

int arrayContains(string str, TDICK *dick, int dickSize)
{
    for (int i = 0; i < dickSize; i++)
    {
        if (strcmp(dick[i].name, str) == 0)
        {
            printf("Match found at index %d\n", i);
            return i;
        }
    }
    printf("Match not found\n");
    return -1;
}

TDICK *loadDick(int *size)
{
    printf("Jmena:\n");
    int capacity = 2;
    TDICK *array = (TDICK *)malloc(capacity * sizeof(TDICK));
    string line = NULL;
    size_t buffer = 1;
    int length = 0;
    while ((length = getline(&line, &buffer, stdin)) != -1)
    {
        int strArrSize = 0;
        string *stringArr = splitLine(line, &strArrSize);
        if (stringArr == NULL)
        {
            if (line != NULL)
            {
                free(line);
            }
            free(stringArr);
            return NULL;
        }
        for (int i = 0; i < strArrSize - 1; i++)
        {
            int arrayIndex = -1;
            if ((arrayIndex = arrayContains(stringArr[i], array, *size)) == -1)
            {
                if (*size == capacity)
                {
                    capacity += 5;
                    capacity *= 2;
                    array = (TDICK *)realloc(array, capacity * sizeof(TDICK));
                }
                string name = (string)malloc(strlen(stringArr[i]) + 1);
                strcpy(name, stringArr[i]);
                TDICK tmp = {name, 1};
                array[(*size)++] = tmp;
            }
            else
            {
                array[arrayIndex].count++;
            }
        }
        freeStringArr(stringArr, strArrSize);
    }
    if (line != NULL)
    {
        free(line);
    }
    return array;
}

int main()
{
    int size = 0;
    TDICK *array = loadDick(&size);
    if (array == NULL)
    {
        printf("Nespravny vstup.\n");
        return 1;
    }
    printFullDick(array, size);
    printAnswer(array, size);
    freeDickArr(array, size);
    return 0;
}
