#include <iostream>

using namespace std;

struct node {
    int data;
    struct node* left;
    struct node* right;
}typedef node;

node* root = NULL;

int empty() {
    if (root == NULL)
        return 1;
    return 0;
}

void add_node(int x) {
    node* new_node;
    node* cur = root;
    node* prev = NULL;
    int flag = 0;

    new_node = new node;
    new_node->data = x;
    new_node->left = NULL;
    new_node->right = NULL;

    if (root == NULL) {
        root = new_node;
    }
    else {
        while (cur) {
            if (cur->data < x) {
                prev = cur;
                cur = cur->right;
                flag = 1;
            }
            else {
                prev = cur;
                cur = cur->left;
                flag = 0;
            }
        }
        if (flag == 0)
            prev->left = new_node;
        else
            prev->right = new_node;
    }
}

void delete_node(int x) {
    node* prev= NULL;
    node* cur = root;
    node* successor;
    node* successor_parent;
    int flag = 0;

    if (empty())
        return;

    while (cur) {
        if (cur->data < x) {
            prev = cur;
            cur = cur->right;
            flag = 1;
        }
        else if (cur->data > x) {
            prev = cur;
            cur = cur->left;
            flag = 0;
        }
        else {
            break;
        }
    }
    if (cur->left != NULL) {
        successor_parent = cur;
        successor = cur->left;
        if (successor->right != NULL) {
            while (successor->right != NULL) {
                successor_parent = successor;
                successor = successor->right;
            }
            cur->data = successor->data;
            successor_parent->right = NULL;
            free(successor);
        }
        else {
            cur->data = successor->data;
            successor_parent->left = successor->left;
            free(successor);
        }

    }
    else if (cur->left == NULL && cur->right != NULL) {
        if (flag == 0) {
            prev->left = cur->right;
            free(cur);
        }
        else {
            prev->right = cur->right;
            free(cur);
        }
    }
    else {
        if (flag == 0) {
            prev->left = NULL;
            free(cur);
        }
        else {
            prev->right = NULL;
            free(cur);
        }
    }
}

void tree_traversal(node* ptr) {
    if (ptr == NULL)
        return;
    cout << ptr->data << '\n';
    tree_traversal(ptr->left);
    tree_traversal(ptr->right);
}

int main() {
    //test code
    add_node(10);
    add_node(6);
    add_node(17);
    add_node(2);
    add_node(9);
    add_node(13);
    add_node(22);
    add_node(1);
    add_node(3);
    delete_node(2);
    delete_node(1);
    add_node(7);
    delete_node(13);
    delete_node(17);
    add_node(30);
    add_node(31);
    add_node(11);
    add_node(4);
    delete_node(6);
    
    tree_traversal(root);
}