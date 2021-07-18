//f1
#include <stdio.h>
#include <stdlib.h>

char* loadString() {
    char* str = NULL, c;
    int i = 0;
    
    c = getchar();
    while(c != '\n') {
        str = realloc(str, (i+1)*sizeof(char));
        *(str + (i++)) = c;
        c = getchar();
    }
    str = realloc(str, (i+1)*sizeof(char));
    str[i] = '\0';
    return str;
}

//f2
#include <stdio.h>
#include <stdlib.h>

int getNextDigit(char *string) {
    
    int pos, i = 0;
    
    while(string[i] != '\0') {
        if((string[i] >= '0') && (string[i]  <= '9')) {
            return i;
        }
        i++;
    }
    return i;
    
}

//f3
#include <stdio.h>
#include <stdlib.h>

char* substring(char *string, int start, int end) {
    char* substring = malloc((end-start+2) * sizeof(char));
    int len = 0;
    for(int i = start; i <= end; i++){
        substring[len++] = string[i];
    }
    substring[len] = '\0';
    return substring;
}

//f4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** split(char *string) {
    char** c = NULL, *str = string, *pom;
    int br, len, size = 0;
    
    while(*str){
        
        br = *str++ - '0';
        pom = str;
        len = 0;
        
        while((*pom >= 'a' && *pom <= 'z') || (*pom >= 'A' && *pom <= 'Z')) {
            pom++;
            len++;
        }

        if(len < br) {
            c = realloc(c, (size+1)*sizeof(char*));
            c[size] = malloc((len+1)*sizeof(char));
            memcpy(c[size], str, len*sizeof(char));
            c[size++][len] = '\0';
        }
        str = pom;
    }
   c = realloc(c, (size+1) * sizeof(char*));
   c[size] = NULL;
   return c;
}

//main
#include <stdio.h>
#include <stdlib.h>

int main() {
    
    char *s, **splits, **pom;
    
    s = loadString();
    splits = split(s);
    pom = splits;
    int i = 0;
    
    while(*(pom+i) != NULL){
        
        printf("%s", *(pom+i));
        free(*(pom+i));
        i++;
        if(*(pom+i) != NULL) putchar('\n');
        
    }
    
    free(splits);
    free(s);
}