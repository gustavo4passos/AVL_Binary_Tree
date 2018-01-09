Main: Main.o AVLTree.o
	gcc Main.o AVLTree.o -o Main

Main.o: Main.c
	gcc -c Main.c

AVLTree.o: AVLTree.c AVLTree.h
	gcc -c AVLTree.c
