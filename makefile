BinarySearchTree: bstmain.o BST.o Phrase.o TNode.o
	g++ bstmain.o -o BinarySearchTree

bstmain.o: bstmain.cpp
	g++ -c bstmain.cpp

BST.o: BST.cpp BST.hpp
	g++ -c BST.cpp

Phrase.o: Phrase.cpp Phrase.hpp
	g++ -c Phrase.cpp

TNode.o: TNode.cpp TNode.hpp
	g++ -c TNode.cpp

clean:
	rm *.o BinarySearchTree
