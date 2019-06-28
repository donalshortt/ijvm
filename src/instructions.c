//
// Created by donal on 25/06/19.
//

#include "stack.h"
#include "ijvm.h"
#include "instructions.h"
#include "frame.h"
#include <stdio.h>

struct StackNode *root;

extern int program_counter;

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
    fprintf(output, "%c", temp);
}

void in(FILE* input) {
    word_t lettuce;
    lettuce = fgetc(input);
    if (lettuce == EOF) {
        lettuce = 0;
    } else if (lettuce >= 255) {
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

void ldc_w(byte_t* array, word_t* constant_pool_array) {
    unsigned short index = arr_to_short(array);
    push(&root, constant_pool_array[index]);
}

void istore(int index) {
    word_t beans = pop(&root);
    current_frame->local_vars[index] = beans;
}

void iload(int index) {
    word_t temp = current_frame->local_vars[index];
    push(&root, temp);
}

void iinc(byte_t index, byte_t value) {
    current_frame->local_vars[index] += value;
}

void invoke_virtual(byte_t* array, word_t* constant_pool) {
    printf("<!>Invoke virtual<!>\n");
    program_counter++;
    unsigned short pointer = arr_to_short(&array[program_counter]);
    int prev_pc = program_counter+2;
    program_counter = constant_pool[pointer]; //*(constant_pool+pointer)
    printf("Constant pool at index %d: %d\n", pointer ,constant_pool[pointer]);
    printf("Unsigned short(pointer): %d\n", pointer);
    unsigned short num_of_args = arr_to_short(&array[program_counter]);
    program_counter += 2;
    printf("Number of args: %d\n", num_of_args);
    unsigned short local_var_size = arr_to_short(&array[program_counter]);
    program_counter += 2;
    printf("Local var size: %d\n", local_var_size);
    int memory_allocated = local_var_size + num_of_args;
    new_frame(memory_allocated, prev_pc, stack_size());
    for (int i=num_of_args-1; i>=0; i--) {
        frame_store(i, pop(&root));
    }
}

void ireturn() {
    printf("<!>IReturn<!>\n");
    word_t returned_value = pop(&root);
    printf("Returned value: %d\n",returned_value);
    program_counter = current_frame->prev_program_counter;
    printf("Reset program counter: %d\n", program_counter);
    while(current_frame->prev_stack_size < stack_size()) {
        pop(&root);
    }
    frame_delete();
    push(&root, returned_value);
}

void wide(byte_t* array, int* program_counter) {
    unsigned short arg = arr_to_short(&array[1]);
    switch(array[0]) {
        case OP_ISTORE:
            istore(arg);
            *program_counter += 3;
            break;
        case OP_ILOAD:
            iload(arg);
            *program_counter += 3;
            break;
        case OP_IINC:
            iinc(arg, array[3]);
            *program_counter += 4;
            break;
        default:
            printf("<!>Error in wide<!>\n");
    }
}

unsigned short arr_to_short(byte_t* bytes) {
    unsigned short arg = bytes[1] | bytes[0] << 8;
    return arg;
}
