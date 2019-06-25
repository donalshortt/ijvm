//
// Created by donal on 25/06/19.
//

#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include "ijvm.h"

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

unsigned short arr_to_short(byte_t* arg);

#endif //PAD_SKELETON_C_INSTRUCTIONS_H
