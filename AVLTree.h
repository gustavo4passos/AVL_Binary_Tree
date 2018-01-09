#ifndef AVLTREE_H
#define AVLTREE_H

typedef struct node {
	int key;
	struct node* right;
	struct node* left;
	struct node* father;
	int height;
	int balance;
	int deepth;
} Node;

typedef struct avlTree {
	Node* root;
	int size;
} AVLTree;

AVLTree* createTree();
Node* createNode(int key);
void insert(AVLTree* tree, int key);
void remove_key(AVLTree* tree, int key);
void updateHeight(Node* node);
void insertNode(AVLTree* tree, Node* node, int key);
void printNicely(Node* node);
void rotateRight(AVLTree* tree, Node* left, Node* top);
void rotateLeft(AVLTree* tree, Node* topNode, Node* rightNode);
Node* search(AVLTree* tree, int key);
Node* searchSubtree(Node* node, int key);

#endif