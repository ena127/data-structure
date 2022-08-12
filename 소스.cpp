#include <iostream>

using namespace std;

struct node {
    int data;
    struct node* left;
    struct node* right;
}typedef node;

node* root = NULL;
/*
��� �߰� �Լ�
���� ��尡 NULL���� �� �� ���� �ݺ�(���� ��忡 �ٴٸ� ������)
�߰� �ϰ��� �ϴ� ����� ������ ���� ���� ����� ������ �� ���� ũ�ų� ������ ���� ����� ����������,
������ ���� ����� �������� �������� Ž��
���ܿ� �ٴٸ��� Ž�� ������ flag���� ���� �˸��� ��ġ�� ��� �߰�
*/

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

/*
��� ���� �Լ�
�߰� �Լ��� ������ ������� Ž���Ѵ�. 
�����ϰ��� �ϴ� ���� ���� ���� ã���� �����ϵ��� �Ѵ�.
*/
void delete_node(int x) {
    node* prev;
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

    /*
    ������� �ϴ� ����� ���ʿ� ���� �ִٸ� ���� �� �� Ž���� �� ���������� �������� ���ܳ�带 ã�´�.
    ���� ����� ���� ������� �ϴ� ����� ��ġ(cur)�� �־��ְ� �ش� ���� ���� ����*/
    if (cur->left != NULL) { 
        successor_parent = cur;
        successor = cur->left;
        while (successor->right != NULL) { 
            successor_parent = successor; 
            successor = successor->right;
        }
        cur->data = successor->data;
        successor_parent->right = NULL;
        free(successor);
    }
    /*
    * ������� �ϴ� ����� ������ ���� �������� ���� ��
    ������� �ϴ� ���� �θ��� ���ʿ� �ִ��� �����ʿ� �ִ��� �ľ��ϰ�
    ������� �ϴ� ��(cur)�� �������� ���� ��� ��ġ�� �־��ְ� ���� �Ҹ�.
    */
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
    /*
    �����ϰ��� �ϴ� ���� ���� ���(���ʵ� ���� �����ʵ� ������) �θ�κ��� � ��ġ�� �ִ��� �ľ��ϰ� ����
    */
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

int empty() {
    if (root == NULL)
        return 1;
    return 0;
}

//�ּ� �����
//�ڵ尡 ��� ���ư��°��� ���� �ּ��� �����