#include <stdlib.h>
#include <string.h>
#include "ijvm.h"
#include "stack.h"
#include "instructions.h"

int program_counter = 0;

struct block {
    byte_t* block_instructions;
    int block_size;
};

struct ijvm_instance {
    struct block constants;
    struct block text;
};

struct ijvm_instance instance;

struct StackNode *root;

static word_t swap_word(word_t num) {
    return ((num>>24)&0xff) | ((num<<8)&0xff0000) | ((num>>8)&0xff00) | ((num<<24)&0xff000000);
}

struct block read_block(FILE* fptr) {
    struct block temp;
    for (int i = 0; i < 2; ++i) { //to throw away the block origin
        fread(&temp.block_size, 4, 1, fptr);
    }
    temp.block_size = swap_word(temp.block_size);
    temp.block_instructions = malloc(sizeof(byte_t) * temp.block_size);
    for(int i = 0; i < temp.block_size; i++) {
        fread(&temp.block_instructions[i], 1, 1, fptr);
    }
    return temp;
}

int init_ijvm(char *binary_file) {

    //initialise the instance
    instance = (struct ijvm_instance) {
        .constants = {.block_instructions = NULL, .block_size = 0},
        .text = {.block_instructions = NULL, .block_size = 0}
    };

    //check if the file is valid
    FILE* fptr;
    fptr = fopen(binary_file, "rb");
    if(fptr == NULL) {
        printf("Could not open file :(\n");
        return -1;
    }

    word_t buffer;
    fread(&buffer, sizeof(word_t), 1, fptr);

    buffer = swap_word(buffer);

    if(buffer != MAGIC_NUMBER) {
        printf("Invalid file!\n");
        return -1;
    }

    //load the data into the struct
    instance.constants = read_block(fptr);
    instance.text = read_block(fptr);

    fclose(fptr);
    return 0;
}

void destroy_ijvm() {
    program_counter = 0;
    instance = (struct ijvm_instance) {.constants = {.block_instructions = NULL, .block_size = 0},
            .text = {.block_instructions = NULL, .block_size = 0}};
}

void run() {
    while(program_counter < instance.text.block_size) {
        step();
    }
}

void set_input(FILE *fp) {
    // TODO: implement me
}

void set_output(FILE *fp) {
    // TODO: implement me
}

//TEMPORARY

//END TEMPORARY

//TEMPORARY 2


//END TEMPORARY 2

bool step() {
    switch (instance.text.block_instructions[program_counter]) {
        case OP_BIPUSH:
            bipush(instance.text.block_instructions[program_counter + 1]);
            program_counter = program_counter + 2;
            break;
        case OP_IADD:
            iadd();
            program_counter++;
            break;
        case OP_OUT:
            program_counter++;
            break;
        case OP_ISUB:
            isub();
            program_counter++;
            break;
        case OP_IAND:
            iand();
            program_counter++;
            break;
        case OP_IOR:
            ior();
            program_counter++;
            break;
        case OP_SWAP:
            swap();
            program_counter++;
            break;
        case OP_POP:
            pop(&root);
            program_counter++;
            break;
        default:
            program_counter++;
            break;
    }
    return 0;
}

int text_size() {
    return instance.text.block_size;
}

byte_t* get_text() {
    return instance.text.block_instructions;
}

int get_program_counter() {
    return program_counter;
}