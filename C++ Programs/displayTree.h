#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node
{
	int key, height;
	Node *left, *right;
} Node;

int height(Node *tree);
void write(int pp, int offset, Node *root, char *side, int level);
void displayTree(Node *root);

int height(Node *tree)
{

	if (tree)
	{
		int lheight = height(tree->left);
		int rheight = height(tree->right);
		if (lheight > rheight)
			return lheight + 1;
		else
			return rheight + 1;
	}

	return -1;
}