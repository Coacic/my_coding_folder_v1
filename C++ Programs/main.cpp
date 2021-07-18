#include <iostream>
#include <ctype.h>
#include <cstdlib>
#include <string>
#include <ctime>
#include <iomanip>
#include <utility>
#include <queue>
#include <stack>
#include <cmath>
#include <string.h>
#define MAX 255
using namespace std;

typedef struct Element
{
    char *naziv;
    int cena;
    int naStanju;
}Elem;

//Binary tree definition
typedef struct Node
{
    struct Node *left;
    struct Node *right;
    struct Elem;
    int key, height;
} Node;

//Stack definition
typedef struct Stack
{
    struct Node *t;
    struct Stack *next;
} Stack;

void push(Stack **top, Node *tree)
{
    struct Stack *newTreeNode = (Stack *)malloc(sizeof(Stack));

    if (newTreeNode == NULL)
    {
        printf("Stack Overflow \n");
        getchar();
        exit(0);
    }

    newTreeNode->t = tree;

    newTreeNode->next = (*top);

    (*top) = newTreeNode;
}

bool isStackEmpty(Stack *top)
{
    if (top == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

Node *pop(Stack **vrh)
{
    Node *res = NULL;
    Stack *top = NULL;

    if (isStackEmpty(*vrh))
    {
        printf("Stack Underflow \n");
        getchar();
        exit(0);
    }
    else
    {
        top = *vrh;
        res = top->t;
        (*vrh) = top->next;
        free(top);
        return res;
    }
}

int *inputVector(int *arr, int *number, int *n, int *m)
{
    cout << "Unesite dimenzije n i m za datu matricu:\n";
    cin >> (*n) >> (*m);
    if (((*n) <= 0) || ((*m) <= 0) || ((*n) >= MAX) || ((*m) >= MAX))
    {
        perror("Neispravne vrednosti za matricu");
    }
    (*number) = (*n) * (*m);
    for (int i = 0; i < (*number); i++)
    {
        cout << "Upisite " << i << ". element matrice:" << endl;
        cin >> arr[i];
    }
    int i, j;
    for (i = 0; i < (*number) - 1; i++)
    {
        for (j = 0; j < (*number) - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return arr;
}

int *inputVectorThroughFile(int *arr, int *number, int *n, int *m)
{
    FILE *in = fopen("matrica.txt", "r");
    if (!in)
        perror("File nedostaje\n");
    cout << "Unesite n i m dimenzije date matrice:\n";
    cin >> (*n) >> (*m);
    if (((*n) <= 0) || ((*m) <= 0) || ((*n) >= MAX) || ((*m) >= MAX))
    {
        perror("Neispravne vrednosti za matricu");
    }
    (*number) = (*n) * (*m);
    char c;
    int num = 0, counter = 0;
    c = fgetc(in);
    while (!feof(in))
    {
        if (c == '\n')
        {
            c = fgetc(in);
        }
        while (isdigit(c))
        {
            num = num * 10 + c - '0';
            c = fgetc(in);
        }
        arr[counter++] = num;
        num = 0;
        c = fgetc(in);
    }

    int i, j;
    for (i = 0; i < (*number) - 1; i++)
    {
        for (j = 0; j < (*number) - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    fclose(in);
    return arr;
}

int **sortMatrix(int **matrix, int n, int m)
{
    int placeholder = n * m;
    int **transpose = new int *[placeholder];
    for (int i = 0; i < placeholder; ++i)
        transpose[i] = new int[placeholder];

    //Sorting by rows
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            for (int k = (j + 1); k < m; ++k)
            {
                if (matrix[i][j] > matrix[i][k])
                {
                    int a = matrix[i][j];
                    matrix[i][j] = matrix[i][k];
                    matrix[i][k] = a;
                }
            }
        }
    }

    //Transposing
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            transpose[j][i] = matrix[i][j];
        }
    }

    //Sorting by rows 2nd time
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            for (int k = (j + 1); k < n; ++k)
            {
                if (transpose[i][j] > transpose[i][k])
                {
                    int a = transpose[i][j];
                    transpose[i][j] = transpose[i][k];
                    transpose[i][k] = a;
                }
            }
        }
    }

    //Transposing 2nd time
    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            matrix[j][i] = transpose[i][j];
        }
    }

    //Sorting matrix by column
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n - 1 - j; k++)
            {
                if (matrix[k][i] > matrix[k + 1][i])
                {
                    int temp = matrix[k][i];
                    matrix[k][i] = matrix[k + 1][i];
                    matrix[k + 1][i] = temp;
                }
            }
        }
    }

    //Printing Matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d\t", matrix[i][j]);
            if (j == m - 1)
            {
                cout << endl;
            }
        }
    }
    return matrix;
}

int **formMatrix(int *v, int *row, int *col)
{
    int n = (*row), m = (*col), mul = n * m, tekuciRed = 0;
    int **matrix = new int *[n];
    for (int i = 0; i < n; ++i)
        matrix[i] = new int[m];

    //Unos elemenata u matricu
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            matrix[i][j] = v[tekuciRed++];
        }
    }

    //Sorting Matrix
    matrix = sortMatrix(matrix, n, m);

    return matrix;
}

int searchAlgorithmEvaluatePerformance(int **matrica, int *row, int *col, int *ite)
{
    int n = (*row), m = (*col), counter = 0, key = (*ite);
    int lowest = matrica[0][0], highest = matrica[n - 1][m - 1];
    if (key < lowest || key > highest)
    {
        counter++;
        return 1;
    }
    int i = 0, j = m - 1;
    while (i < n && j >= 0)
    {
        counter++;
        if (matrica[i][j] == key)
        {
            return counter;
        }
        if (matrica[i][j] > key)
        {
            j--;
        }
        else
        {
            i++;
        }
    }
    return counter;
}

void createSeq(int **matrica, int *row, int *col, int *y)
{
    int n = (*row), m = (*col);
    int counter = 0;
    for (int i = 0; i < (*y); i++)
    {
        //findTheKeyThroughSeq(matrica, &n, &m, i, &counter);
        counter = counter + searchAlgorithmEvaluatePerformance(matrica, &n, &m, &i);
    }
    double d_counter = counter, d_totalNumber = (*y), totalCounter = 0;
    totalCounter = float(d_counter) / float((*y));
    printf("U proseku za nalazenje svakog kljuca se desilo %.2f iteracija\n", ((double)counter) / ((double)(*y)));
}

int **generateRandomMatrix(int *randn, int *randm)
{
    int n = 0, m = 0, low, high;
    cout << "Unesite dimenzije N x M date matrice:" << endl;
    cin >> (*randn) >> (*randm);
    n = (*randn);
    m = (*randm);
    cout << "Unesite opseg proizvoljnih brojeva matrice od najmanjeg broja do najveceg" << endl;
    cin >> low >> high;
    int i = 0, j = 0;
    int **matrica = new int *[n];
    for (int i = 0; i < n; ++i)
        matrica[i] = new int[m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            matrica[i][j] = (rand() % (high - low + 1)) + low;
        }
    }
    matrica = sortMatrix(matrica, n, m);
    return matrica;
}

int searchAlgorithm(int **matrica, int *row, int *col)
{
    int key, n = (*row), m = (*col);
    cout << "Unesite kljuc:\n";
    cin >> key;
    int lowest = matrica[0][0], highest = matrica[n - 1][m - 1];
    if (key < lowest || key > highest)
    {
        cout << "Kljuc " << key << " nije nadjen" << endl;
        return 0;
    }
    int i = 0, j = m - 1;
    while (i < n && j >= 0)
    {
        if (matrica[i][j] == key)
        {
            printf("Kljuc %d je nadjen na kordinatama matrice: %d %d\n", key, i, j);
            return 1;
        }
        if (matrica[i][j] > key)
        {
            j--;
        }
        else
        {
            i++;
        }
    }

    cout << "Kljuc " << key << " nije nadjen" << endl;
    return 0;
}

//Tree Code BST Drveca//
int findTheHeight(Node *node)
{
    if (!node)
        return 0;
    return node->height;
}

Node *newNode(int key)
{
    Node *node = new Node;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return (node);
}

Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *temp = x->right;
    x->right = y;
    y->left = temp;
    if (findTheHeight(y->left) > findTheHeight(y->right) + 1)
    {
        y->height = findTheHeight(y->left);
    }
    else
    {
        y->height = findTheHeight(y->right) + 1;
    }

    if (findTheHeight(x->left) > findTheHeight(x->right) + 1)
    {
        x->height = findTheHeight(x->left);
    }
    else
    {
        x->height = findTheHeight(x->right) + 1;
    }
    return x;
}

Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(findTheHeight(x->left),
                    findTheHeight(x->right)) +
                1;
    y->height = max(findTheHeight(y->left),
                    findTheHeight(y->right)) +
                1;
    return y;
}

int findTheBalance(Node *node)
{
    if (!node)
        return 0;
    return findTheHeight(node->left) - findTheHeight(node->right);
}

Node *insertIntoBST(Node *root, int key)
{
    if (!root)
        return (newNode(key));
    Node *newnode = newNode(key), *x = root, *y = NULL;
    Stack *s = NULL;

    while (x != NULL)
    {
        y = x;
        push(&s, x);
        if (key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    if (!y)
        y = newnode;

    else if (key < y->key)
        y->left = newnode;
    else
        y->right = newnode;

    push(&s, y);
    while (!isStackEmpty(s))
    {
        y = pop(&s);
        y->height = 1 + max(findTheHeight(y->left), findTheHeight(y->right));
        int balance = findTheBalance(y);

        if (balance > 1 && key < y->left->key)
            return rightRotate(y);

        if (balance < -1 && key > y->right->key)
            return leftRotate(y);

        if (balance > 1 && key > y->left->key)
        {
            y->left = leftRotate(y->left);
            return rightRotate(y);
        }

        if (balance < -1 && key < y->right->key)
        {
            y->right = rightRotate(y->right);
            return leftRotate(y);
        }
    }
    return y;
}

Node *createAVLTree(int **matrica, int *row, int *col, Node *root)
{
    int n = (*row);
    int m = (*col);
    int key;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            key = matrica[i][j];
            if (!root)
                root = insertIntoBST(root, key);
            else
            {
                insertIntoBST(root, key);
            }
        }
    }
    return root;
}

void inorderTraversal(Node *root)
{
    Stack *s = NULL;
    Node *node = root;

    while (node != NULL || !isStackEmpty(s))
    {
        while (node != NULL)
        {
            push(&s, node);
            node = node->left;
        }
        node = pop(&s);
        cout << node->key << " ";
        node = node->right;
    }
    cout << endl;
}

int binarySearch(Node *root)
{
    Node *tmp = root;
    int key, count = 0;
    cout << "Upisite kljuc:\n";
    cin >> key;
    while (true)
    {
        if (key != tmp->key)
        {
            count++;
            if (key <= tmp->key && (tmp->left != NULL))
            {
                tmp = tmp->left;
                continue;
            }
            else if (key >= tmp->key && (tmp->right != NULL))
            {
                tmp = tmp->right;
                continue;
            }
            cout << "Kljuc nije nadjen";
            return 0;
        }
        else
        {
            cout << "Kljuc " << key << " je nadjen posle " << count << " iteracija" << endl;
            return 1;
        }
    }
}

Stack *printLevelOrder(Node *root, Stack *outerStack)
{
    bool left = false, right = false;
    int height = findTheHeight(root);
    if (root == NULL)
        return 0;

    for (int i = 0; i < height; i++)
    {
        cout << "\t";
    }
    cout << root->key << endl;

    queue<Node *> q;
    Stack *newStack = NULL;
    Node *tmp = NULL;

    q.push(root);

    while (q.empty() == false)
    {
        Node *node = q.front();
        if (left)
        {
            for (int i = 0; i < findTheHeight(node); i++)
            {
                cout << "\t";
            }
            cout << node->key << endl;
            left = false;
        }
        else if (right)
        {
            for (int i = 0; i < findTheHeight(node); i++)
            {
                cout << "\t";
            }
            cout << node->key << endl;
            right = false;
        }
        push(&newStack, node);
        q.pop();

        if (node->left != NULL)
        {
            left = true;
            q.push(node->left);
        }

        if (node->right != NULL)
        {
            right = true;
            q.push(node->right);
        }
    }
    while (!isStackEmpty(newStack))
    {
        tmp = pop(&newStack);
        push(&outerStack, tmp);
    }
    return outerStack;
}

struct Node *insert(struct Node *node, int key)
{
    bool inserted = false;
    int rot = 0;
    Node *x = NULL, *tmp;
    Stack *s = NULL;
    if (node == NULL)
        return (newNode(key));

    while (!inserted)
    {
        if (key < node->key && node->left)
        {
            push(&s, node);
            node = node->left;
        }
        else if (key > node->key && node->right)
        {
            push(&s, node);
            node = node->right;
        }
        else
        {
            if (key < node->key)
            {
                push(&s, node);
                node->left = newNode(key);
                inserted = true;
            }
            else
            {
                push(&s, node);
                node->right = newNode(key);
                inserted = true;
            }
        }
    }
    while (!isStackEmpty(s))
    {
        x = pop(&s);
        switch (rot)
        {
        case 0:
            break;
        case 1:
            x->left = tmp;
            rot = 0;
            break;
        case 2:
            x->right = tmp;
            rot = 0;
            break;
        case 3:
            rot = 0;
            break;
        case 4:
            rot = 0;
            break;
        default:
            break;
        }
        x->height = 1 + max(findTheHeight(x->left), findTheHeight(x->right));
        int balance = findTheBalance(x);

        if (balance > 1 && key < x->left->key)
        {
            rot = 1;
            x = rightRotate(x);
            tmp = x;
        }
        if (balance < -1 && key > x->right->key)
        {
            rot = 2;
            x = leftRotate(x);
            tmp = x;
        }
        if (balance > 1 && key > x->left->key)
        {
            rot = 3;
            x->left = leftRotate(x->left);
            x = rightRotate(x);
            tmp = x;
        }
        if (balance < -1 && key < x->right->key)
        {
            rot = 4;
            x->right = rightRotate(x->right);
            x = leftRotate(x);
            tmp = x;
        }
    }
    return x;
}

Node *createTree(int **matrica, int *row, int *col, Node *root)
{
    int n = (*row);
    int m = (*col);
    int key;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            key = matrica[i][j];
            if (!root)
                root = insert(root, key);
            else
            {
                root = insert(root, key);
            }
        }
    }
    return root;
}

void printTree(Node *root)
{
    if (root == NULL)
        return;
    Stack *s = NULL;
    Node *tmp = NULL;
    int height = 1, maxheight = findTheHeight(root);
    s = printLevelOrder(root, s);
    while (!isStackEmpty(s))
    {
        tmp = pop(&s);
        for (int i = 0; i < findTheHeight(tmp); i++)
        {
            cout << "\t";
        }
        cout << tmp->key << endl;
    }
}

void padding(char ch, int n)
{
    int i;

    for (i = 0; i < n; i++)
        putchar(ch);
}

void structure(Node *root, int level)
{
    int i;

    if (root == NULL)
    {
        padding('\t', level);
        puts("~");
    }
    else
    {
        structure(root->right, level + 1);
        padding('\t', level);
        printf("%d\n", root->key);
        structure(root->left, level + 1);
    }
}

void write(int pp, int offset, Node *root, char *side, int level, int **A)
{

    if (root == nullptr)
        return;

    if (strcmp(side, "left") == 0)
    {
        A[level][pp - offset] = root->key;

        write(pp - offset, offset / 2, root->left, "left", level + 1, A);
        write(pp - offset, offset / 2, root->right, "right", level + 1, A);
    }
    else
    {
        A[level][pp + offset] = root->key;
        write(pp + offset, offset / 2, root->left, "left", level + 1,A);
        write(pp + offset, offset / 2, root->right, "right", level + 1,A);
    }
}

void displayTree(Node *root, int **A)
{
    int i, j;

    int h = findTheHeight(root);
    int nn = pow(2, h + 1) - 1;
    A = NULL;

    A = (int **)malloc((h + 1 + 1) * sizeof(int *));
    for (int i = 1; i <= h + 1; i++)
        A[i] = (int *)malloc((nn + 1) * sizeof(int));

    for (i = 1; i <= h + 1; i++)
        for (j = 1; j <= nn; j++)
            A[i][j] = 0;

    write(nn + 1, (nn + 1) / 2, root, "left", 1, A);

    // Displaying the 2d matrix
    for (i = 1; i <= h + 1; i++)
    {
        for (j = 1; j <= nn; j++)
        {
            if (A[i][j] != 0)
                printf("%d", A[i][j]);
            else
                printf(" ");
        }
        printf("\n\n\n");
    }

    for (int i = 0; i <= h + 1; i++)
        free(A[i]);
    free(A);
}

int main()
{
    srand(time(NULL));
    int Option, n = 0, m = 0, *ptr, v[MAX], length = 0, number = 0, **matrica, key, findB = 0, random = rand(), **randMatrica, matrixChoice, randn, randm, keyForInsert = 0, **A;
    Node *root = NULL;
    while (true)
    {
        printf("--------------------------------------------\n1. Unos vrednosti za matricu sa STD-a \n2. Unos vrednosti za matricu iz fila \n3. Generisanje matrice sa datim karakteristikama \n4. Pretraga matrice sa zadatim kljucem \n5. Evaluacija performansi pretrage\n--------------------------------------------");
        cout << "\nUnesite opciju: " << endl;
        cin >> Option;
        switch (Option)
        {
        case 0:
            exit(0);
            break;

        case 1:
            ptr = inputVector(v, &number, &n, &m);
            matrica = formMatrix(v, &n, &m);
            break;

        case 2:
            ptr = inputVectorThroughFile(v, &number, &n, &m);
            matrica = formMatrix(v, &n, &m);
            break;

        case 3:
            randMatrica = generateRandomMatrix(&randn, &randm);
            break;

        case 4:
            cout << "Upisite opciju za koju matricu zelite vrsiti pretragu:\n"
                 << "1. Zadata matrica\n"
                 << "2. Generisana matrica\n";
            cin >> matrixChoice;
            switch (matrixChoice)
            {
            case 1:
                searchAlgorithm(matrica, &n, &m);
                break;

            case 2:
                searchAlgorithm(randMatrica, &randn, &randm);
                break;
            }
            break;

        case 5:
            cout << "Upisite opciju za koju matricu zelite naci performanse:\n"
                 << "1. Zadata matrica\n"
                 << "2. Generisana matrica\n";
            cin >> matrixChoice;
            switch (matrixChoice)
            {
            case 1:
                createSeq(matrica, &n, &m, &random);
                break;

            case 2:
                createSeq(randMatrica, &randn, &randm, &random);
                break;
            }
            break;

        case 6:
            root = createTree(matrica, &n, &m, root);
            break;
        case 7:
            findB = binarySearch(root);
            break;
        case 8:
            cout << "Unesite kljuc koji zelite uneti u AVL stablo: " << endl;
            cin >> keyForInsert;
            root = insert(root, keyForInsert);
            break;
        case 9:
            displayTree(root, A);
            //printTree(root);
            break;

        case 10:
            inorderTraversal(root);
            break;

        default:
            break;
        }
    }
}