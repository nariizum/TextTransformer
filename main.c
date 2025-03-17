#include <stdio.h>
#include <stdbool.h>
#include "reverse.h"

int main(int argc, char *argv[])
{
    // init & read
    char **lines;
    int n = readFromFile(argv[1], &lines);

    // get all flags
    char *filterWord;
    bool printNumbers, reverseLines, filterLines;
    getAllFlags(argc, argv, &printNumbers, &reverseLines, &filterLines, &filterWord);

    // reverse every line
    for (int i = 0; i < n; i++)
    {
        reverse(lines[i]);
    }

    if (printNumbers)
    {
        numberLines(lines, n);
    }

    if (reverseLines)
    {
        reverseOrderLines(lines, n);
    }

    if (filterLines)
    {
        n = filter(lines, n, filterWord);
    }

    // print
    for (int i = 0; i < n; i++)
    {
        printf("%s\n", lines[i]);
    }

    return 0;
}