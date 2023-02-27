#include <iostream>


template <typename T>
class AVL_Tree {
private:
	//Create Struct Node
	struct Node{
		T data;
		int height;
		Node* left;
		Node* right;
	};
	// Append pointer Node in class
	Node* root;
	int height(Node* t) {
		if (t == NULL) {
			return -1;
		}
		return t->height;
	}
	Node* s_left(Node*&t ) {
		Node* u = t->right;
		t->right = u->left;
		u->left = t;
		t->height = std::max(height(t->left), height(t->right)) + 1;
		u->height = std::max(height(u->left),height( u->right)) + 1;
		return u;
	}
	Node* b_left(Node*& t) {
		t->right = s_left(t->right);
		return s_left(t);
	}
	Node* s_right(Node*& t) {
		Node* u = t->left;
		t->left = u->right;
		u->right = t;
		t->height = std::max(height(t->left), height(t->right));
		u->height = std::max(height(u->left), height(u->right));
		return u;
	}
	Node* b_right(Node*& t) {
		t->left = s_right(t->left);
		return s_right(t);
	}
	Node* insert(T& x, Node* t) {
		if (t == NULL) {
			t = new Node;
			t->data = x;
		}
		if (t->val > x) {
			t->left = insert(x, t->left);
			if (height(left) - height(right) == 2) {
				if (x < t->left->data) {
					t = s_right(t);
				}
				else {
					t = b_right(t);
				}
			}
		}
		else if (t->data < x) {
			t->right = insert(x, t->right);
			if (height(right) - height(left) == 2) {
				if (x < t->right->data) {
					t = s_left(t);
				}
				else {
					t = b_left(t);
				}
			}
		}
		t->height = std::max(height(t->left), height(t->right)) + 1;
		return t;
	}
	Node* remove()

public:
	AVL_Tree() {
		root->data = NULL;
		root->left = NULL;
		root->right = NULL;
		root->height = 0;
	}
};