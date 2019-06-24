//
// Created by donal on 21/06/19.
//

#include "stack.h"
#include <ijvm.h>

int nodeCount = 0;

struct stack_node {
    int data;
    struct stack_node* next_node;
};

struct stack_node* new_node(int data) {
    struct stack_node* stackNode = malloc(sizeof(stack_node));
    stackNode->data = data;
    stackNode->next_node = NULL;
    return stackNode;
}

void bipush(int data) {
    if (nodeCount == 0) {
        new_node(data);
        nodeCount++;
    } else {
        
    }
}