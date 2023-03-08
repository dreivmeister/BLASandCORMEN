#include <stdio.h>
#include <stdlib.h>



typedef struct Node
{
    int key;
    // 0 - red, 1 - black
    int color;
    struct Node* p;
    struct Node* left;
    struct Node* right;
}Node;

Node* create_node(int key) {
    Node* tmp = malloc(sizeof(Node));
    tmp->key = key;
    tmp->color = 0;
    tmp->p = NULL;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}

void print_color(Node* x) {
    if(x->color == 0) {
        printf("red");
    }
    else {
        printf("black");
    }
}

void print_node(Node* x) {
    printf("%d ", x->key);
    print_color(x);
}


typedef struct RedBlackTree
{
    Node* NIL;
    Node* root;
}RedBlackTree;

RedBlackTree* create_rbtree() {
    RedBlackTree* tmp = malloc(sizeof(RedBlackTree));
    tmp->NIL = create_node(99999);
    tmp->NIL->color = 1;
    tmp->root = tmp->NIL;
    return tmp;
}

// operations

void left_rotate(RedBlackTree* T, Node* x) {
    Node* y = x->right;
    x->right = y->left; 

    if(y->left != T->NIL){
        y->left->p = x;
    }
    y->p = x->p; 

    if(x->p == T->NIL) {
        T->root = y;
    }
    else if(x == x->p->left) {
        x->p->left = y;
    }
    else {
        x->p->right = y;
    }

    y->left = x; 
    x->p = y;
}

void right_rotate(RedBlackTree* T, Node* x) {
    Node* y = x->left;
    x->left = y->right;

    if(y->right != T->NIL) {
        y->right->p = x;
    }

    y->p = x->p;

    if(x->p == T->NIL) {
        T->root = y;
    }
    else if(x == x->p->right) {
        x->p->right = y;
    }
    else {
        x->p->left = y;
    }

    y->right = x;
    x->p = y;
}


void insert_fixup(RedBlackTree* T, Node* z) {
    // 0 is red
    while(z->p->color == 0) {
        if(z->p == z->p->p->left) {
            Node* y = z->p->p->right;
            if(y->color == 0) {
                z->p->color = 1;
                y->color = 1;
                z->p->p->color = 0;
                z = z->p->p;
            }
            else{
                if(z == z->p->right) {
                    z = z->p;
                    left_rotate(T, z);
                }
                z->p->color = 1;
                z->p->p->color = 0;
                right_rotate(T, z->p->p);
            }
        }
        else {
            Node* y = z->p->p->left;
            if(y->color == 0) {
                z->p->color = 1;
                y->color = 1;
                z->p->p->color = 0;
                z = z->p->p;
            }
            else {
                if(z == z->p->left) {
                    z = z->p;
                    right_rotate(T, z);
                }
                z->p->color = 1;
                z->p->p->color = 0;
                left_rotate(T, z->p->p);
            }
        }
        if(z == T->root) {
            return;
        }
    }
    T->root->color = 1;
}


void insert(RedBlackTree* T, int key) {
    Node* z = create_node(key);
    z->left = T->NIL;
    z->right = T->NIL;

    Node* y = T->NIL;
    Node* x = T->root;

    while(x != T->NIL) {
        y = x;
        if(z->key < x->key) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    z->p = y;
    if(y == T->NIL) {
        T->root = z;
    }
    else if(z->key < y->key) {
        y->left = z;
    }
    else {
        y->right = z;
    }
    insert_fixup(T, z);
}

Node* search(RedBlackTree* T, int k) {
    Node* x = T->root;
    while(x != T->NIL && k != x->key) {
        if(k < x->key) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    return x;
}


void inorder(RedBlackTree* T, Node* x) {
    if(x != T->NIL) {
        inorder(T, x->left);
        printf("%d ", x->key);
        print_color(x);
        printf("\n");
        inorder(T, x->right);
    }
}


//TODO: implement delete
int main() {
    RedBlackTree* tree = create_rbtree();
    int n = 9;
    int keys[] = {3,2,1,4,5,7,6,8,9};

    for(int i = 0; i < n; i++) {
        insert(tree, keys[i]);
    }

    Node* res = search(tree, 8); 
    if (res != tree->NIL) {
        print_node(res);
    }
    else {
        printf("key not found");
    }
}