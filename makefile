BalancedBST: MainPhrase.o StudentTreeInfo.o StudInf.o BST.o TNode.o
	g++ MainPhrase.o -o BalancedBST

MainPhrase.o: MainPhrase.cpp
	g++ -c MainPhrase.cpp

StudentTreeInfo.o: StudentTreeInfo.cpp StudentTreeInfo.hpp
	g++ -c StudentTreeInfo.cpp

StudInf.o: StudInf.cpp StudInf.hpp
	g++ -c StudInf.cpp

BST.o: BST.cpp BST.hpp
	g++ -c BST.cpp

TNode.o: TNode.cpp TNode.hpp
	g++ -c TNode.cpp

clean:
	rm *.o BalancedBST
