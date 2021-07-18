#include <stddef.h> 
#include <stdio.h>
#include <stack>
using namespace std; 

struct Zivotinja 
{ 
	struct Zivotinja *left, *right; 
	int info; 
	bool lthread; 
	bool rthread; 
}; 

struct Zivotinja *insert(struct Zivotinja *root, int ikey) 
{ 
	Zivotinja *ptr = root; 
	Zivotinja *par = NULL;
	while (ptr != NULL) 
	{ 
		if (ikey == (ptr->info)) 
		{ 
			printf("Duplicate Key !\n"); 
			return root; 
		} 

		par = ptr;

		if (ikey < ptr->info) 
		{ 
			if (ptr -> lthread == false) 
				ptr = ptr -> left; 
			else
				break; 
		} 

		else
		{ 
			if (ptr->rthread == false) 
				ptr = ptr -> right; 
			else
				break; 
		} 
	} 

	Zivotinja *tmp = new Zivotinja; 
	tmp -> info = ikey; 
	tmp -> lthread = true; 
	tmp -> rthread = true; 

	if (par == NULL) 
	{ 
		root = tmp; 
		tmp -> left = NULL; 
		tmp -> right = NULL; 
	} 
	else if (ikey < (par -> info)) 
	{ 
		tmp -> left = par -> left; 
		tmp -> right = par; 
		par -> lthread = false; 
		par -> left = tmp; 
	} 
	else
	{ 
		tmp -> left = par; 
		tmp -> right = par -> right; 
		par -> rthread = false; 
		par -> right = tmp; 
	} 

	return root; 
} 

struct Zivotinja *inorderSuccessor(struct Zivotinja *ptr) 
{ 
	if (ptr -> rthread == true) 
		return ptr->right; 

	ptr = ptr -> right; 
	while (ptr -> lthread == false) 
		ptr = ptr -> left; 
	return ptr; 
} 

void inorder(struct Zivotinja *root) 
{ 
	if (root == NULL) 
		printf("Tree is empty"); 

	struct Zivotinja *ptr = root; 
	while (ptr -> lthread == false) 
		ptr = ptr -> left; 

	while (ptr != NULL) 
	{ 
		printf("%d ",ptr -> info); 
		ptr = inorderSuccessor(ptr); 
	} 
} 

void iterativePreorder(struct Zivotinja* root) 
{ 
    if (root == NULL) 
        return; 
  
    stack<Zivotinja*> nodeStack; 
    nodeStack.push(root); 
  
    /* Pop all items one by one. Do following for every popped item 
       a) print it 
       b) push its right child 
       c) push its left child 
    Note that right child is pushed first so that left is processed first */
    while (nodeStack.empty() == false) { 
        // Pop the top item from stack and print it 
        struct Zivotinja* Node = nodeStack.top(); 
        printf("%d ", Node->info); 
        nodeStack.pop(); 
  
        // Push right and left children of the popped Node to stack 
        if (Node->right && Node->rthread == false) 
            nodeStack.push(Node->right); 
        if (Node->left && Node->lthread == false) 
            nodeStack.push(Node->left); 
    } 
} 

int main() 
{ 
	struct Zivotinja *root = NULL; 

	root = insert(root, 20); 
	root = insert(root, 10); 
	root = insert(root, 30); 
	root = insert(root, 5); 
	root = insert(root, 16); 
	root = insert(root, 14); 
	root = insert(root, 17); 
	root = insert(root, 13); 

	//inorder(root); 
	iterativePreorder(root);

	return 0; 
} 
