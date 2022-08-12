#include <iostream>

using namespace std;

struct node {
    int data;
    struct node* left;
    struct node* right;
}typedef node;

node* root = NULL;
/*
노드 추가 함수
현재 노드가 NULL값이 될 때 까지 반복(말단 노드에 다다를 때까지)
추가 하고자 하는 노드의 데이터 값이 현재 노드의 데이터 값 보다 크거나 같으면 현재 노드의 오른쪽으로,
작으면 현재 노드의 왼쪽으로 내려가며 탐색
말단에 다다르면 탐색 종료후 flag값에 따라 알맞은 위치에 노드 추가
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
노드 삭제 함수
추가 함수와 유사한 방식으로 탐색한다. 
삭제하고자 하는 값과 같은 값을 찾으면 종료하도록 한다.
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
    지우고자 하는 노드의 왼쪽에 값이 있다면 왼쪽 한 번 탐색후 쭉 오른쪽으로 내려가며 말단노드를 찾는다.
    말단 노드의 값을 지우고자 하는 노드의 위치(cur)에 넣어주고 해당 말단 노드는 삭제*/
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
    * 지우고자 하는 노드의 왼쪽은 없고 오른쪽은 있을 때
    지우고자 하는 값이 부모의 왼쪽에 있는지 오른쪽에 있는지 파악하고
    지우고자 하는 값(cur)의 오른쪽을 현재 노드 위치에 넣어주고 현재 소멸.
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
    삭제하고자 하는 값이 말단 노드(왼쪽도 없고 오른쪽도 없으면) 부모로부터 어떤 위치에 있는지 파악하고 삭제
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

//주석 써오기
//코드가 어떻게 돌아가는가에 대한 주석을 써오기