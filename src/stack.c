#include "ijvm.h"
#include "stack.h"
#include "instructions.h"
#include "frame.h"
#include <stdlib.h>
#include <assert.h>

struct StackNode *root;

int gay_stack_size = 0;

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
    gay_stack_size++;
}

word_t pop(struct StackNode** root) {
    if (isEmpty(*root))
        exit(-1);
    struct StackNode* temp = *root;
    *root = (*root)->next;
    word_t popped = temp->data;
    free(temp);

    gay_stack_size--;

    return popped;
}

word_t peek(struct StackNode* root) {
    if (isEmpty(root))
        printf("Stack is empty!\n");
    //printf("Peeked from stack: %x\n", root->data);
    return root->data;
}

word_t tos() {
    return peek(root);
}

word_t *get_stack() {
    struct StackNode* temp = root;
    //*temp = *root;
    //printf("NODE DATA: %d\n", temp->data);
    word_t* tempstack;
    int i;
    tempstack = malloc(sizeof(word_t *)*64000);
    for(i = 0; !isEmpty(temp); i++) {
        tempstack[i] = temp->data;
        temp=temp->next;
    }
    assert(i==stack_size());
//    for (i=stack_size()-1; i >= 0; i--) {
//        tempstack[i] = temp->data;
//        temp=temp->next;
//    }
    return tempstack;
}

int stack_size() {
    return gay_stack_size;
}