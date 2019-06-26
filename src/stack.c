#include "ijvm.h"
#include "stack.h"
#include "instructions.h"
#include "frame.h"
#include <stdlib.h>

struct StackNode *root;

struct StackNode* newNode(word_t data) {
    struct StackNode* stackNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}

int isEmpty(struct StackNode* root) {
    return !root;
}

void push(struct StackNode** root, word_t data) {
    struct StackNode* stackNode = newNode(data);
    stackNode->next = *root;
    *root = stackNode;
    //printf("%x pushed to stack\n", data);
}

word_t pop(struct StackNode** root) {
    if (isEmpty(*root))
        exit(-1);
    struct StackNode* temp = *root;
    *root = (*root)->next;
    word_t popped = temp->data;
    free(temp);

    return popped;
}

word_t peek(struct StackNode* root) {
    if (isEmpty(root))
        exit(-1);
    //printf("Peeked from stack: %x\n", root->data);
    return root->data;
}

word_t tos() {
    printf("xXx_TopOfStack_xXx: %x\n", peek(root));
    return peek(root);
}