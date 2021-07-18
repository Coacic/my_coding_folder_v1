#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#define INFINITY 999
#define SIZE 40
#define MAX 100
#define true 1
#define false 0

typedef struct AdjListNode
{
	int dest;
	struct AdjListNode* next;
} AdjListNode;

typedef struct AdjList
{
	AdjListNode* head;
} AdjList;

typedef struct Graph
{
	int V;
	AdjList* array;
	int* visited;
} Graph;

AdjListNode* newAdjListNode(int dest, int V)
{
	AdjListNode* newNode = (AdjListNode*)malloc((V + 1) * sizeof(AdjListNode));
	newNode->dest = dest;
	newNode->next = NULL;
	return newNode;
}

Graph* createGraph(int V)
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->V = V;
	graph->array = (AdjList*)malloc((V + 1) * sizeof(AdjList));
	graph->visited = malloc((V + 1) * sizeof(int) * V);

	int i;
	for (i = 0; i < V + 1; ++i)
	{
		graph->array[i].head = NULL;
		graph->visited[i] = 0;
	}
	return graph;
}

void addEdge(Graph* graph, int src, int dest, int V)
{
	AdjListNode* newNode = newAdjListNode(dest, V);
	newNode->next = graph->array[src].head;
	graph->array[src].head = newNode;
}

void printGraph(Graph* graph, int* weightedMatrix, char* lineMatrix)
{
	int v;
	for (v = 0; v < graph->V; ++v)
	{
		AdjListNode* temporary = graph->array[v].head;
		while (temporary)
		{
			if (lineMatrix[temporary->dest] == '\0')
			{
				printf("Element %c je povezan sa NULL, tezinom %d\n", lineMatrix[v], weightedMatrix[v]);
				temporary = temporary->next;
				continue;
			}

			printf("Element %c je povezan sa %c, tezinom %d\n", lineMatrix[v], lineMatrix[temporary->dest], weightedMatrix[v]);
			temporary = temporary->next;
		}
	}
}

void printGraphTopologicalSort(Graph* graph, int* weightedMatrix, char* lineMatrix, int* topologicalMatrix, int* zeroNodes)
{
	int v;
	for (v = 0; v < graph->V; ++v)
	{
		printf("%c", lineMatrix[topologicalMatrix[v]]);
		if (zeroNodes[v] != 0)
		{
			printf("Nulti node je: %d", v);
		}
	}

	printf("\n");
}

void FreeMemory(Graph* graph)
{
	int v;
	for (v = 0; v < graph->V; ++v)
	{
		AdjListNode* temporary = graph->array[v].head;
		while (temporary)
		{
			AdjListNode* tmp = temporary;
			temporary = temporary->next;
			free(tmp);
		}
		free(temporary);
	}
	free(graph->array);
	free(graph->visited);
	free(graph);
}
typedef struct stack
{
	int top;
	unsigned size;
	int* array;
} Stack;

Stack* createStack(unsigned size)
{
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	stack->size = size;
	stack->top = -1;
	stack->array = malloc(stack->size * sizeof(int));
	return stack;
}

int isStackFull(Stack* stack)
{
	return stack->top == stack->size - 1;
}

int isStackEmpty(Stack* stack)
{
	return stack->top == -1;
}

void pushToStack(Stack* stack, int item)
{
	if (isStackFull(stack))
		return;
	stack->array[++stack->top] = item;
}

int popFromStack(Stack* stack)
{
	if (isStackEmpty(stack))
		return INT_MIN;
	return stack->array[stack->top--];
}

int peekOnStack(Stack* stack)
{
	if (isStackEmpty(stack))
		return INT_MIN;
	return stack->array[stack->top];
}


void dfsTry(Graph* graph, int vertex, int n)
{
	AdjListNode* adjList = graph->array[vertex].head;
	AdjListNode* temp = adjList;
	Stack* stack = createStack(n);
	int increment = 0;

	graph->visited[vertex] = 1;
	printf("Visiting %d \n", vertex);
	pushToStack(stack, vertex);

	while (!isStackEmpty(stack))
	{
		int connectedVertex = popFromStack(stack);
		temp = graph->array[connectedVertex].head;

		if (graph->visited[connectedVertex] == 0)
		{
			printf("Cvor %d zavisi od %d\n", connectedVertex, vertex);
			graph->visited[connectedVertex] = 1;
		}
		while (temp)
		{
			int adjVertex = temp->dest;

			if (graph->visited[adjVertex] == 0)
			{
				pushToStack(stack, adjVertex);
			}
			temp = temp->next;
		}
		increment++;
	}
	for (int i = 0; i < n + 1; i++)
	{
		graph->visited[i] = 0;
	}

}

void dfs(Graph* graph, int vertex, int n, int* EF, int* LF, char* arrayOfCharacters)
{
	AdjListNode* adjList = graph->array[vertex].head;
	AdjListNode* temp = adjList;
	Stack* stack = createStack(n);
	int increment = 0,
		biggestEF,
		firstIn = 0;


	graph->visited[vertex] = 1;
	printf("Nodovi koji se posecuju su:\n%c", arrayOfCharacters[vertex]);
	pushToStack(stack, vertex);

	while (!isStackEmpty(stack))
	{
		int connectedVertex = popFromStack(stack);
		if (connectedVertex >= n)
		{
			break;
		}
		temp = graph->array[connectedVertex].head;

		if (graph->visited[connectedVertex] == 0)
		{
			printf("-> %c ", arrayOfCharacters[connectedVertex]);
			graph->visited[connectedVertex] = 1;
		}
		while (temp)
		{
			int adjVertex = temp->dest;

			if (graph->visited[adjVertex] == 0 && firstIn == 1)
			{
				if (biggestEF < EF[adjVertex])
				{
					biggestEF = EF[adjVertex];
					popFromStack(stack);
					pushToStack(stack, adjVertex);
				}
			}
			if (graph->visited[adjVertex] == 0 && firstIn == 0)
			{
				biggestEF = EF[adjVertex];
				pushToStack(stack, adjVertex);
				firstIn = 1;
			}


			temp = temp->next;
		}
		firstIn = 0;
		increment++;
	}
	for (int i = 0; i < n + 1; i++)
	{
		graph->visited[i] = 0;
	}
	free(stack->array);
	free(stack);
}

int isReachable(Graph* graph, int vertex, int n, char* arrayOfCharacters, int destination, int* LF, int* EF)
{
	AdjListNode* adjList = graph->array[vertex].head;
	AdjListNode* temp = adjList;
	Stack* stack = createStack(n);
	int increment = 0;

	graph->visited[vertex] = 1;
	pushToStack(stack, vertex);

	while (!isStackEmpty(stack))
	{
		int connectedVertex = popFromStack(stack);
		temp = graph->array[connectedVertex].head;

		if (graph->visited[connectedVertex] == 0)
		{
			graph->visited[connectedVertex] = 1;
			if (connectedVertex == destination)
			{
				for (int i = 0; i < n + 1; i++)
				{
					graph->visited[i] = 0;
				}
				free(stack->array);
				free(stack);
				return 1;
			}
		}
		while (temp)
		{
			int adjVertex = temp->dest;

			if (graph->visited[adjVertex] == 0)
			{
				if (adjVertex < n && EF[adjVertex] == LF[adjVertex])
				{
					pushToStack(stack, adjVertex);
				}
			}
			temp = temp->next;
		}
		increment++;
	}
	for (int i = 0; i < n + 1; i++)
	{
		graph->visited[i] = 0;
	}
	free(stack->array);
	free(stack);
	return 0;
}

int isLowerCaseLetter(char c)
{
	if ((c >= 'a') && (c <= 'z'))
		return 1;
	return 0;
}

int durationTable(char operator)
{
	int op;
	if ((int)operator== '+' || (int) operator== '-')
		op = 3;
	else if ((int)operator== '*')
		op = 2;
	else if ((int)operator== '/')
		op = 1;
	else
		op = 0;

	switch (op)
	{
	case 0:
		// AND OR XOR NOT
		return 1;
		break;

	case 1:
		// /
		return 23;
		break;

	case 2:
		//*
		return 10;
		break;

	case 3:
		// + -
		return 3;
		break;
	}
}

char* readLine()
{
	char* old_word = NULL, * new_word, c = 0;
	int i = 0;
	if (c == '\n')
	{
		return NULL;
	}
	while ((c = getchar()) != '\n')
	{
		new_word = realloc(old_word, (i + 1) * sizeof(char));
		if (!new_word)
		{
			printf("Mem greska");
			break;
		}
		else
		{
			old_word = new_word;
		}
		old_word[i] = c;
		i++;
	}
	new_word = realloc(old_word, (i + 1) * sizeof(char));
	if (!new_word)
	{
		printf("Mem greska");
		i--;
	}
	else
		old_word = new_word;
	old_word[i] = '\0';
	c = '\0';
	return old_word;
}

int isOperator(char op)
{
	if (((int)op == 'A') || ((int)op == 'O') || ((int)op == 'N') || ((int)op == 'X'))
		return 2;
	if (((int)op == '*') || ((int)op == '+') || ((int)op == '-') || ((int)op == '/'))
		return 1;
	return 0;
}

int stringLength(char* string)
{
	int counter = 0;
	for (int i = 0; i < strlen(string); i++)
	{
		if (string[i] != ' ')
		{
			counter++;
		}
	}
	return counter;
}

char** readLines(int* n, int arrayOfIntegers[MAX][MAX])
{
	char** Lines = NULL,
		* line,
		* arr;

	*n = 0;
	int*** tmpArrayOfIntegers = NULL;

	int lineLength = 0,
		increment,
		j = 0,
		x = 0,
		digitExists = 0,
		arrayIntegerIncrement = 0,
		operatorRead = 0;

	while (1)
	{
		operatorRead = 0;
		increment = 0;
		arr = readLine();
		line = calloc(5, sizeof(arr));
		memset(line, ' ', sizeof(arr));
		for (int i = 0; i < strlen(arr); i++)
		{
			if (isLowerCaseLetter(arr[i]))
			{
				line[increment++] = arr[i];
			}
			if (isOperator((int)arr[i]) == 1)
			{
				line[3] = arr[i];
				operatorRead = 1;
			}
			else if (isOperator((int)arr[i]) == 2)
			{
				line[3] = arr[i];
				i = i + 3;
				operatorRead = 1;
			}
			if (isdigit((int)arr[i]))
			{
				digitExists = 1;
				x = x * 10;
				x = x + arr[i] - 48;
			}
			if (digitExists == 1 && arr[i] == ' ')
			{
				if (operatorRead == 0)
				{
					arrayOfIntegers[(*n)][0] = x;
					x = 0;
					digitExists = 0;
				}
				else
				{
					arrayOfIntegers[(*n)][1] = x;
					x = 0;
					digitExists = 0;
				}
			}
			if ((i == strlen(arr) - 1) && digitExists == 1)
			{
				arrayOfIntegers[(*n)][1] = x;
				x = 0;
				digitExists = 0;
			}
		}
		line[4] = '\0';
		if (!stringLength(line))
		{
			free(arr);
			free(line);
			break;
		}
		Lines = realloc(Lines, (*n + 1) * sizeof(*Lines));
		Lines[((*n)++)] = line;

		free(arr);
	}

	return Lines;
}

int checkIfPresent(char* string, char c)
{
	int i = 0;
	while (string[i])
	{
		if (c == string[i])
		{
			return 1;
		}
		i++;
	}
	return 0;
}

int checkIfPresentInt(int* string, int c)
{
	int i = 0;
	while (string[i])
	{
		if (string[i] == c)
		{
			return 1;
		}
		i++;
	}
	return 0;
}

int findPosition(char* string, char c)
{
	for (int i = 0; i < strlen(string); i++)
	{
		if (c == string[i])
		{
			return i;
		}
	}
	return -1;
}

int FreeAllMemory(Graph* graph, char** Lines, int weightMatrix[MAX][MAX], int arrayOfIntegers[MAX][MAX], char* line, int* lengthTable, int* topologicalSortMatrix, int* zeroNodes, int* L, int* lengthTableReversed, int* successors, int* reverseTopologicalMatrix, int predecessorMatrix[MAX][MAX], int* ES, int* EF, int* LS, int* LF, int* LLF, int* LLS, int n, int* predecessorPosition, int* arrayOfNumbers, int successorMatrixTemp[MAX][MAX], int successorMatrix[MAX][MAX], int* noSuccessorsNode, int* reverseSuccessors, int* reverseTopologicalSortMatrix)
{
	FreeMemory(graph);
	for (int i = 0; i < n; ++i)
	{
		free(Lines[i]);
	}
	free(Lines);
	free(line);
	free(lengthTable);
	free(topologicalSortMatrix);
	free(zeroNodes);
	free(L);
	free(lengthTableReversed);
	free(successors);
	free(ES);
	free(EF);
	free(LF);
	free(LS);
	free(LLF);
	free(LLS);
	free(predecessorPosition);
	free(noSuccessorsNode);
	free(reverseSuccessors);
	printf("\nAll memory freed");
	return 0;
}

int CriticalPathFinding(Graph* graph, int* ES, int* EF, int* LS, int* LF, int* L, int* LLS, int* LLF, int weightMatrix[MAX][MAX], int* topologicalSortMatrix, char* arrayOfCharacters, int predecessorMatrix[MAX][MAX], int* lengthTable, int* reverseTopologicalSortMatrix, int* lengthTableReversed, int* successors, int n, int* reverseSuccessors, int successorMatrix[MAX][MAX], int* noSuccessorsNode, int* arrayOfNumbers, int* predecessorPosition, int successorMatrixTemp[MAX][MAX])
{
	int firstNode = 0;
	arrayOfNumbers = calloc(MAX, sizeof(int));

	for (int i = 0; i < n; i++)
	{
		firstNode = 0;
		for (int j = 0; j < n + 1; j++)
		{
			if (predecessorMatrix[topologicalSortMatrix[i] + 1][j] != 0)
			{
				if (EF[j] > ES[topologicalSortMatrix[i]])
					ES[topologicalSortMatrix[i]] = EF[j];
				if (ES[topologicalSortMatrix[i]] + lengthTable[j] > EF[topologicalSortMatrix[i]])
				{
					EF[topologicalSortMatrix[i]] = ES[topologicalSortMatrix[i]] + lengthTable[topologicalSortMatrix[i]];
					lengthTableReversed[i] = lengthTable[topologicalSortMatrix[i]];
				}
				firstNode = 1;
			}
		}
		if (firstNode == 0)
		{
			ES[topologicalSortMatrix[i]] = 0;
			EF[topologicalSortMatrix[i]] = lengthTable[topologicalSortMatrix[i]];
			lengthTableReversed[i] = lengthTable[topologicalSortMatrix[i]];
		}
	}
	for (int i = 0; i < n; i++)
	{
		LF[i] = INFINITY;
		LLF[i] = INFINITY;
	}
	LF[n - 1] = EF[topologicalSortMatrix[n - 1]];
	LS[n - 1] = EF[topologicalSortMatrix[n - 1]] - lengthTable[topologicalSortMatrix[n - 1]];
	LLF[n - 1] = EF[topologicalSortMatrix[n - 1]];
	LLS[n - 1] = EF[topologicalSortMatrix[n - 1]] - lengthTable[topologicalSortMatrix[n - 1]];

	int temp,
		increment = n - 1,
		positionForLF = n - 1;
	for (int j = 0; j < increment; j++)
	{
		temp = topologicalSortMatrix[increment];
		reverseTopologicalSortMatrix[increment] = topologicalSortMatrix[j];
		reverseTopologicalSortMatrix[j] = temp;
		increment--;

	}
	int counter = n - 1,
		tempCounter = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (weightMatrix[i][j] != 0)
			{
				tempCounter++;
			}
		}
		successors[i] = tempCounter;
		tempCounter = 0;
	}
	counter = 0;

	for (int i = 0; i < graph->V; i++)
	{

		AdjListNode* temporary = graph->array[topologicalSortMatrix[i]].head;
		while (temporary)
		{
			firstNode = 0;
			for (int j = 0; j < n + 1; j++)
			{
				if (predecessorMatrix[topologicalSortMatrix[i] + 1][j] != 0)
				{
					if (EF[j] > ES[topologicalSortMatrix[i]])
						ES[topologicalSortMatrix[i]] = EF[j];
					if (ES[topologicalSortMatrix[i]] + lengthTable[j] > EF[topologicalSortMatrix[i]])
					{
						EF[topologicalSortMatrix[i]] = ES[topologicalSortMatrix[i]] + lengthTable[topologicalSortMatrix[i]];
						lengthTableReversed[i] = lengthTable[topologicalSortMatrix[i]];
					}
					firstNode = 1;
				}
			}
			if (firstNode == 0)
			{
				ES[topologicalSortMatrix[i]] = 0;
				EF[topologicalSortMatrix[i]] = lengthTable[topologicalSortMatrix[i]];
				lengthTableReversed[i] = lengthTable[topologicalSortMatrix[i]];
			}


			temporary = temporary->next;

		}

		printf("%c  ES: %d  EF: %d\n", arrayOfCharacters[topologicalSortMatrix[i]], ES[topologicalSortMatrix[i]], EF[topologicalSortMatrix[i]]);
	}
	printf("\n\n");


	//Odredjivanje Ostalih vremena
	int noSuccesorNodesCount = 0,
		temporaryNode;
	for (int i = 0; i < n; i++)
	{
		if (successors[i] == 0)
			noSuccesorNodesCount++;
	}

	increment = n - 1;
	for (int j = 0; j < increment; j++)
	{
		temp = successors[increment];
		reverseSuccessors[increment] = successors[j];
		reverseSuccessors[j] = temp;
		increment--;
	}

	for (int j = 0; j < noSuccesorNodesCount; j++)
	{
		for (int i = 0; i < n; i++)
		{
			if (reverseSuccessors[i] == 0)
			{
				temporaryNode = i;
				reverseSuccessors[i] = -1;
				break;
			}

		}
	}
	for (int i = 0; i < graph->V; i++)
	{

		AdjListNode* temporary = graph->array[reverseTopologicalSortMatrix[i]].head;
		while (temporary)
		{
			firstNode = 0;
			for (int j = 0; j < n; j++)
			{
				if (temporary->dest < 8 && LLF[reverseTopologicalSortMatrix[i]] > LLF[temporary->dest])
				{
					LLF[reverseTopologicalSortMatrix[i]] = LLS[temporary->dest];
					LLS[reverseTopologicalSortMatrix[i]] = LLF[reverseTopologicalSortMatrix[i]] - lengthTable[reverseTopologicalSortMatrix[i]];
					firstNode = 1;
				}
			}
			if (firstNode == 0)
			{
				LLF[reverseTopologicalSortMatrix[i]] = EF[reverseTopologicalSortMatrix[i]];
				LLS[reverseTopologicalSortMatrix[i]] = LLF[reverseTopologicalSortMatrix[i]] - lengthTable[reverseTopologicalSortMatrix[i]];
				firstNode = 1;
			}



			temporary = temporary->next;

		}
		printf("%c  LLF: %d  LLS: %d\n", arrayOfCharacters[reverseTopologicalSortMatrix[i]], LLF[reverseTopologicalSortMatrix[i]], LLS[reverseTopologicalSortMatrix[i]]);
	}
	printf("\n");
	for (int i = 0; i < graph->V; i++)
	{

		AdjListNode* temporary = graph->array[i].head;
		while (temporary)
		{
			successorMatrix[i][temporary->dest] = 1;

			temporary = temporary->next;
		}
	}


	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{

			if (successorMatrix[i][j] != 0)
			{
				successorMatrix[i][j] = EF[topologicalSortMatrix[i]];
			}
			printf("%2d ", successorMatrix[j][i]);

		}
		printf("\n");
	}

	printf("\n\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%2d ", successorMatrix[i][j]);

		}
		printf("\n");
	}
	int incrementForNoSuccessorsNode = 0;
	counter = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			counter = counter + successorMatrix[i][j];
		}
		if (counter == 0)
		{
			noSuccessorsNode[incrementForNoSuccessorsNode++] = i;

		}
		else
			counter = 0;
	}

	int Node;
	Stack* stack = createStack(n + 1);

	for (int j = 0; j < noSuccesorNodesCount; j++)
	{
		firstNode = 0;
		Node = noSuccessorsNode[j];
		LF[Node] = EF[n - 1];
		LS[Node] = EF[n - 1] - lengthTable[Node];
		pushToStack(stack, Node);

		while (!isStackEmpty(stack))
		{
			if (peekOnStack(stack) != INT_MIN)
				Node = popFromStack(stack);


			for (int i = 0; i < n; i++)
			{
				if (successorMatrix[i][Node] != 0)
				{
					if (LF[i] > LS[Node] && firstNode == 1)
					{
						LF[i] = LS[Node];
						LS[i] = LF[i] - lengthTable[i];
						pushToStack(stack, i);
					}
					if (LF[i] > LS[Node] && firstNode == 0)
					{
						LF[i] = LS[Node];
						LS[i] = LF[i] - lengthTable[i];
						pushToStack(stack, i);
						firstNode = 1;
					}
				}
			}
		}
	}
	for (int i = 0; i < n; i++)
	{
		printf("LF : %d   LS : %d\n", LF[i], LS[i]);
	}

	counter = 0;
	int numberOfNodesWithNoPredecessors = 0,
		start,
		incrementForSuccessors = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (predecessorMatrix[i + 1][j] != 0)
			{
				arrayOfNumbers[i] = 0;
				j++;
				break;
			}
			if (EF[i] == LF[i])
			{
				arrayOfNumbers[i] = 1;
			}
		}
	}
	numberOfNodesWithNoPredecessors = 0;
	for (int i = 0; i < n; i++)
	{
		if (arrayOfNumbers[i] == 1)
		{
			numberOfNodesWithNoPredecessors++;
		}
	}

	for (int i = 0; i < numberOfNodesWithNoPredecessors; i++)
	{

		for (int j = 0; j < n; j++)
		{
			if (arrayOfNumbers[j] == 1)
			{
				start = j;
				arrayOfNumbers[j] = 0;
				break;
			}

		}
		if (isReachable(graph, start, n, arrayOfCharacters, reverseTopologicalSortMatrix[0], LLF, EF) == 1)
		{
			free(stack->array);
			free(stack);
			free(reverseTopologicalSortMatrix);
			free(arrayOfNumbers);
			return start;
		}



	}
	free(stack->array);
	free(stack);
	free(arrayOfNumbers);
	free(reverseTopologicalSortMatrix);

}

void findPredecessors(Graph* graph, int* ES, int* EF, int* LS, int* LF, int* L, int weightMatrix[MAX][MAX], int* topologicalSortMatrix, char* line, int predecessorMatrix[MAX][MAX], int n)
{
	int StartingNode = 0,
		nodeIncrement = 0;
	for (int i = 0; i < n + 1; i++)
		for (int j = 0; j < n + 1; j++)
			predecessorMatrix[i][j] = 0;



	for (int v = 0; v < n - 1; v++)
	{
		AdjListNode* temporary = graph->array[v].head;
		while (temporary)
		{
			predecessorMatrix[temporary->dest + 1][v] = 1;
			printf("%d", temporary->dest + 1);
			temporary = temporary->next;
		}
		printf("\n");
	}

	for (int i = 1; i < n + 1; i++)
	{
		for (int j = 0; j < n + 1; j++)
		{
			printf("%3d", predecessorMatrix[i][j]);
		}
		printf("\n");
	}
}

int* TopologicalSort(Graph* graph, char* lineMatrix, int* weightedMatrix, int* zeroNodes, int* topologicalSortMatrix, int n)
{
	int v,
		** NumberOfVertices = NULL,
		* integerMatrica = NULL;
	NumberOfVertices = calloc(n, sizeof(int*));
	for (int i = 0; i < n; i++)
	{
		NumberOfVertices[i] = calloc(n, sizeof(int));
	}
	integerMatrica = calloc(n, sizeof(int));
	AdjListNode* start = graph->array[0].head;


	for (v = 0; v < graph->V; ++v)
	{
		AdjListNode* temporary = graph->array[v].head;
		while (temporary)
		{
			if (lineMatrix[temporary->dest] == '\0')
			{
				temporary = temporary->next;
				continue;
			}

			integerMatrica[temporary->dest] = integerMatrica[temporary->dest] + 1;
			temporary = temporary->next;
		}
	}
	int degreeOfNode = 0,
		firstZero = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (integerMatrica[j] == 0 && firstZero == 0)
			{
				topologicalSortMatrix[degreeOfNode++] = j;
				zeroNodes[j] = 1;
			}
			else if (integerMatrica[j] == 0)
			{
				topologicalSortMatrix[degreeOfNode++] = j;
			}
		}
		firstZero = 1;
		for (int m = 0; m < n; m++)
		{
			integerMatrica[m] = integerMatrica[m] - 1;
		}
	}

	for (int i = 0; i < n; i++)
	{
		free(NumberOfVertices[i]);
	}
	free(NumberOfVertices);
	free(integerMatrica);

	return topologicalSortMatrix;
}

void floydWarshall(int weightMatrix[MAX][MAX], int dist[MAX][MAX], int V, char* line)
{
	int i, j, k;

	for (i = 0; i < V; i++)
	{
		for (j = 0; j < V; j++)
		{
			if (weightMatrix[i][j] != 0)
			{
				dist[i][j] = weightMatrix[i][j];
			}
			else
			{
				dist[i][j] = INFINITY;
			}
			if (i == j)
			{
				dist[i][j] = 0;
			}
		}
	}

	for (k = 0; k < V; k++)
	{
		for (i = 0; i < V; i++)
		{
			for (j = 0; j < V; j++)
			{
				if (dist[i][k] + dist[k][j] < dist[i][j])
					dist[i][j] = dist[i][k] + dist[k][j];
			}
		}
	}

	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			printf("%5d", dist[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	for (int i = 0; i < V; i++)
	{
		for (int j = 0; j < V; j++)
		{
			if (dist[i][j] != 0 && dist[i][j] != 999)
			{
				printf("Element %c ima criticni path tezine %d do elementa %c\n", line[i], dist[i][j], line[j]);
			}
		}
	}
}

int PrintTransitiveNodes(Graph* graph, int vertex, int n, char* arrayOfCharacters, int weightMatrix[MAX][MAX], int predecessorMatrix[MAX][MAX])
{
	AdjListNode* adjList = graph->array[vertex].head;
	AdjListNode* temp = adjList;
	Stack* stack = createStack(n);
	int CountOfNodes = 0,
		biggestEF,
		firstIn = 0,
		increment = 0,
		incrementNodes = 0,
		* arrayOfStartNodes = NULL,
		incrementForNodes = 0,
		numberOfTransitiveNodes = 0;

	while (adjList)
	{
		incrementNodes++;
		adjList = adjList->next;
	}

	arrayOfStartNodes = calloc(n, sizeof(int));
	adjList = graph->array[vertex].head;
	while (incrementNodes > 0)
	{
		arrayOfStartNodes[incrementForNodes++] = adjList->dest;
		adjList = adjList->next;
		incrementNodes--;
	}

	graph->visited[vertex] = 1;
	printf("%c", arrayOfCharacters[vertex]);
	pushToStack(stack, vertex);

	while (!isStackEmpty(stack))
	{
		int connectedVertex = popFromStack(stack);
		temp = graph->array[connectedVertex].head;

		if (graph->visited[connectedVertex] == 0 && checkIfPresentInt(arrayOfStartNodes, connectedVertex) == 0)
		{
			if (weightMatrix[vertex][connectedVertex] != 0)
			{
				printf("Grana %d je tranzitivna sa %d", connectedVertex, vertex);
				numberOfTransitiveNodes++;

			}
			graph->visited[connectedVertex] = 1;
		}
		while (temp)
		{
			int adjVertex = temp->dest;

			if (graph->visited[adjVertex] == 0)
			{
				pushToStack(stack, adjVertex);
			}
			temp = temp->next;
		}
		increment++;
	}
	printf("\n");
	for (int i = 0; i < n + 1; i++)
	{
		graph->visited[i] = 0;
	}
	if (numberOfTransitiveNodes != 0)
	{
		printf("Broj tranzitivnih grana je: %d\n", numberOfTransitiveNodes);
	}
	else if (numberOfTransitiveNodes == 0)
	{
		printf("Nema tranzitivnih grana!\n");
	}
	free(arrayOfStartNodes);
	free(stack->array);
	free(stack);
}

void printByTact(Graph* graph, int* ES, int* EF, int* LS, int* LF, int* L, int* LLS, int* LLF, int weightMatrix[MAX][MAX], int* topologicalSortMatrix, char* arrayOfCharacters, int predecessorMatrix[MAX][MAX], int* lengthTable, int* reverseTopologicalSortMatrix, int* lengthTableReversed, int* successors, int n, int* reverseSuccessors, int successorMatrix[MAX][MAX], int* noSuccessorsNode, int* arrayOfNumbers, int* predecessorPosition, int successorMatrixTemp[MAX][MAX], int CriticalPathStart)
{
	AdjListNode* adjList = graph->array[arrayOfCharacters[0] - 97].head,
		* temp = adjList;
	Stack* stack = createStack(n);
	int LengthOfCurrent = EF[arrayOfCharacters[0] - 97] - ES[arrayOfCharacters[0] - 97],
		timesToPrint = LS[arrayOfCharacters[0] - 97],
		incrementForCharacters = 0,
		increment = 1,
		* copyOfLS = calloc(n, sizeof(int)),
		* orderOfPrint = calloc(n, sizeof(int)),
		tempNode = 0,
		incrementForOrder = 1,
		howManyNodes = 0,
		ifWritten = 0;
	orderOfPrint[0] = arrayOfCharacters[0] - 97;

	graph->visited[tempNode] = 1;
	printf("Visiting %d \n", tempNode);
	pushToStack(stack, tempNode);

	while (!isStackEmpty(stack))
	{
		int connectedVertex = popFromStack(stack);
		temp = graph->array[connectedVertex].head;

		if (graph->visited[connectedVertex] == 0)
		{
			if (connectedVertex < n) {
				orderOfPrint[incrementForOrder++] = connectedVertex;
				howManyNodes++;
			}
			graph->visited[connectedVertex] = 1;
		}
		while (temp)
		{
			int adjVertex = temp->dest;

			if (graph->visited[adjVertex] == 0)
			{
				pushToStack(stack, adjVertex);
			}
			temp = temp->next;
		}
		increment++;
	}
	for (int i = 0; i < n + 1; i++)
	{
		graph->visited[i] = 0;
	}


	for (int i = 0; i < n; i++)
	{
		copyOfLS[i] = LS[i];
	}

	increment = 0;
	for (int i = 0; i < LF[n - 1] + 1; i++)
	{
		printf("%d : ", i);
		ifWritten = 0;
		for (int j = 0; j < howManyNodes; j++)
		{
			if (increment >= ES[orderOfPrint[j]] && copyOfLS[orderOfPrint[j]] >= increment)
			{
				printf("%c ", arrayOfCharacters[orderOfPrint[j]]);
				copyOfLS[orderOfPrint[j]];
				ifWritten = 1;
			}
		}
		if (ifWritten == 0)
		{
			printf("X");
		}
		printf("\n");
		increment++;
	}

	timesToPrint--;
	free(copyOfLS);
	free(orderOfPrint);
	free(stack->array);
	free(stack);
}

int main()
{
	char** Lines = NULL,
		* line = NULL;
	int n,
		j = 1,
		i = 0,
		dijkstraOption = 0,
		option = 0,
		stringLength = 0,
		stringLines = 0,
		CriticalPathStart = -1,
		weightMatrix[MAX][MAX],
		* lengthTable = NULL,
		matrixIncrement = 0,
		written = 0,
		positionWhatChar = 0,
		positionToWho = 0,
		IteratingMatrixIncrement = 0,
		arrayOfIntegers[MAX][MAX],
		* topologicalSortMatrix = NULL,
		* zeroNodes = NULL,
		* ES = NULL,
		* EF = NULL,
		* LF = NULL,
		* LS = NULL,
		* L = NULL,
		* LLS = NULL,
		* LLF = NULL,
		predecessorMatrix[MAX][MAX],
		* reverseTopologicalSortMatrix = NULL,
		* lengthTableReversed = NULL,
		* successors = NULL,
		* predecessorPosition = NULL,
		* arrayOfNumbers = NULL,
		successorMatrixTemp[MAX][MAX],
		successorMatrix[MAX][MAX],
		* noSuccessorsNode = NULL,
		* reverseSuccessors = NULL,
		dist[MAX][MAX],
		firstElement = -1;

	Graph* graph = NULL;

	for (int i = 0; i < MAX; i++)
	{
		memset(arrayOfIntegers[i], 0, MAX);
		memset(weightMatrix[i], 0, MAX);
	}

	while (true)
	{
		printf("------------------------------------------------------------------------------------------\n0. Exit\n1. Unos elemenata grapha\n2. Printuj matricu tezine\n3. Printuj Graph\n4. Nalazenje nenulte vrednosti\n5. Warshallov algoritam\n6. Prikaz matrice\n7. Odredjivanje kriticnog puta\n8. Trazenje tranzistivnih grana\n9. Ispis po taktovima operacije\n------------------------------------------------------------------------------------------\n");
		option = getchar() - 48;
		getchar();
		switch (option)
		{
		case 1:
			Lines = readLines(&n, arrayOfIntegers);
			ES = calloc(n, sizeof(int));
			EF = calloc(n, sizeof(int));
			LF = calloc(n, sizeof(int));
			LS = calloc(n, sizeof(int));
			LLF = calloc(n, sizeof(int));
			LLS = calloc(n, sizeof(int));
			predecessorPosition = calloc(n, sizeof(int));
			noSuccessorsNode = calloc(n, sizeof(int));
			reverseSuccessors = calloc(n, sizeof(int));
			lengthTableReversed = calloc(n, sizeof(int));
			successors = calloc(n, sizeof(int));
			topologicalSortMatrix = calloc(n + 1, sizeof(int));
			reverseTopologicalSortMatrix = calloc(n + 1, sizeof(int));
			zeroNodes = calloc(n, sizeof(int));
			for (int i = 0; i < MAX; i++)
			{
				memset(successorMatrix, 0, sizeof(successorMatrix));
			}
			line = (char*)malloc(3 * (n + 2) * sizeof(char));
			graph = createGraph(n);
			for (i = 0; i < n; i++)
			{
				stringLength = strlen(Lines[i]);

				for (int j = 0; j < strlen(Lines[i]); j++)
				{
					if (!(checkIfPresent(line, Lines[i][0])) && (isLowerCaseLetter(Lines[i][j])))
					{
						line[stringLines++] = Lines[i][0];
					}
				}
			}
			line[stringLines++] = '\0';

			lengthTable = malloc((n + 1) * sizeof(int));
			for (int i = 0; i < n; i++)
			{
				lengthTable[i] = durationTable((int)Lines[i][3]);
			}

			for (int i = 0; i < n; i++)
			{
				for (int j = 1; j < 3; j++)
				{
					if (checkIfPresent(line, Lines[i][j]))
					{
						positionWhatChar = findPosition(line, Lines[IteratingMatrixIncrement][j]);
						positionToWho = findPosition(line, Lines[IteratingMatrixIncrement][0]);
						weightMatrix[positionWhatChar][positionToWho] = lengthTable[positionWhatChar];
						weightMatrix[IteratingMatrixIncrement][n] = 0;
						matrixIncrement = 0;
						written = 1;
					}
					else
					{
						if (written != 1)
							weightMatrix[IteratingMatrixIncrement][n] = durationTable((int)Lines[IteratingMatrixIncrement][3]);
					}
				}
				IteratingMatrixIncrement++;
				written = 0;
			}

			for (int i = 0; i < (n); i++)
			{
				for (int j = 0; j < (n); j++)
				{
					if (weightMatrix[i][j] != 0)
					{
						weightMatrix[i][n] = 0;
						i++;
						j = 0;
					}
				}
				weightMatrix[i][n] = lengthTable[i];
			}

			for (int i = 0; i < (n); i++)
			{
				for (int j = 0; j < (n + 1); j++)
				{
					if (weightMatrix[i][j] != 0)
					{
						addEdge(graph, i, j, n);
					}
				}
			}
			break;

		case 2:
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < (n + 1); j++)
				{
					printf("%3d", weightMatrix[i][j]);
				}
				printf("\n");
			}
			break;

		case 3:
			for (int i = 0; i < n; i++)
				printf("%c ", line[i]);
			printGraph(graph, lengthTable, line);
			break;

		case 8:
			for (int node = 0; node < n; node++)
			{
				PrintTransitiveNodes(graph, node, n, line, weightMatrix, predecessorMatrix);
			}
			break;

		case 7:
			CriticalPathStart = CriticalPathFinding(graph, ES, EF, LS, LF, L, LLS, LLF, weightMatrix, topologicalSortMatrix, line, predecessorMatrix, lengthTable, reverseTopologicalSortMatrix, lengthTableReversed, successors, n, reverseSuccessors, successorMatrix, noSuccessorsNode, arrayOfNumbers, predecessorPosition, successorMatrixTemp);
			printf("Duzina kriticnog puta je: %d i CriticalPath Start je: %d\n", EF[n - 1], CriticalPathStart);
			for (int i = 0; i < n; i++)
			{
				if (LLS[i] == 0)
					firstElement = i;
			}
			dfs(graph, CriticalPathStart, n, EF, LF, line);
			printf("\n");
			break;

		case 4:
			topologicalSortMatrix = TopologicalSort(graph, line, lengthTable, zeroNodes, topologicalSortMatrix, n);
			for (int i = 0; i < n; i++)
			{
				printf("%d ", zeroNodes[i]);
			}
			printGraphTopologicalSort(graph, lengthTable, line, topologicalSortMatrix, zeroNodes);
			break;

		case 5:
			floydWarshall(weightMatrix, dist, n, line);
			break;

		case 9:
			printByTact(graph, ES, EF, LS, LF, L, LLS, LLF, weightMatrix, topologicalSortMatrix, line, predecessorMatrix, lengthTable, reverseTopologicalSortMatrix, lengthTableReversed, successors, n, reverseSuccessors, successorMatrix, noSuccessorsNode, arrayOfNumbers, predecessorPosition, successorMatrixTemp, CriticalPathStart);
			break;

		case 6:
			findPredecessors(graph, ES, EF, LS, LF, L, weightMatrix, topologicalSortMatrix, line, predecessorMatrix, n);
			break;

		case 0:
			FreeAllMemory(graph, Lines, weightMatrix, arrayOfIntegers, line, lengthTable, topologicalSortMatrix, zeroNodes, L, lengthTableReversed, successors, reverseTopologicalSortMatrix, predecessorMatrix, ES, EF, LS, LF, LLF, LLS, n, predecessorPosition, arrayOfNumbers, successorMatrixTemp, successorMatrix, noSuccessorsNode, reverseSuccessors, reverseTopologicalSortMatrix);
			exit(1);
			break;

		default:
			printf("Unesite validnu opciju:\n");
			break;
		}
	}

	return 0;
}