#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } NodeColor;

// Estructura del nodo
typedef struct Node {
    int data;
    NodeColor color;
    struct Node *left, *right, *parent;
} Node;

// Crear un nodo
Node* createNode(int data) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->color = RED; // Los nuevos nodos siempre son rojos inicialmente
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

// Rotación izquierda
void rotateLeft(Node **root, Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}

// Rotación derecha
void rotateRight(Node **root, Node *y) {
    Node *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}

// Reparar las propiedades del árbol rojinegro después de insertar
void fixInsert(Node **root, Node *z) {
    while (z->parent && z->parent->color == RED) {
        Node *grandparent = z->parent->parent;
        if (z->parent == grandparent->left) {
            Node *uncle = grandparent->right;
            if (uncle && uncle->color == RED) { // Caso 1: Tío rojo
                z->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            } else {
                if (z == z->parent->right) { // Caso 2: Tío negro, en zig-zag
                    z = z->parent;
                    rotateLeft(root, z);
                }
                // Caso 3: Tío negro, en línea recta
                z->parent->color = BLACK;
                grandparent->color = RED;
                rotateRight(root, grandparent);
            }
        } else { // Simétrico al caso anterior
            Node *uncle = grandparent->left;
            if (uncle && uncle->color == RED) { // Caso 1: Tío rojo
                z->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            } else {
                if (z == z->parent->left) { // Caso 2: Tío negro, en zig-zag
                    z = z->parent;
                    rotateRight(root, z);
                }
                // Caso 3: Tío negro, en línea recta
                z->parent->color = BLACK;
                grandparent->color = RED;
                rotateLeft(root, grandparent);
            }
        }
    }
    (*root)->color = BLACK;
}

// Insertar un nodo en el árbol rojinegro
void insert(Node **root, int data) {
    Node *newNode = createNode(data);
    Node *parent = NULL;
    Node *current = *root;

    while (current != NULL) {
        parent = current;
        if (data < current->data)
            current = current->left;
        else
            current = current->right;
    }

    newNode->parent = parent;
    if (parent == NULL)
        *root = newNode;
    else if (data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    fixInsert(root, newNode);
}

// Recorrido en orden
void inOrder(Node *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d(%s) ", root->data, (root->color == RED) ? "R" : "B");
        inOrder(root->right);
    }
}

// Programa principal
int main() {
    Node *root = NULL;

    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 30);
    insert(&root, 15);
    insert(&root, 25);
    insert(&root, 5);

    printf("Recorrido en orden del árbol Rojo-Negro:\n");
    inOrder(root);

    return 0;
}
