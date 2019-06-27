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
    int local_program_counter;
    int prev_program_counter;
};

struct frame* current_frame;

void init_first_frame();

void new_frame(unsigned short local_var_size, unsigned short num_of_args, int counter_to_store);

void big_test();

#endif //PAD_SKELETON_C_FRAME_H
