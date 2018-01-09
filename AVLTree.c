#include "AVLTree.h"
#include <malloc.h>
#include <stdio.h>

AVLTree* createTree() {
	AVLTree* tmp = malloc(sizeof(AVLTree));
	if(tmp) {
		tmp->root = NULL;
		tmp->size = 0;
		return tmp;
	}
	return NULL;
}

Node* createNode(int key) {
	Node* tmp = malloc(sizeof(Node));

	if(tmp) {
		tmp->key = key;
		tmp->father = NULL;
		tmp->right = NULL;
		tmp->left = NULL;
	}

	return tmp;
}

void insert(AVLTree* tree, int key) {
	if(tree){
		tree->size++;
		Node* tmp = malloc(sizeof(Node));
		if(!tree->root) {		
			tree->root = createNode(key);
			tree->root->height = 1;
		}
		else {
			insertNode(tree, tree->root, key);
		}
	}
}

void insertNode(AVLTree* tree, Node* node, int key) {
	if(key < node->key) {
		if(!node->left) {
			Node* tmp = createNode(key);
			tmp->father = node;
			node->left = tmp;
		}
		else {
			insertNode(tree, node->left, key);
		}
	}
	else {
		if(!node->right) {
			Node* tmp = createNode(key);
			tmp->father = node;
			node->right = tmp;
		}
		else {
			insertNode(tree, node->right, key);
		}
	}

	updateHeight(node);
	// If tree is unbalanced
	if(node->balance > 1 || node->balance < -1) {
		if(node->balance > 1) {
			if(node->left->balance > 0) {
				rotateRight(tree, node->left, node);
			}
			else {
				rotateLeft(tree, node->left, node->left->right);
				rotateRight(tree, node, node->left);			
			}
		}
		else if(node->balance < -1) {
			if(node->right->balance < 0) {
				rotateLeft(tree, node, node->right);
			}
			else {
				rotateRight(tree,  node->right->left, node->right);
				rotateLeft(tree, node, node->right);
			}
		}
		updateHeight(node->father);
	}
}

void updateHeight(Node* node) {
	if(!node) return;
	if(!node->left && !node->right) {
		node->height = 1;
		node->balance = 0;
		return;
	}
	updateHeight(node->left);
	updateHeight(node->right);
	if(!node->left) {
		node->height = node->right->height + 1;
		node->balance = -node->right->height;
		return;
	}
	if(!node->right) {
		node->height = node->left->height + 1;
		node->balance = node->left->height;
		return;
	}
	node->height = (node->left->height > node->right->height) ? node->left->height + 1 : node->right->height + 1;
	node->balance = node->left->height - node->right->height;
}

void printNicely(Node* node) {
	if(node) {
		printf("%d'%d'(e:", node->key, node->height);
		printNicely(node->left);
		printf("d:");
		printNicely(node->right);
		printf(")");
	}
}

void rotateRight(AVLTree* tree, Node* leftNode, Node* topNode) {
	topNode->left = leftNode->right;
	leftNode->right = topNode;
	if(topNode->left) topNode->left->father = topNode;
	leftNode->father = topNode->father;
	topNode->father = leftNode;

	if(!leftNode->father) tree->root = leftNode;
	else leftNode->father->left = leftNode;
}

void rotateLeft(AVLTree* tree, Node* topNode, Node* rightNode)	{
	topNode->right = rightNode->left;
	rightNode->left = topNode;
	if(topNode->right) topNode->right->father = topNode;
	rightNode->father = topNode->father;
	topNode->father = rightNode;

	if(!rightNode->father) tree->root = rightNode;
	else rightNode->father->right = rightNode;
}

Node* search(AVLTree* tree, int key) {
	return searchSubtree(tree->root, key);
}

Node* searchSubtree(Node* node, int key) {
	if(!node) return NULL;
	if(node->key == key) return node;
	if(key < node->key) return searchSubtree(node->left, key);
	else return searchSubtree(node->right, key);
}