//
// Created by donal on 26/06/19.
//

#ifndef FRAME_H
#define FRAME_H

#include "ijvm.h"

struct frame {
    struct frame* prev;
    word_t *local_vars;
    short num_args;
    int prev_program_counter;
    int prev_stack_size;
};

struct frame* current_frame;

void init_first_frame();

void new_frame(int memory_allocated, int counter_to_store, int stack_size_to_store);

void frame_store(int index, word_t arg);

void frame_delete();


#endif //PAD_SKELETON_C_FRAME_H
