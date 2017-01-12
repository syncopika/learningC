/* binary search tree */

#include <stdio.h>
#include <stdlib.h>
#include "memcheck.h"

/* typedef the important parts */

/* node struct */
typedef struct node{

	int value;
	struct node *left;
	struct node *right;

} Node;

/* bst struct has a root */
typedef struct bst{

	Node *root;

} BST;

/* function prototypes */
void addNode(BST *tree, int value);
void addHelper(Node *n, int value);

void removeNode(BST *tree, int value);
void removeHelper(Node *n, int value);

Node *getMax(Node *n);
Node *getMin(Node *n);

int isLeaf(Node *n);

int search(BST *tree, int value);

void printTree(BST *tree);
void printTreeHelper(Node *n);

void freeTree(BST *tree);
void freeTreeHelper(Node *n);

void freeRoot(Node *n);

/* implement functions */

/*
*   add a new node to tree
*/
void addNode(BST *tree, int value){
	
	if(tree->root == NULL){
		Node *newNode = calloc(1, sizeof(Node));
		newNode->value = value;	
		tree->root = newNode;
		return;
	}
	addHelper(tree->root, value);
}

/*
*   add helper function
*/
void addHelper(Node *n, int value){

	/* check if value to be put in is smaller or larger than n->value */
	if(value <= (n->value)){
		/* go left */
		if(n->left == NULL){
			/* use calloc when dealing with NULL values ! */
			Node *newNode = calloc(1, sizeof(Node));
			newNode->value = value;
			n->left = newNode;
			return;
		}
		addHelper(n->left, value);
	}else if(value > (n->value)){
		/* go right */
		if(n->right == NULL){
			Node *newNode = calloc(1, sizeof(Node));
			newNode->value = value;
			n->right = newNode;
			return;
		}
		addHelper(n->right, value);
	}
}

/*
*   remove a node from the tree
*/
void removeNode(BST *tree, int value){
	
	Node *n = tree->root;
	
	/* if tree has no nodes yet */
	if(tree->root == NULL){
		return;
	}
	
	/* if tree only has one node */
	if(n->left == NULL && n->right == NULL && n->value == value){
		free(tree->root);
		tree->root = NULL;
		return;
	}
	
	/* if tree has more than 2 nodes */
	removeHelper(n, value);
}

/* remove helper */
void removeHelper(Node *n, int value){

	if(n == NULL){
		return;
	}
	
	/* base cases */
	if(n->left != NULL){
		if(n->left->value == value && isLeaf(n->left)){
			/* free that left node */
			free(n->left);
			n->left = NULL;
			return;
		}
	}
	if(n->right != NULL){
		if(n->right->value == value && isLeaf(n->right)){
			/* free that right node */
			free(n->right);
			n->right = NULL;
			return;
		}
	}
	
	/* if the node to remove is an inner node */
	if(!isLeaf(n) && (n->value == value)){
		/* replace the current node's value with either the MAX value from the left subtree, or
		the MIN value from the right subtree, whichever is available. */
		Node *max = getMax(n->left);
		Node *min = getMin(n->right);
		if(max != NULL){
			/* replacing value */
			n->value = max->value;
			/* now use recursion to remove that value used to replace the current node's */
			/* 
			   after replacing its value, 
			   if the left or right node shares the same target value as the current node's,
			   AND only if that left or right node is a leaf
			   start the recursion at the current node again
			   
			   otherwise move on at the left or right node, depending
			   on which subtree the replacement value is from. 
			 */
			if(n->left->value == n->value && isLeaf(n->left)){
				removeHelper(n, n->value);
			}else{
				removeHelper(n->left, n->value);
			}
		}else if(min != NULL){
			n->value = min->value;
			if(n->right->value == n->value && isLeaf(n->right)){
				removeHelper(n, n->value);
			}else{
				removeHelper(n->right, n->value);
			}
		}
	}else{
		if(value <= (n->value)){
			/* if the value to look for is less than current node's value, go left */
			removeHelper(n->left, value);
		}else if(value > (n->value)){
			removeHelper(n->right, value);
		}
	}
}

/* get max function 
   returns a pointer to the node with the max value
*/
Node *getMax(Node *n){
	
	if(n == NULL){
		return NULL;
	}
	
	Node *node = n;
	
	while(node->right != NULL){
		node = node->right;
	}
	
	return node;
}

/* get min function 
   returns a pointer to the node with the min value
*/
Node *getMin(Node *n){
	
	if(n == NULL){
		return NULL;
	}
	
	Node *node = n;
	
	while(node->left != NULL){
		node = node->left;
	}
	
	return node;
}

/* is the node a leaf? 1 if yes, 0 if no */
int isLeaf(Node *n){
	if(n == NULL){
		return 0;
	}
	if(n->left == NULL && n->right == NULL){
		return 1;
	}
	return 0;
}

/* search tree for particular value 
   returns 1 is present, 0 if cannot be found
*/
int search(BST *tree, int value){
	
	Node *n = tree->root;
	
	while(n != NULL){
		if(n->value == value){
			return 1;
		}
		
		if(value <= n->value){
			n = n->left;
		}else{
			n = n->right;
		}
	}
	return 0;
}

/*
	print tree in order
*/
void printTree(BST *tree){
	printTreeHelper(tree->root);
}

void printTreeHelper(Node *n){
	
	if(n == NULL){
		return;
	}
	/* in order traversal */
	printTreeHelper(n->left);
	printf("node value: %d\n", n->value);
	printTreeHelper(n->right);
}

/*
	free tree nodes
*/
void freeTree(BST *tree){
	
	/* if no nodes */
	if(tree->root == NULL){
		free(tree);
		return;
	}
	
	/* if single node tree */
	if(tree->root->left == NULL && tree->root->right == NULL){
		if(tree->root == NULL){
			free(tree);
		}else{
			free(tree->root);
			tree->root = NULL;
			free(tree);
		}
		return;
	}else{
		freeTreeHelper(tree->root);
		free(tree);
	}
}

void freeTreeHelper(Node *n){
	
	if(n == NULL){
		return;
	}
	
	/* post order allows the root to be taken care of last */
	freeTreeHelper(n->left);
	freeTreeHelper(n->right);
	
	/* no need to worry about if n is a leaf. because of this recursion,
	   n will always be a leaf node 
	*/
	free(n);
}

/*
	free the root. this one is special because it frees the left and right nodes, and then the root 
*/
void freeRoot(Node *n){
	
	if(n->left != NULL){
		free(n->left);
	}
	if(n->right != NULL){
		free(n->right);
	}
	free(n);
}

/* testing */
int main(void){
	
	/* use calloc when dealing with NULL values ! */
	BST *bst = calloc(1, sizeof(BST));
	
	addNode(bst, 5);
	addNode(bst, 4);
	addNode(bst, 3);
	addNode(bst, 2);
	addNode(bst, 1);

	printTree(bst);
	
	printf("removing node...\n");
	removeNode(bst, 5);
	removeNode(bst, 2);
	printTree(bst);
	
	freeTree(bst);

	print_memory_leaks();
	
	return 0;
	
}


