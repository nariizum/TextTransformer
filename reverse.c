#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXWORDS 100
#define MAXLINES 1000

int readFromFile(char *filename, char ***output)
{
    FILE *fp = fopen(filename, "r");

    char **lines = (char **)malloc(sizeof(char) * MAXLINES * MAXWORDS);
    for (int i = 0; i < MAXLINES; i++)
    {
        lines[i] = (char *)malloc(sizeof(char) * MAXWORDS);
    }

    int n = 0;
    while (fgets(lines[n], MAXWORDS, fp) != NULL)
    {
        for (int i = 0; i < strlen(lines[n]); i++)
        {
            if (lines[n][i] == '\n')
            {
                lines[n][i] = '\0';
            }
        }

        n++;
    }
    fclose(fp);
    *output = lines;
    return n;
}

void reverse(char *s)
{
    char *reversed = (char *)malloc(sizeof(char) * MAXWORDS);

    int n = 0;
    for (int i = strlen(s) - 1; i >= 0; i--)
    {
        reversed[n++] = s[i];
    }
    reversed[n] = '\0';

    strcpy(s, reversed);
    free(reversed);
}

void getAllFlags(int argc, char *argv[], bool *printNumbers, bool *reverseLines, bool *filterLines, char **filterWord)
{
    *printNumbers = false;
    *reverseLines = false;
    *filterLines = false;
    *filterWord = NULL;

    for (int i = 2; i < argc; i++)
    {
        if (strcmp(argv[i], "-n") == 0)
        {
            *printNumbers = true;
        }
        else if (strcmp(argv[i], "-r") == 0)
        {
            *reverseLines = true;
        }
        else if (strcmp(argv[i], "-f") == 0)
        {
            *filterLines = true;
            *filterWord = argv[i + 1];
        }
    }
}

void numberLines(char **lines, int n)
{
    for (int i = 0; i < n; i++)
    {
        char *numbered = (char *)malloc(sizeof(char) * MAXWORDS);
        sprintf(numbered, "%d %s", i + 1, lines[i]);
        strcpy(lines[i], numbered);
        free(numbered);
    }
}

void reverseOrderLines(char **lines, int n)
{
    char **reversed = (char **)malloc(sizeof(char) * MAXLINES * MAXWORDS);
    for (int i = 0; i < MAXLINES; i++)
    {
        reversed[i] = (char *)malloc(sizeof(char) * MAXWORDS);
    }

    for (int i = 0; i < n; i++)
    {
        strcpy(reversed[n - i - 1], lines[i]);
    }

    for (int i = 0; i < n; i++)
    {
        strcpy(lines[i], reversed[i]);
    }

    for (int i = 0; i < MAXLINES; i++)
    {
        free(reversed[i]);
    }
    free(reversed);
}

int filter(char **lines, int n, char *filterWord)
{
    char **filtered = (char **)malloc(sizeof(char) * MAXLINES * MAXWORDS);
    for (int i = 0; i < MAXLINES; i++)
    {
        filtered[i] = (char *)malloc(sizeof(char) * MAXWORDS);
    }

    int m = 0;
    for (int i = 0; i < n; i++)
    {
        if (strstr(lines[i], filterWord) != NULL)
        {
            strcpy(filtered[m++], lines[i]);
        }
    }

    for (int i = 0; i < m; i++)
    {
        strcpy(lines[i], filtered[i]);
    }

    for (int i = 0; i < MAXLINES; i++)
    {
        free(filtered[i]);
    }
    free(filtered);

    return m;
}