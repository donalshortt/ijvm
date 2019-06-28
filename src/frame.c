//
// Created by donal on 26/06/19.
//

#include "stack.h"
#include "ijvm.h"
#include "instructions.h"
#include "frame.h"
#include <stdio.h>
#include <stdlib.h>

void init_first_frame() {
    current_frame = (struct frame*)malloc(sizeof(struct frame));
    current_frame->local_vars = (word_t*)malloc(sizeof(word_t)*1024);
    current_frame->prev = NULL;
}

void new_frame(int memory_allocated, int counter_to_store, int stack_size_to_store) {
    printf("<!>New Frame<!>\n");
    printf("INPUTS: %d <--> %d <--> %d\n",memory_allocated,counter_to_store,stack_size_to_store);
    struct frame* new_current_frame = malloc(sizeof(struct frame));
    new_current_frame->local_vars = (word_t*)malloc(sizeof(word_t) * memory_allocated);
    new_current_frame->num_args = memory_allocated;
    new_current_frame->prev_stack_size = stack_size_to_store;
    printf("Num of args: %d\n", new_current_frame->num_args);
    new_current_frame->prev = current_frame;
    new_current_frame->prev_program_counter = counter_to_store;
    printf("Stored counter: %d\n", new_current_frame->prev_program_counter);
    current_frame = new_current_frame;
}

void frame_store(int index, word_t arg) {
    current_frame->local_vars[index] = arg;
}

void frame_delete() {
    printf("<!>Frame delete<!>\n");
    current_frame = current_frame->prev;
}