//
// Created by donal on 25/06/19.
//

#include "stack.h"
#include "ijvm.h"
#include "instructions.h"
#include <stdio.h>

struct StackNode *root;

void bipush(word_t arg) { //QUESTION: Should I use byte_t or word_t?
    push(&root, (char)arg);
    return;
}

void iadd() {
    word_t a = pop(&root);
    word_t b = pop(&root);
    a = a + b;
    push(&root, a);
}

void isub() {
    word_t a = pop(&root);
    word_t b = pop(&root);
    a = b - a;
    push(&root, a);
}

void iand() {
    word_t a = pop(&root);
    word_t b = pop(&root);
    a = (a & b);
    push(&root, a);
}

void ior() {
    word_t a = pop(&root);
    word_t b = pop(&root);
    a = (a | b);
    push(&root, a);
}

void swap() {
    word_t a = pop(&root);
    word_t b = pop(&root);
    push(&root, a);
    push(&root, b);

}

