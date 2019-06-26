//
// Created by donal on 26/06/19.
//

#ifndef FRAME_H
#define FRAME_H

#include "ijvm.h"

struct frame {
    struct frame *prev;
    word_t *local_vars;
};

struct frame* big_frame;

//void init_frame(struct frame* frame);

void big_test();

#endif //PAD_SKELETON_C_FRAME_H
