#include <stdio.h>
#include <stdlib.h>

// Estructura para el nodo del árbol AVL
typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

// Función para obtener la altura de un nodo
int height(Node *n) {
    return (n == NULL) ? 0 : n->height;
}

// Función para obtener el factor de balance
int getBalance(Node *n) {
    return (n == NULL) ? 0 : height(n->left) - height(n->right);
}

// Crear un nuevo nodo
Node* createNode(int key) {
    Node *node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // Inicialmente el nodo es una hoja
    return node;
}

// Rotación derecha
Node* rotateRight(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

// Rotación izquierda
Node* rotateLeft(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y;
}

// Insertar un nodo en el árbol AVL
Node* insert(Node *node, int key) {
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // Claves duplicadas no permitidas

    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    int balance = getBalance(node);

    // Caso LL
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    // Caso RR
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    // Caso LR
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Caso RL
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Recorrido en orden (in-order)
void inOrder(Node *root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

// Programa principal
int main() {
    Node *root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("Recorrido en orden del árbol AVL:\n");
    inOrder(root);

    return 0;
}
