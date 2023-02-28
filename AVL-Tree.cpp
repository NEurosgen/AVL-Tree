// AVL-Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <string>

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
    Node* balance(Node* t){
        if (getBalance(t) == -2) {
            if (t->right && getBalance(t->right) == -1 || getBalance(t->right) == 0) {
                
                t = S_left(t);
                
            }
            else if (t->right && t->right->left && getBalance(t->right) == 1 && (getBalance(t->right->left) == 1 || getBalance(t->right->left) == -1 || getBalance(t->right->left) == 0)) {
                t = B_left(t);

            }
        }
        t->height = height(t->left) - height(t->right);
        if (getBalance(t) == 2) {
            if (t->left && getBalance(t->left) == 1 || getBalance(t->left) == 0) {

                t = S_right(t);
                
            }
            if (t->left && t->left->right && getBalance(t->left) == 1 && (getBalance(t->left->right) == 1 || getBalance(t->left->right) == -1 || getBalance(t->left->right) == 0)) {
                t = B_right(t);
            }
        }
        t->height = height(t->left) - height(t->right);
        return t;
    
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
            t = balance(t);

        }
        else if (t->data < x) {
            t->right = insert(x, t->right);
            t = balance(t);
        }
        t->height = max(height(t->left), height(t->right)) + 1;

        return t;
    }
    Node* exist(T& val, Node* root) {
        Node* t = root;
        if (t == NULL) {
            return t;
        }
        
        while (1) {
            if (t == NULL) {
                return t;
            }
            if (val < t->data) {
                t = t->left;
                continue;
            }
            if (val > t->data) {
                t = t->right;
                continue;
            }
            if (val == t->data) {
                return t;
            }
        }
       
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
        if (t == NULL  || t==nullptr) {
            return 0;
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
        if (t->data > val) {
            t->left = remove(val, t->left);

        }
        if (t->data == val) {
            if (t->left != nullptr && t->right != nullptr) {

                temp = findMin(t->right);
                t->data = temp->data;
                t->right = remove(t->data, t->right);


            }
            else {
                temp = t;
                if (t->left == NULL) {
                    t = t->right;
                }
                else if (t->right == NULL) {
                    t = t->left;
                }
                delete temp;

            }
        }
        if (t == NULL)
            return t;
        t->height = max(height(t->left), height(t->right)) + 1;

        


        t = balance(t);
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
            return 0;
        else
            return height(t->left) - height(t->right);
    }
public:
    AVLTree()
    {
        root = NULL;
    }
    Node* exist(T val) {
        Node* t= exist(val, root);
        
        return  t;
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
    for (int i = 0; i < 20; ++i) {
        tree.insert(i);
    }

    tree.remove(6);
    std::cout<<tree.exist(2)->data<<" ";
    std::cout << tree.exist(3)->data << " ";
    std::cout << tree.exist(-1) << " ";
    tree.display();

    // Remove values
   
    cout << "Tree after removing values: ";
 
   
    
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
