#include <stdio.h>
#include <stdlib.h>
#include <math.h> // 소수 판단을 위한 math.h 헤더 파일 추가

// 이진 트리 노드 정의
typedef struct Node {
    double data;
    struct Node* left;
    struct Node* right;
} Node;

// 새로운 노드를 생성하는 함수
Node* createNode(double data) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 이진 트리에 숫자를 삽입하는 함수
Node* insert(Node* root, double data) 
{
    if (root == NULL) {
        return createNode(data);
    }
    
    if (data < root->data) {
        root->left = insert(root->left, data);
    } else if (data > root->data) {
        root->right = insert(root->right, data);
    }
    
    return root;
}

// 소수 판단 함수
int isPrime(double number) 
{
    if (number <= 1) {
        return 0; // 1 또는 음수는 소수가 아님
    }
    
    // 2부터 제곱근까지의 수로 나누어 소수인지 판단
    for (int i = 2; i <= sqrt(number); i++) {
        if ((int)number % i == 0) {
            return 0; // 나누어 떨어지면 소수가 아님
        }
    }
    
    return 1; // 나누어 떨어지지 않으면 소수
}

// 중위 순회를 이용하여 노드 수를 계산하고 소수 개수를 출력하는 함수

int inorderTraversal(Node* root) 
{
    static int nodeCount = 0;

    if (root != NULL) {
        nodeCount++;
        inorderTraversal(root->left);
        inorderTraversal(root->right);
    }
    return nodeCount;
}

int primenumber(Node* root)
{
    static int primeCount = 0;

    if (root != NULL) {
                
        // 현재 노드의 값에서 1을 더하거나 뺀 값을 계산
        double plusOne = root->data + 1;
        double minusOne = root->data - 1;
        
        // 계산한 값이 소수인지 판단하여 소수 개수 증가
        if (isPrime(plusOne) || isPrime(minusOne)) {
            primeCount++;
        }
        
        primenumber(root->left);
        primenumber(root->right);
    }
    
    return primeCount;

}
int main() 
{
    FILE* fp = NULL;
    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        perror("file cannot be opened");
        return 1;
    }
    
    Node* root = NULL;
    
    double number;
    while (fscanf(fp, "%lf", &number) != EOF) {
        root = insert(root, number);
    }
    
    fclose(fp);

    int nodeCount = inorderTraversal(root);
    printf("\nOnly one count : %d\n", nodeCount);

    int primeCount = primenumber(root);
    printf("Near prime count : %d\n", primeCount);
    
    free(root);

    return 0;
}
