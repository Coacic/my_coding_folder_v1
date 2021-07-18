#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NUMBER_OF_SCHOOLS 400

typedef struct school
{
    int id, places;
    char name[31];
} School;

typedef struct pupil
{
    int id, school;
    char name[31];
    double averageGrade;
} Pupil;

typedef struct node
{
    Pupil pupil;
    struct node *next;
} Node;

void readSchools(School schools[MAX_NUMBER_OF_SCHOOLS])
{
    FILE *in = fopen("skole.txt", "r");

    int count = 0;
    while (1)
    {

        School *node = malloc(sizeof(School));

        if (fscanf(in, "%d %s", &node->id, &node->name) != 2)
        {
            free(node);
            break;
        }

        schools[count++] = node;
    }

    fclose(in);
}

int main()
{
    printf("Hello dude");
}
