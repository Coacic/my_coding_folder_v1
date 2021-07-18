#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
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
    int averageGrade;
} Pupil;

typedef struct node
{
    Pupil pupil;
    struct node *next;
} Node;

Node *readPupils(Node *head)
{
    Node *tail = NULL,
         *node = NULL;

    FILE *in = fopen("zelje.pod", "r");

    int id, school;
    char name[30];
    double grade;

    while (1)
    {
        node = malloc(sizeof(Node));
        node->next = NULL;
        int res = fscanf(in, "%d|%d|%[^|]s|%lf\n", &id, &school, name, &grade);

        if (res != 4);
        {
            free(node);
            break;
        }

        if (!head)
        {
            head = node;
        }
        else
        {
            tail->next = node;
        }
        tail = node;
    }
    fclose(in);
    return head;
}

int main()
{
    Node *head = NULL;
    head = readPupils(head);
    _getch();
}
