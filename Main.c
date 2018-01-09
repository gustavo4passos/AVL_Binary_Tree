#include "AVLTree.h"
#include <stdio.h>

#define WAIT() printf("Press any key to continue...");\
	getchar()

#define PRINT(x) printNicely(x);\
	printf("\n")

int main(int argc, char* argv[]) {
	AVLTree* tree = createTree();
	for(int i = 0; i < 16; i++) {
		insert(tree, i);
	}

	PRINT(tree->root);
	printf("\n");

	int keyToSearch = 1;
	
	while(keyToSearch >= 0) {
		printf("What key do  you want to search? >> ");
		scanf("%i", &keyToSearch);

		Node* query = search(tree, keyToSearch);
		if(query) {
			printf("Key found. Height is: %i and balance is: %i\n", query->height, query->balance);
		}
		else {
			printf("Key is not in tree.\n");
		}
	}

	WAIT();

	return 0;
}