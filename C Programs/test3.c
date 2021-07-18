

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **readWords(int n)
{
    char **rec = NULL, *r = NULL, *start = NULL, c = 0;
    int br = 0, brr = 0;
    for (int i = 0; i < n; i++)
    {
        br = 0;
        start = NULL;
        while ((c = getchar()) != '\n')
        {
            start = realloc(start, (br + 1) * sizeof(char));
            start[br++] = c;
        }
        start = realloc(start, (br + 1) * sizeof(char));
        start[br] = '\0';

        rec = realloc(rec, (brr + 1) * sizeof(rec));
        rec[brr++] = start;
    }
    start = NULL;
    free(start);
    return rec;
}

int main()
{
    int n = 3, j = 0;
    char **words = readWords(n);
    for (int i = 0; i < n; i++)
    {
        j = 0;
        printf("%s\n", words[i]);
    }
    for (int i = 0; i < n; i++)
    {
        free(words[i]);
    }
    
}