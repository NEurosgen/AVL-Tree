// AVL-Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>



using namespace std;

template <typename T>
class AVLTree {
    struct Node {
        T data;
        int height;
        Node* left;
        Node* right;
    };
    Node* root;
    Node* findMin(Node* t)
    {
        if (t == NULL)
            return NULL;
        else if (t->left == NULL)
            return t;
        else
            return findMin(t->left);
    }
    void makeEmpty(Node*& t) {
        if (t == NULL) {
            return;
        }
        makeEmpty(t->right);
        makeEmpty(t->left);
        delete t;
    }
    Node* S_left(Node*& t) {//small left rotation
        Node* u = t->right;
        t->right = u->left;
        u->left = t;
        t->height = max(height(t->left), height(t->right)) + 1;
        u->height = max(height(t->right), t->height) + 1;
        return u;
    }
    Node* B_left(Node*& t) {  //Big left rotation
        t->right = S_left(t->right);
        return S_left(t);
    }
    Node* S_right(Node*& t) {
        Node* u = t->left;
        t->left = u->right;
        u->right = t;
        t->height = max(height(t->right), height(t->left)) + 1;
        u->height = max(height(u->left), t->height) + 1;
        return u;
    }
    Node* B_right(Node*& t) {
        t->left = S_right(t->left);
        return S_right(t);
    }
    Node* insert(T& x, Node* t) {
        if (t == NULL) {
            t = new Node;
            t->data = x;
            t->height = 0;
            t->right = NULL;
            t->left = NULL;
        }
        else if (t->data > x) {
            t->left = insert(x, t->left);
            if (height(t->left) - height(t->right) == 2) {
                if (x < t->left->data) {
                    t = S_right(t);
                }
                else {
                    t = B_right(t);
                }
            }

        }
        else if (t->data < x) {
            t->right = insert(x, t->right);
            if (height(t->right) - height(t->left) == 2) {
                if (x < t->right->data) {
                    t = S_left(t);
                }
                else {
                    t = B_left(t);
                }
            }
        }
        t->height = max(height(t->left), height(t->right)) + 1;

        return t;
    }
    Node* findMax(Node* t)
    {
        if (t == NULL)
            return NULL;
        else if (t->right == NULL)
            return t;
        else
            return findMax(t->right);
    }
    int height(Node* t) {
        if (t == NULL) {
            return -1;;
        }
        return t->height;
    }
    Node* remove(T& val,Node* t) {
        Node* temp;
        if (t == NULL) {
            return t;
        }
        if (t->data < val) {
            t->right = remove( val,t->right);
        }
        if (t->data >val) {
            t->left = remove( val,t->left);
        }
        else if(t->left!=nullptr && t->right!=nullptr) {
            
            temp = findMin(t->right);
            t->data = temp->data;
            t->right = remove(t->data,t->right);


        }
        else {
            temp = t;
            if (t->left == NULL) {
                t = t->right;
            }
            else if(t->right==NULL) {
                t = t->left;
            }
            delete temp;
            
        }
        if (t == NULL)
            return t;
        t->height = max(height(t->left), height(t->right)) + 1;

        


        if (height(t->left) - height(t->right) == -2)
        {
            
            if ((height(t->right->right) - height(t->right->left)) == 1)
                return S_left(t);
            
            else
                return B_left(t);
        }

        else if (height(t->right) - height(t->left) == 2)
        {
            
            if (height(t->left->left) - height(t->left->right) == 1)
                return S_right(t);
            
            else
                return B_right(t);
        }
        return t;
        
    }
    void inorder(Node* t)
    {
        if (t == NULL)
            return;
        inorder(t->left);
        cout << t->data << " ";
        inorder(t->right);
    }
    int getBalance(Node* t)
    {
        if (t == NULL)
            return -1;
        else
            return height(t->left) - height(t->right);
    }
public:
    AVLTree()
    {
        root = NULL;
    }

    void insert(T x)
    {
        root = insert(x, root);
    }

    void remove(T x)
    {
        root = remove(x, root);
    }

    void display()
    {
        inorder(root);
        cout << endl;
    }
    
};



int main()
{
    AVLTree<int> tree;

    // Insert values
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    tree.insert(25);

    // Display the tree
    cout << "Tree after inserting values: ";
    tree.display();

    // Remove values
    tree.remove(30);
    tree.remove(40);

    // Display the tree after removal
    cout << "Tree after removing values: ";
    tree.display();
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
