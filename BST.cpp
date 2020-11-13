/*Note: you must create the BST.cpp file.  I'm only including a few
Otherwise, as specified in the directions, you must write the BST.cpp.
including the method definitions to accompany the method declarations
in BST.hpp
*/
#include "BST.hpp"
#include "TNode.hpp"
#include <iostream>
#include <string>


BST::BST() {
	root = NULL;
}
BST::BST(string sarr[]) {
	root = new TNode(sarr);
}

bool BST::insert(string sarr[]){
	if(root == NULL){
		root = new TNode(sarr);
		return true;
	} else if (find(sarr[0], sarr[3])){
		cout << "Already in tree: " << sarr[0] << ", " << sarr[3] << endl;
	} else {
		TNode *n = root;
		string sF = sarr[3];
		string sL = sarr[0];
		while (n != NULL){


			bool left = false;
			bool useFirst = false;
			if(sL.compare(n->student->last) == 0){
				useFirst = true;
				if (sF.compare(n->student->last) < 0){
					left = true;
				}

			}

			if (sL.compare(n->student->last) < 0 || (useFirst && left)){
				if (n->left == NULL){
					n->left = new TNode(sarr);
					n->left->parent = n;
					setHeight(n);
					return true;
				} else {
					n = n->left;
				}
			} else if (sL.compare(n->student->last) > 0 || (useFirst && !left)){
				if (n->right == NULL){
					n->right = new TNode(sarr);
					n->right->parent = n;
					setHeight(n);
					return true;
				} else {
					n = n->right;
				}
			} else {
				return false;
			}
		}
	}
	return false;
}

TNode *BST::find(string l, string f){
	TNode *n = root;
	int c = 1;
	while (n){
		if (l.compare(n->student->last) == 0 && f.compare(n->student->first) == 0){
			break;
		} else if (l.compare(n->student->last) < 0 || (l.compare(n->student->last) == 0 && f.compare(n->student->first) < 0)){
				n = n->left;
		} else if (l.compare(n->student->last) > 0 || (l.compare(n->student->last) == 0 && f.compare(n->student->first) > 0)){
			n = n->right;
		}
		c++;
	}
	if(n){
		cout << "Found " << n->student->last << ": number of comparisons: " << c << endl;
	} else {
		cout << "not found" << endl;
	}
	return n;

}

void BST::printTreeIO() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing In Order:" <<endl;
		printTreeIO(root);
	}
}

void BST::printTreeIO(TNode *n){
	if (n->left){
		printTreeIO(n->left);
	}
	n->printNode();
	if(n->right){
		printTreeIO(n->right);
	}
}


void BST::printTreePre() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PreOrder:" <<endl;
		printTreePre(root);
	}
}


void BST::printTreePre(TNode *n){
	n->printNode();
	if (n->left){
		printTreePre(n->left);
	}
	if (n->right){
		printTreePre(n->right);
	}
}


void BST::printTreePost() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PostOrder:" <<endl;
		printTreePost(root);
	}
}


void BST::printTreePost(TNode *n){
	if (n->left){
		printTreePost(n->left);
	}
	if (n->right){
		printTreePost(n->right);
	}
	n->printNode();
}


void BST::clearTree() {
	if (root == NULL) {
		cout << "Tree already empty" << endl;
	}
	else {
		cout << endl << "Clearing Tree:" << endl;
		clearTree(root);
		root = NULL;
	}
}
void BST::clearTree(TNode *tmp) {
	if (tmp == NULL) {
		return;
	}
	else {
		clearTree(tmp->left);
		clearTree(tmp->right);
		tmp->printNode();
		delete(tmp);
	}
}


TNode *BST::removeNoKids(TNode *tmp){
	if (root == tmp){
		root = NULL;
	} else if(tmp->parent->left == tmp){
		tmp->parent->left = NULL;
		setHeight(tmp->parent);
	} else if(tmp->parent->right == tmp){
		tmp->parent->right = NULL;
		setHeight(tmp->parent);
	}
	free(tmp);
	return tmp;
}


TNode *BST::removeOneKid(TNode *tmp, bool leftFlag){
	TNode *c = tmp->right;
	if(leftFlag){
		c = tmp->left;
	}

	if (root == tmp){
		root = c;
		setHeight(root);
	} else if (tmp->parent->left == tmp){
		c->parent = tmp->parent;
		c->parent->left = c;
		setHeight(tmp->parent);
	} else if (tmp->parent->right == tmp){
		c->parent = tmp->parent;
		c->parent->right = c;
		setHeight(tmp->parent);
	}
	free(tmp);
	return tmp;
}

TNode *BST::remove(string s, string l){
	TNode *tmp = find(s,l);
	if(tmp->left == NULL && tmp->right == NULL){
		removeNoKids(tmp);
	} else if (tmp->left == NULL){
		removeOneKid(tmp, false);
	} else if (tmp->right == NULL){
		removeOneKid(tmp, true);
	} else {
		TNode *rep = tmp->left;
		while(rep->right != NULL){
			rep = rep->right;
		}
		if(rep->left == NULL){
			removeNoKids(rep);
		} else {
			removeOneKid(rep, true);
		}
		if (root == tmp){
			root = rep;
			rep->parent = NULL;
			root->left = tmp->left;
			root->right = tmp->right;
			if(tmp->left){
				tmp->left->parent = root;
			}
			if(tmp->right){
				tmp->right->parent = root;
			}
			setHeight(root);
		} else if (tmp->parent->left == tmp){
				tmp->parent->left  = rep;
				if(tmp->left){
					tmp->left->parent = tmp->parent;
					tmp->parent->left->left = tmp->left;
				}
				if(tmp->right){
					tmp->right->parent = tmp->parent;
					tmp->parent->left->right = tmp->right;
				}
				setHeight(tmp->parent->left);
		} else if (tmp->parent->right == tmp){
			tmp->parent->right  = rep;
			if(tmp->left){
				tmp->left->parent = tmp->parent;
				tmp->parent->right->left = tmp->left;
			}
			if(tmp->right){
				tmp->right->parent = tmp->parent;
				tmp->parent->right->right = tmp->right;
			}
			setHeight(tmp->parent->right);
		}
		free(tmp);
		return tmp;
	}
	return NULL;
}


void BST::setHeight(TNode *n){
	bool pass = false;
	if (n->left == NULL && n->right == NULL){
		if(n->height == 1){
			pass = true;
		}
		n->height = 1;
	} else if (n->right == NULL){
		if (n->height == n->left->height + 1){
			pass = true;
		}
		n->height = n->left->height + 1;
	} else if (n->left == NULL){
		if (n->height == n->right->height + 1){
			pass = true;
		}
		n->height = n->right->height + 1;
	} else {
		int t = n->left->height;
		if (n->right->height > t){
			t = n->right->height;
		}
		if (n->height == t + 1){
			pass = true;
		}
		n->height = t + 1;
	}
	int bal = getBalance(n);

	if(bal > 1){
		if(getBalance(n->left) == 1){
			// Rotate around n
			rotateRight(n);
		} else if (getBalance(n->left) == -1){
			// Rotate around n-left
			rotateLeft(n->left);
			// Rotate around n
			rotateRight(n);
		} else {

		}
	} else if (bal < -1){
		if (getBalance(n->right) == -1){
			// Rotate around n
			rotateLeft(n);
		} else if (getBalance(n->right) == 1){
			// Rotate around n-right
			rotateRight(n->right);
			// rotate around n
			rotateLeft(n);
		}
	}


	if(n->parent && !pass){
		setHeight(n->parent);
	}
}


int BST::getBalance(TNode *tmp){
	int lH = 0;
	int rH = 0;
	if(tmp->left){
		lH = tmp->left->height;
	}
	if(tmp->right){
		rH = tmp->right->height;
	}
	return (lH - rH);
}

TNode *BST::rotateLeft(TNode *tmp){
	TNode *above = tmp->parent;
	TNode *newRoot = tmp->right;
	TNode *tree2 = newRoot->left;

	newRoot->left = tmp;
	tmp->right = tree2;
	tmp->parent = newRoot;
	if(tmp->right){
		tmp->right->parent = tmp;
	}
	if (above){
		newRoot->parent = above;
		if(newRoot->parent->right == tmp){
			newRoot->parent->right = newRoot;
		} else {
			newRoot->parent->left = newRoot;
		}
	} else {
		root = newRoot;
		root->parent = NULL;
	}

	// Setting Heights
	int tLH = 0;
	int tRH = 0;
	if(tmp->left){
		tLH = tmp->left->height;
	}
	if(tmp->right){
		tRH = tmp->right->height;
	}
	if(tLH > tRH){
		tmp->height = tLH + 1;
	} else {
		tmp->height = tRH + 1;
	}

	int nLH = 0;
	int nRH = 0;
	if(newRoot->right){
		nLH = newRoot->right->height;
	}
	if(newRoot->left){
		nRH = newRoot->left->height;
	}
	if(nLH > nRH){
		newRoot->height = nLH + 1;
	} else {
		newRoot->height = nRH + 1;
	}

	return newRoot;
}

TNode *BST::rotateRight(TNode *tmp){
	TNode *above = tmp->parent;
	TNode *newRoot = tmp->left;
	TNode *tree2 = newRoot->right;

	newRoot->right = tmp;
	tmp->left = tree2;
	tmp->parent = newRoot;
	if(tmp->left){
		tmp->left->parent = tmp;
	}
	if (above){
		newRoot->parent = above;
		if(newRoot->parent->left == tmp){
			newRoot->parent->left = newRoot;
		} else {
			newRoot->parent->right = newRoot;
		}
	} else {
		root = newRoot;
		root->parent = NULL;
	}

	// Setting Heights
	int tLH = 0;
	int tRH = 0;
	if(tmp->right){
		tLH = tmp->right->height;
	}
	if(tmp->left){
		tRH = tmp->left->height;
	}
	if(tLH > tRH){
		tmp->height = tLH + 1;
	} else {
		tmp->height = tRH + 1;
	}

	int nLH = 0;
	int nRH = 0;
	if(newRoot->right){
		nLH = newRoot->right->height;
	}
	if(newRoot->left){
		nRH = newRoot->left->height;
	}
	if(nLH > nRH){
		newRoot->height = nLH + 1;
	} else {
		newRoot->height = nRH + 1;
	}


	return newRoot;
}
