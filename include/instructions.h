//
// Created by donal on 25/06/19.
//

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "frame.h"
#include "stack.h"

void bipush(word_t arg);

void iadd(void);

void iand(void);

void ior(void);

void isub(void);

void dup(void);

void swap(void);

void out(FILE* output);

void in(FILE* input);

void go_to(byte_t* array, int* program_counter);

void ifeq(byte_t* array, int* program_counter);

void iflt(byte_t* array, int* program_counter);

void icmpeq(byte_t* array, int* program_counter);

void ldc_w(byte_t* array, word_t* constant_pool_array);

void istore(int index);

void iload(int index);

void iinc(byte_t index, byte_t value);

unsigned short arr_to_short(byte_t* arg);

#endif //PAD_SKELETON_C_INSTRUCTIONS_H
