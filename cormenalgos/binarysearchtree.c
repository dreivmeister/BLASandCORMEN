#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int key; // key or data same thing
    struct Node* left;
    struct Node* right;
    struct Node* parent;
}Node;

typedef struct BinarySearchTree {
    Node* root;
}BinarySearchTree;

BinarySearchTree* create_binary_search_tree() {
    BinarySearchTree* tmp = malloc(sizeof(BinarySearchTree));
    tmp->root = NULL;
    return tmp;
}


Node* createNode(int key) {
    Node* tmp = malloc(sizeof(Node));
    tmp->key = key;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->parent = NULL;
    return tmp;
}

void inorder(Node* curr) {
    if(curr != NULL) {
        inorder(curr->left);
        printf("%d ", curr->key);
        inorder(curr->right);
    }
}


Node* recursive_search(Node* curr, int k) {
    // search for node in tree with key == k
    if(curr == NULL || k == curr->key) {
        return curr;
    }
    if(k < curr->key) {
        return recursive_search(curr->left, k);
    }
    else {
        recursive_search(curr->right, k);
    }
    return NULL;
}

Node* iterative_search(Node* curr, int k) {
    while(curr != NULL && k != curr->key) {
        if(k < curr->key) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
    return curr;
}

Node* minimum(Node* curr) {
    while(curr->left != NULL) {
        curr = curr->left;
    }
    return curr;
}

Node* maximum(Node* curr) {
    while(curr->right != NULL) {
        curr = curr->right;
    }
    return curr;
}

Node* successor(Node* x) {
    if(x->right != NULL) {
        return minimum(x->right);
    }
    Node* y = x->parent;
    while(y != NULL && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

void insert(BinarySearchTree* T, Node* z) {
    Node* y = NULL;
    Node* x = T->root;
    while(x != NULL) {
        y = x;
        if(z->key < x->key) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    z->parent = y;
    if(y == NULL) {
        T->root = z;
    }
    else if(z->key < y->key) {
        y->left = z;
    }
    else {
        y->right = z;
    }
}

BinarySearchTree* build_binary_search_tree(int* keys, int n) {
    BinarySearchTree* T = create_binary_search_tree();

    for(int i = 0; i < n; i++) {
        Node* z = createNode(keys[i]);
        insert(T, z);
    }
    return T;
}


void transplant(BinarySearchTree* T, Node* u, Node* v) {
    if(u->parent == NULL) {
        T->root = v;
    }
    else if(u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    if(v != NULL) {
        v->parent = u->parent;
    }
}

void delete(BinarySearchTree* T, Node* z) {
    if(z->left == NULL) {
        transplant(T,z,z->right);
    }
    else if(z->right == NULL) {
        transplant(T,z,z->left);
    }
    else {
        Node* y = minimum(z->right);
        if(y->parent != z) {
            transplant(T,y,y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(T,z,y);
        y->left = z->left;
        y->left->parent = y;
    }
}


int main() {
    int keys[] = {1,3,5,7,8,2,9};
    int n = 7;
    BinarySearchTree* T = build_binary_search_tree(keys,n);

    inorder(T->root);
    printf("\n");
    delete(T, T->root->right);
    printf("\n");
    inorder(T->root);

}