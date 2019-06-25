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

void dup() {
    word_t temp = pop(&root);
    push(&root, temp);
    push(&root, temp);
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

void out(FILE* output) {
    word_t temp = pop(&root);
    if (output == NULL) {
        printf("Could not write character %c to file!\n", temp);
    } else {
        fprintf(output,"%c", temp);
    }
}

void in(FILE* input) {
    int lettuce;
    lettuce = fgetc(input);
    if (lettuce == EOF) {
        lettuce = 0;
    } else if (lettuce == 255) {
        lettuce = 0;
    }
    push(&root, lettuce);
}

void go_to(byte_t* array, int* program_counter) {
    signed short offset = arr_to_short(array);
    *program_counter = *program_counter + (offset - 1); //QUESTION: why include * when it is already declared in the args?
}

void ifeq(byte_t* array, int* program_counter) {
    word_t temp = pop(&root);
    if (temp == 0) {
        go_to(array, program_counter);
    } else {
        *program_counter = *program_counter + 2;
    }
}

void iflt(byte_t* array, int* program_counter) {
    word_t temp = pop(&root);
    if (temp < 0) {
        go_to(array, program_counter);
    } else {
        *program_counter = *program_counter + 2;
    }
}

void icmpeq(byte_t* array, int* program_counter) {
    word_t temp1 = pop(&root);
    word_t temp2 = pop(&root);
    if (temp1 == temp2) {
        go_to(array, program_counter);
    } else {
        *program_counter = *program_counter + 2;
    }
}

unsigned short arr_to_short(byte_t* bytes) {
    unsigned short arg = bytes[1] | bytes[0] << 8;
    return arg;
}
