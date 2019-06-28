#ifndef STACK_H
#define STACK_H

#include "ijvm.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>


struct StackNode {
    word_t data;
    struct StackNode* next;
};

//int gay_stack_size;

struct StackNode* newNode(word_t data);

int isEmpty(struct StackNode* root);

void push(struct StackNode** root, word_t data);

word_t pop(struct StackNode** root);

word_t peek(struct StackNode* root);

#endif