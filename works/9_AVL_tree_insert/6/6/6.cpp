#include <iostream>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

int getHeight(Node* node) {
    if (node == nullptr) return 0;
    return node->height;
}

int max(int a, int b) { return (a > b) ? a : b; }

Node* createNode(int key) {
    Node* newNode = new Node();
    newNode->key = key;
    newNode->left = nullptr;
    newNode->right = nullptr;
    newNode->height = 1;
    return newNode;
}

Node* rotateRight(Node* y) {
    if (y == nullptr || y->left == nullptr) return y;
    Node* x = y->left;
    Node* z = x->right;

    x->right = y;
    y->left = z;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

Node* rotateLeft(Node* x) {
    if (x == nullptr || x->right == nullptr) return x;
    Node* y = x->right;
    Node* z = y->left;

    y->left = x;
    x->right = z;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

int getBalance(Node* node) {
    if (node == nullptr)  return 0;
    return getHeight(node->left) - getHeight(node->right);
}

Node* rebalance(Node* tree, int key) {
    int balance = getBalance(tree);

    if (balance > 1 && key < tree->left->key) { return rotateRight(tree); }
    else if (balance < -1 && key > tree->right->key) { return rotateLeft(tree); }
    else if (balance > 1 && key > tree->left->key) {
        tree->left = rotateLeft(tree->left);
        return rotateRight(tree);
    }
    else if (balance < -1 && key < tree->right->key) {
        tree->right = rotateRight(tree->right);
        return rotateLeft(tree);
    }
    return tree;
}

Node* insert(Node* root, int key) {
    if (root == nullptr) return createNode(key);

    if (key < root->key) root->left = insert(root->left, key);
    else root->right = insert(root->right, key);

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    return rebalance(root, key);
}

void printTree(Node* root, string prefix = "", bool isLeft = true) {
    if (root == nullptr) {
        cout << prefix;
        cout << (isLeft ? "L " : "   ") << "_\n";
        return;
    }

    if (root->right != nullptr) printTree(root->right, prefix + (isLeft ? "|  " : "   "), false);

    cout << prefix;
    cout << (isLeft ? "L " : (root->left != nullptr ? "|-" : "   ")) << root->key << "\n";

    if (root->left != nullptr) printTree(root->left, prefix + (isLeft ? "   " : "|  "), true);
}

int main() {
    Node* root = nullptr;

    int size;
    cout << "Enter the number of elements: ";
    cin >> size;

    for (int i = 0; i < size; i++) {
        int num;
        cin >> num;
        root = insert(root, num);
    }

    cout << "Tree structure:\n";
    printTree(root);

    return 0;
}