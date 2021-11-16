#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 1000000

typedef struct Date {
    int day;
    int month;
    int year;
} Date;

bool isDate(char* s)
{
    int length = strlen(s);
    if (length != 10)
        return false;
    if (s[2] != '.' || s[5] != '.')
        return false;
    for (int i = 0; i < length; ++i)
        if (s[i] < '0' || s[i] > '9')
            return false;
    return true;
}

bool compareDate(Date firstDate, Date secondDate)
{
    if (firstDate.year == secondDate.year) {
        if (firstDate.month == secondDate.month)
            return firstDate.day < secondDate.day;
        return firstDate.month < secondDate.month;
    }
    return firstDate.year < secondDate.year;
}

int main(int argc, char* argv[])
{
    FILE* inputFile = fopen(argv[1], "r");
    Date minDate = { INF, INF, INF };
    while (!feof(inputFile)) {
        char* string = malloc(256 * sizeof(char));
        fscanf(inputFile, "%s", string);
        if (isDate(string)) {
            Date date = { 0, 0, 0 };
            date.day = atoi(strcat(string[0], string[1]));
            date.month = atoi(strcat(string[3], string[3]));
            date.year = atoi(strcat(strcat(strcat(string[6], string[7]), string[8]), string[9]));
            if (date.day < 1 || date.day > 31 || date.month < 1 || date.month > 12 || date.year < 1)
                continue;
            if (compareDate(date, minDate))
                minDate = date;
        }
        free(string);
    }
    printf("Minimal date: %i.%i.%i", minDate.day, minDate.month, minDate.year);
}