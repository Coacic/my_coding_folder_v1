#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int main(void)
{
    unsigned long long y;
    unsigned int i;
    FILE *fd = fopen("uredjeni_parovi.txt" , "w");
    if( fd == NULL)
    {
        printf("Greska pri otvaranju!\n");
        exit(1);
    }

    for(i=1;i<600;i++) fprintf(fd , "(x,y) = ( %u , %llu )\n" , i , pow(i,6) );

    fclose(fd);

    printf("Sve ok\n");

    return(0);
}