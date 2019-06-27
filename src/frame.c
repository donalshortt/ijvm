//
// Created by donal on 26/06/19.
//

#include "stack.h"
#include "ijvm.h"
#include "instructions.h"
#include "frame.h"
#include <stdio.h>
#include <stdlib.h>

void big_test() {
    printf("I AM VERY SICK OF THIS ASSIGNMENT\n");
}

void init_first_frame() {
    current_frame = (struct frame*)malloc(sizeof(struct frame));
    current_frame->local_vars = (word_t*)malloc(sizeof(word_t)*1024);
    current_frame->prev = NULL;
}

void new_frame(unsigned short local_var_size, unsigned short num_of_args, int counter_to_store) {
    printf("<!>New Frame<!>\n");
    struct frame* new_current_frame = malloc(sizeof(struct frame));
    new_current_frame->local_vars = (word_t*)malloc(sizeof(word_t) * local_var_size);
    printf("Local var size: %d\n", local_var_size);
    new_current_frame->num_args = num_of_args;
    printf("Num of args: %d\n", new_current_frame->num_args);
    new_current_frame->local_program_counter = counter_to_store;
    new_current_frame->prev = current_frame;
    new_current_frame->prev_program_counter = counter_to_store;
    printf("Stored counter: %d\n", new_current_frame->prev_program_counter);
    current_frame = new_current_frame;
}
