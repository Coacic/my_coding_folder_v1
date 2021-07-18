#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <conio.h>
#define bool int
#define MAX_SIZE 255

char g_Infix[MAX_SIZE],
    g_Postfix[MAX_SIZE],
    g_PostfixUnos[MAX_SIZE],
    g_OnlyInfix[MAX_SIZE],
    g_CharStack[MAX_SIZE];

int g_TemporaryLetters = 0,
    g_TopOfTheTree = -1,
    g_QueueSize = 0,
    g_AllCounter,
    g_IsBinaryTreeFormated = 0,
    g_IsInfix = 0;

float g_Rezultat;

struct tree
{
    char data;
    float value;
    struct tree *left;
    struct tree *right;
};

struct q
{
    int front, rear;
    int size;
    struct tree **array;
};

struct tree *newNode(char data)
{
    struct tree *tree = (struct tree *)malloc(sizeof(struct tree));
    tree->data = data;
    tree->left = NULL;
    tree->right = NULL;
    return (tree);
};

struct stackTree
{
    struct tree *t;
    struct stackTree *next;
};

struct StackForInOrder
{
    int size;
    int top;
    struct tree **array;
};

struct StackForInOrder *createStack(int size)
{
    struct StackForInOrder *stack = (struct StackForInOrder *)malloc(sizeof(struct StackForInOrder));
    stack->size = size;
    stack->top = -1;
    stack->array = (struct tree **)malloc(stack->size * sizeof(struct tree *));
    return stack;
}

struct tree *g_Root = NULL;
struct tree *g_RootOnly = NULL;

bool isEmptyTree(struct stackTree *top)
{
    return (top == NULL) ? 1 : 0;
}

void PushTree(struct stackTree **topTree, struct tree *t)
{
    struct stackTree *NewTreeNode = (struct stackTree *)malloc(sizeof(struct stackTree));

    if (NewTreeNode == NULL)
    {
        printf("Stack Overflow\n");
        getchar();
        exit(0);
    }

    NewTreeNode->t = t;
    NewTreeNode->next = (*topTree);
    (*topTree) = NewTreeNode;
}

struct tree *PopTree(struct stackTree **topTree)
{
    struct tree *res;
    struct stackTree *top;

    if (isEmptyTree(*topTree))
    {
        printf("Stack Underflow\n");
        getchar();
        exit(0);
    }
    else
    {
        top = *topTree;
        res = top->t;
        *topTree = top->next;
        free(top);
        return res;
    }
}

struct q *createQueue(int size)
{
    struct q *queue = (struct q *)malloc(sizeof(struct q));

    queue->front = queue->rear = -1;
    queue->size = size;

    queue->array = (struct tree **)malloc(queue->size * sizeof(struct tree *));

    int i;
    for (i = 0; i < size; ++i)
        queue->array[i] = NULL;

    return queue;
}

int isEmptyQueue(struct q *queue)
{
    return queue->front == -1;
}

int isFullQueue(struct q *queue)
{
    return queue->rear == queue->size - 1;
}

int hasBothChild(struct tree *temp)
{
    return temp && temp->left && temp->right;
}

int HasOneChild(struct q *queue)
{
    return queue->front == queue->rear;
}

void Enqueue(struct tree *root, struct q *queue)
{
    if (isFullQueue(queue))
        return;

    queue->array[++queue->rear] = root;

    if (isEmptyQueue(queue))
        ++queue->front;
    g_QueueSize++;
}

struct tree *Dequeue(struct q *queue)
{
    if (isEmptyQueue(queue))
        return NULL;

    struct tree *temp = queue->array[queue->front];

    if (HasOneChild(queue))
        queue->front = queue->rear = -1;
    else
        ++queue->front;

    g_QueueSize--;

    return temp;
}

int isOperand(char op)
{
    if (op >= 'A' && op <= 'Z')
        return 1;
    if (op >= '0' && op <= '9')
        return 1;
    return 0;
}

int isLittleCharacter(char op)
{
    if (op >= 'a' && op <= 'z')
        return 1;
    return 0;
}

int isDigit(char op)
{
    if (op >= '0' && op <= '9')
        return 1;
    return 0;
}

int CountDigits(char temporaryArray[MAX_SIZE])
{
    int broj = 0, i = 0;
    while (temporaryArray[i] != '\0')
    {
        if ((temporaryArray[i] >= '0' && temporaryArray[i] <= '9'))
        {
            broj++;
        }
        i++;
    }
    return broj;
}

int IsOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        return 1;
    return 0;
}

int CountCharacters(char temporaryArray[MAX_SIZE])
{
    int letters = 0, i = 0;
    while (temporaryArray[i] != '\0')
    {
        if ((temporaryArray[i] >= 'A' && temporaryArray[i] <= 'Z'))
        {
            letters++;
        }
        i++;
    }
    return letters;
}

int CountOperators(char temporaryArray[MAX_SIZE])
{
    int op = 0, i = 0;
    while (temporaryArray[i] != '\0')
    {
        if (temporaryArray[i] == '+' || temporaryArray[i] == '*' || temporaryArray[i] == '/' || temporaryArray[i] == '^')
        {
            op++;
        }
        if (temporaryArray[i] == '-')
        {
            if (isOperand(temporaryArray[i + 1]) && temporaryArray[i - 1] == '(')
            {
                i++;
                continue;
            }
            else
            {
                op++;
            }
        }

        i++;
    }
    return op;
}

void levelOrder(struct tree *root)
{
    int isPrinted = 0;
    int letters = CountCharacters(g_Postfix);
    g_AllCounter = CountOperators(g_Postfix) + letters;
    struct q *queue = createQueue(MAX_SIZE);
    struct tree *dilimiter = newNode('-');
    Enqueue(root, queue);
    Enqueue(dilimiter, queue);
    while (!isEmptyQueue(queue))
    {
        struct tree *temp;
        temp = Dequeue(queue);
        if (temp != dilimiter)
        {
            printf("%c ", temp->data);
            isPrinted = 1;
        }

        if (temp->left)
        {
            Enqueue(temp->left, queue);
        }
        if (temp->right)
        {
            Enqueue(temp->right, queue);
        }
        if (temp->data == dilimiter->data && isPrinted == 1)
        {
            printf("\n");
            Enqueue(dilimiter, queue);
            isPrinted = 0;
        }
    }
}

void ResetAll()
{
    memset(g_Postfix, 0, sizeof g_Postfix);
    memset(g_Infix, 0, sizeof g_Infix);
    memset(g_Postfix, 0, sizeof g_Postfix);
    free(g_Root);
    free(g_RootOnly);
    g_TopOfTheTree = -1;
    printf("Uspesno resetovane vrednosti\n");
}

void PushCharacter(char pos)
{
    if (g_TopOfTheTree == MAX_SIZE - 1)
    {
        printf("STACK OVERFLOW\n");
    }
    else
    {
        g_TopOfTheTree++;
        g_PostfixUnos[g_TopOfTheTree] = pos;
    }
}

char PopCharacter()
{
    char value;
    if (g_TopOfTheTree < 0)
    {
        printf("STACK UNDERFLOW\n");
        getchar();
        exit(0);
    }
    else
    {
        value = g_PostfixUnos[g_TopOfTheTree];
        g_PostfixUnos[g_TopOfTheTree] = '\0';
        g_TopOfTheTree--;
        return (value);
    }
    return 0;
}

int OutPrecedence(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '%':
    case '/':
        return 3;
    case '(':
        return 100;
    }
}

int InPrecedence(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 2;
    case '*':
    case '%':
    case '/':
        return 4;
    case '(':
        return 0;
    }
}

void InfixToPostfix(char *input)
{
    int i = 0,
        counter = 0;
    char character;
    while (g_Infix[i] != '\0')
    {
        if (isOperand(g_Infix[i]))
        {
            g_CharStack[counter++] = g_Infix[i];
        }
        else if (IsOperator(g_Infix[i]))
        {
            if (g_TopOfTheTree == -1 || OutPrecedence(g_Infix[i]) > InPrecedence(g_PostfixUnos[g_TopOfTheTree]))
            {
                PushCharacter(g_Infix[i]);
            }
            else
            {
                while (g_TopOfTheTree != -1 && OutPrecedence(g_Infix[i]) < InPrecedence(g_PostfixUnos[g_TopOfTheTree]))
                {
                    character = PopCharacter();
                    g_CharStack[counter++] = character;
                }
                PushCharacter(g_Infix[i]);
            }
        }
        else if (g_Infix[i] == '(')
        {
            while (g_PostfixUnos[g_TopOfTheTree] != ')')
            {
                g_CharStack[counter++] = g_PostfixUnos[g_TopOfTheTree];
                character = PopCharacter();

                if (g_TopOfTheTree == -1)
                {
                    printf("Wrong input\n");
                    getchar();
                    exit(1);
                }
            }
            character = PopCharacter();
        }
        i++;
    }
    while (g_TopOfTheTree != -1)
    {
        if (g_PostfixUnos[g_TopOfTheTree] == '(')
        {
            printf("\n Wrong input\n");
            getchar();
            exit(1);
        }
        g_CharStack[counter++] = g_PostfixUnos[g_TopOfTheTree];
        character = PopCharacter();
    }
    memset(g_Postfix, 0, sizeof(g_Postfix));
    strcpy(g_Postfix, g_CharStack);
}

int Prec(char ch)
{
    switch (ch)
    {
    case '+':
    case '-':
        return 1;

    case '*':
    case '/':
        return 2;

    case '^':
        return 3;
    }
    return -1;
}

int infixToPostfix2(char *input)
{
    int i = 0, k = 0;
    while (i < strlen(input))
    {
        if (isOperand(input[i]))
        {
            input[k++] = input[i];
            i++;
        }
        else if (input[i] == '(')
        {
            if (input[i + 1] == '-')
            {
                input[k++] = input[i++];
                input[k++] = input[i++];
                input[k++] = input[i++];
                input[k++] = input[i++];
                input[k] = input[i++];
            }
            else
            {
                PushCharacter(input[i]);
                i++;
            }
        }

        else if (input[i] == ')')
        {
            while (g_TopOfTheTree != -1 && g_PostfixUnos[g_TopOfTheTree] != '(')
                input[k++] = PopCharacter();
            if (g_TopOfTheTree != -1 && g_PostfixUnos[g_TopOfTheTree] != '(')
            {
                getchar();
                return -1;
            }

            else
                PopCharacter();

            i++;
        }
        else
        {
            while (g_TopOfTheTree != -1 && Prec(input[i]) <= Prec(g_PostfixUnos[g_TopOfTheTree]))
                input[k++] = PopCharacter();
            PushCharacter(input[i]);
            i++;
        }
    }
    while (g_TopOfTheTree != -1)
        input[k++] = PopCharacter();

    input[k++] = '\0';
    strcpy(g_Postfix, input);
}

int redosledToPrefix(char symbol)
{
    switch (symbol)
    {
    case '+':
    case '-':
        return 2;
        break;
    case '*':
    case '/':
        return 4;
        break;
    case '$':
    case '^':
        return 6;
        break;
    case '#':
    case '(':
    case ')':
        return 1;
        break;
    }
}

char *StrReplace(const char *s, const char *oldW, const char *newW)
{
    char *result;
    int i, cnt = 0;
    int newWlen = strlen(newW);
    int oldWlen = strlen(oldW);

    for (i = 0; s[i] != '\0'; i++)
    {
        if (strstr(&s[i], oldW) == &s[i])
        {
            cnt++;

            i += oldWlen - 1;
        }
    }
    result = (char *)malloc(i + cnt * (newWlen - oldWlen) + 1);

    i = 0;
    while (*s)
    {
        if (strstr(s, oldW) == s)
        {
            strcpy(&result[i], newW);
            i += newWlen;
            s += oldWlen;
        }
        else
            result[i++] = *s++;
    }

    result[i] = '\0';
    return result;
}

void InOrder(struct tree *root)
{
    struct tree *current = root;
    struct stackTree *s = NULL;
    bool done = 0;

    while (!done)
    {
        if (current != NULL)
        {
            PushTree(&s, current);
            current = current->left;
        }
        else
        {
            if (!isEmptyTree(s))
            {
                current = PopTree(&s);
                printf("%c", current->data);

                current = current->right;
            }
            else
                done = 1;
        }
    }
    printf("\n");
}

void InOrderUnos(struct tree *root)
{
    struct tree *current = root;
    struct stackTree *s = NULL;
    bool done = 0;

    while (!done)
    {
        if (current != NULL)
        {
            PushTree(&s, current);
            current = current->left;
        }
        else
        {
            if (!isEmptyTree(s))
            {
                current = PopTree(&s);
                if (isOperand(current->data))
                {
                    printf("Unesite value za parametar: %c\n", current->data);
                    scanf("%f", &current->value);
                }
                current = current->right;
            }
            else
                done = 1;
        }
    }
    printf("\n");
}

void PostOrderIterative(struct tree *root)
{
    if (root == NULL)
        return;

    int counter = 0;
    int counter2 = 0;
    struct stackTree *s1, *s2;

    PushTree(&s1, root);
    counter++;
    struct tree *node;

    while (counter != 0)
    {
        node = PopTree(&s1);
        counter--;
        PushTree(&s2, node);
        counter2++;

        if (node->left)
        {
            PushTree(&s1, node->left);
            counter++;
        }
        if (node->right)
        {
            PushTree(&s1, node->right);
            counter++;
        }
    }
    while (counter2 != 0)
    {
        node = PopTree(&s2);
        counter2--;
        printf("%c ", node->data);
    }
}

void PostOrderIterativeEvaluate(struct tree *root)
{
    if (root == NULL)
        return;

    int counter = 0,
        counter2 = 0,
        i = 0;
    float val1 = 0,
          val2 = 0,
          rezultat = 0;
    struct stackTree *s1, *s2, *s;

    PushTree(&s1, root);
    counter++;
    struct tree *node,
        *temp;

    while (counter != 0)
    {
        node = PopTree(&s1);
        if (node->data == '-')
        {
            if (isOperand(node->left->data))
            {
                node = node->left;
                node->value = node->value * (-1);
            }
        }

        counter--;
        PushTree(&s2, node);
        counter2++;

        if (node->left)
        {
            PushTree(&s1, node->left);
            counter++;
        }
        if (node->right)
        {
            PushTree(&s1, node->right);
            counter++;
        }
    }

    while (counter2 != 0)
    {
        node = PopTree(&s2);
        counter2--;

        if ((node->data >= 'A' && node->data <= 'Z'))
        {
            PushTree(&s, node);
        }
        else
        {
            temp = PopTree(&s);
            val1 = temp->value;
            temp = PopTree(&s);
            val2 = temp->value;
            switch (node->data)
            {
            case '+':
                rezultat = val2 + val1;
                temp->value = rezultat;
                PushTree(&s, temp);
                break;
            case '-':
                rezultat = val2 - val1;
                temp->value = rezultat;
                PushTree(&s, temp);
                break;
            case '*':
                rezultat = val2 * val1;
                temp->value = rezultat;
                PushTree(&s, temp);
                break;
            case '/':
                rezultat = val2 / val1;
                temp->value = rezultat;
                PushTree(&s, temp);
                break;
            case '^':
                rezultat = pow(val2, val1);
                temp->value = rezultat;
                PushTree(&s, temp);
                break;
            }
        }
    }
    temp = PopTree(&s);
    g_Rezultat = temp->value;
    printf("%.3f", g_Rezultat);
    printf("\n");
}

void BinaryTreeRepresentation()
{
    struct tree *NewTree, *NewTree1, *NewTree2;
    int i = 0;
    struct stackTree *s = NULL;
    while (g_Postfix[i] != '\0')
    {
        if (isOperand(g_Postfix[i]))
        {
            NewTree = newNode(g_Postfix[i]);
            PushTree(&s, NewTree);
            i++;
        }
        else if (IsOperator(g_Postfix[i]))
        {
            NewTree = newNode(g_Postfix[i]);
            NewTree1 = PopTree(&s);
            NewTree2 = PopTree(&s);

            NewTree->right = NewTree1;
            NewTree->left = NewTree2;

            PushTree(&s, NewTree);
            i++;
        }
        else if (g_Postfix[i] == '(')
        {
            if (g_Postfix[i + 1] == '-')
            {
                NewTree = newNode(g_Postfix[i + 1]);
                NewTree2 = newNode(g_Postfix[i + 2]);
                NewTree->left = NewTree2;
                PushTree(&s, NewTree);
                i = i + 4;
            }
        }
    }
    NewTree = PopTree(&s);
    g_Root = NewTree;
    g_RootOnly = g_Root;
}

void InfixToPrefix(char infix[MAX_SIZE], char prefix[MAX_SIZE])
{
    int i, j = 0;
    char karakter;
    g_PostfixUnos[++g_TopOfTheTree] = '#';
    strrev(infix);
    for (i = 0; i < strlen(infix); i++)
    {
        karakter = infix[i];
        if (IsOperator(karakter) == 0)
        {
            prefix[j] = karakter;
            j++;
        }
        else
        {
            if (karakter == ')')
            {
                PushCharacter(karakter);
            }
            else if (karakter == '(')
            {
                while (g_PostfixUnos[g_TopOfTheTree] != ')')
                {
                    prefix[j] = PopCharacter();
                    j++;
                }
                PopCharacter();
            }
            else
            {
                if (redosledToPrefix(g_PostfixUnos[g_TopOfTheTree]) <= redosledToPrefix(karakter))
                {
                    PushCharacter(karakter);
                }
                else
                {
                    while (redosledToPrefix(g_PostfixUnos[g_TopOfTheTree]) >= redosledToPrefix(karakter))
                    {
                        prefix[j] = PopCharacter();
                        j++;
                    }
                    PushCharacter(karakter);
                }
            }
        }
    }
    while (g_PostfixUnos[g_TopOfTheTree] != '#')
    {
        prefix[j] = PopCharacter();
        j++;
    }
    strrev(prefix);
    prefix[j] = '\0';
}

int height(struct tree *tree)
{
    if (tree == NULL)
        return 0;
    else
    {
        int lheight = height(tree->left);
        int rheight = height(tree->right);
        if (lheight > rheight)
            return (lheight + 1);
        else
            return (rheight + 1);
    }
}

void PreOrder(struct tree *root)
{
    struct tree *next;
    struct stackTree *s = NULL;
    PushTree(&s, root);

    while (!isEmptyTree(s))
    {
        next = PopTree(&s);
        while (next != NULL)
        {
            printf("%c", next->data);
            if (next->right != NULL)
            {
                PushTree(&s, next->right);
            }
            next = next->left;
        }
    }
    printf("\n");
}

int main()
{
    char karakter[MAX_SIZE],
        privremeniChar,
        brojniKarakter[MAX_SIZE],
        *result = NULL;

    int DaLiJePostfix = 0,
        DaLiJePrefix = 0,
        i = 0,
        brojacSlova = 0,
        brojacKaraktera = 0,
        OperatorCounter = 0;

    while (1)
    {
        int izbor;
        printf("----------------------------------------------------------------------------------------\n0. Izlazak programa\n1. Unos izraza u Infix notaciji\n2. Formiranje stabla na osnovu prethodnog unesenog izraza\n3. Ispis datog izraza u Prefix notaciji prolazom Preorder poretka kroz stablo\n4. Ispisivanje stabala u Level Order poretku\n5. Unosenje vrednosti i izracunavanje izraza koji je unesen koriscenjem binarnih stabala\n6. Ispis stabla u Post order poretku\n----------------------------------------------------------------------------------------\n");
        printf("Izaberite opciju:\n");
        scanf("%d", &izbor);
        switch (izbor)
        {
        case 0:
            ResetAll();
            return 0;
            break;

        case 1:
            g_IsInfix = 1;
            printf("Unesite infix izraz:\n");
            scanf("%s", g_Infix);
            strcpy(g_OnlyInfix, g_Infix);
            OperatorCounter = CountOperators(g_Infix);
            g_TemporaryLetters = CountCharacters(g_Infix);
            g_TemporaryLetters = g_TemporaryLetters + CountDigits(g_Infix);
            if (OperatorCounter == g_TemporaryLetters - 1)
            {
                continue;
            }

            else
            {
                printf("Neispravan unos infiks notacije");
                _getch();
                exit(0);
            }
            break;

        case 2:
            if (g_IsInfix == 0)
            {
                printf("Niste uneli izraz\n");
                break;
            }
            strcpy(g_Infix, g_OnlyInfix);
            printf("Stablo formirano od datog izraza: \n");
            infixToPostfix2(g_Infix);
            strcpy(g_Infix, g_OnlyInfix);
            BinaryTreeRepresentation();
            InOrder(g_Root);
            g_IsBinaryTreeFormated = 1;
            break;

        case 3:
            if (g_IsInfix == 0)
            {
                printf("Niste uneli izraz\n");
                break;
            }
            if (g_IsBinaryTreeFormated == 0)
            {
                printf("Niste formirali stablo\n");
                break;
            }
            printf("Izraz u prefix notaciji, ispisan pomocu PREORDER prolaza kroz stablo:\n");
            PreOrder(g_Root);
            break;

        case 4:
            if (g_IsInfix == 0)
            {
                printf("Niste uneli izraz\n");
                break;
            }
            if (g_IsBinaryTreeFormated == 0)
            {
                printf("Niste formirali stablo\n");
                break;
            }
            strcpy(g_Infix, g_OnlyInfix);
            printf("Level Order traversal of binary tree is:\n");
            levelOrder(g_RootOnly);
            break;

        case 5:
            if (g_IsInfix == 0)
            {
                printf("Niste uneli izraz\n");
                break;
            }
            if (g_IsBinaryTreeFormated == 0)
            {
                printf("Niste formirali stablo\n");
                break;
            }
            g_Root = g_RootOnly;
            InOrderUnos(g_Root);
            printf("Konacna vrednost je: \n");
            PostOrderIterativeEvaluate(g_Root);
            break;

        case 6:
            if (g_IsInfix == 0)
            {
                printf("Niste uneli izraz\n");
                break;
            }
            if (g_IsBinaryTreeFormated == 0)
            {
                printf("Niste formirali stablo\n");
                break;
            }
            g_Root = g_RootOnly;
            PostOrderIterative(g_Root);
            printf("\n");
            break;

        default:
            ResetAll();
            return 0;
            break;
        }
    }
}