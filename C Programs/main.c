#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

typedef struct user
{
    char username[31], email[31];
    int time;
} User;
typedef struct node
{
    User user;
    struct node *next;
} Node;

Node *readUsers()
{
    FILE *in = fopen("korisnici.txt", "r");
    Node *temp = NULL,
         *head = NULL;

    while (1)
    {

        Node *node = malloc(sizeof(Node));
        node->next = NULL;
        if (fscanf(in, "%s %s", node->user.username, node->user.email) != 2)
        {
            free(node);
            break;
        }

        if (!head)
            head = node;
        else
        {
            temp->next = node;
        }
        temp = node;
    }

    fclose(in);
    return head;
}

User updateTime(Node *head)
{

    FILE *in = fopen("logs.txt", "r");

    Node *temp = head,
         *current = head;

    while (current)
    {
        current->user.time = 0;
        current = current->next;
    }

    current = temp;

    int MAX = -1,
        tempNum = 0,
        intCounter = 0,
        intArray[MAX_SIZE];

    for (int i = 0; i < MAX_SIZE; i++)
    {
        intArray[i] = 0;
    }

    char c,
        mail[31];

    while (1)
    {

        if (fscanf(in, "%s %c %d", mail, &c, &tempNum) != 3)
        {
            break;
        }
        intCounter = 0;
        while (strcmp(current->user.email, mail) != 0)
        {
            current = current->next;
            intCounter++;
        }

        if (c == 'p')
        {
            intArray[intCounter] = tempNum;
            tempNum = 0;
        }
        else if (c == 'o')
        {
            current->user.time = tempNum - intArray[intCounter] + current->user.time;
            if (MAX < current->user.time)
                MAX = current->user.time;
            tempNum = 0;
        }

        current = temp;
    }
    int counter = 0;
    while (current)
    {
        if (counter > 1)
        {
            counter--;
            if (strcmp(current->user.email, mail) >= 0)
                strcpy(mail, current->user.email);
        }
        if (current->user.time == MAX)
        {
            strcpy(mail, current->user.email);
            counter++;
        }

        current = current->next;
    }
    current = temp;
    while (current)
    {
        if (strcmp(mail, current->user.email) == 0)
        {
            return current->user;
        }
    }
}

int main()
{

    Node *head = readUsers();
    User max = updateTime(head);
}