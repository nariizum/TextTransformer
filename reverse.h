#define MAXWORDS 100
#define MAXLINES 1000

#ifndef reverse_h
#define reverse_h

int readFromFile(char *filename, char ***output);
void reverse(char *s);
void getAllFlags(int argc, char *argv[], bool *printNumbers, bool *reverseLines, bool *filterLines, char **filterWord);
void numberLines(char **lines, int n);
void reverseOrderLines(char **lines, int n);
int filter(char **lines, int n, char *filterWord);

#endif