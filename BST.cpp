/*Note: you must create the BST.cpp file.  I'm only including a few
Otherwise, as specified in the directions, you must write the BST.cpp.
including the method definitions to accompany the method declarations
in BST.hpp
*/
#include "BST.hpp"
#include <iostream>
#include <string>


BST::BST() {
	root = NULL;
}
BST::BST(string s) {
	root = new TNode(s);
}

bool BST::insert(string s){
	if(root == NULL){
		root = new TNode(s);
		return true;
	}
	else {
		TNode *n = root;
		while (n != NULL){
			if (s.compare(n->data->phrase) < 0){
				if (n->left == NULL){
					n->left = new TNode(s);
					n->left->parent = n;
					setHeight(n);
					return true;
				} else {
					n = n->left;
				}
			} else if (s.compare(n->data->phrase) > 0){
				if (n->right == NULL){
					n->right = new TNode(s);
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

TNode *BST::find(string s){
	TNode *n = root;
	while (n){
		if (n->data->phrase == s){
			break;
		} else if (s.compare(n->data->phrase) < 0){
				n = n->left;
		} else if (s.compare(n->data->phrase) > 0){
			n = n->right;
		}
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
	cout << n->data->phrase << ", " << n->height << endl;
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
	cout << n->data->phrase << ", " << n->height << endl;
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
	cout << n->data->phrase << ", " << n->height << endl;
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


TNode *BST::remove(string s){
	TNode *tmp = find(s);
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
		Phrase *val = rep->data;
		if(rep->left == NULL){
			removeNoKids(rep);
		} else {
			removeOneKid(rep, true);
		}
		if (root == tmp){
			root = new TNode(val->phrase);
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
				tmp->parent->left  = new TNode(val->phrase);
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
			tmp->parent->right  = new TNode(val->phrase);
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
	if(n->parent && !pass){
		setHeight(n->parent);
	}
}
