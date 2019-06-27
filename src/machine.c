#include <stdlib.h>
#include <string.h>
#include "ijvm.h"
#include "instructions.h"

int program_counter = 0;

struct block {
    byte_t* block_instructions;
    size_t block_size;
};

struct ijvm_instance {
    struct block constants;
    struct block text;
    word_t* constant_pool;
    FILE* file_input;
    FILE* file_output;
};

struct ijvm_instance instance;

struct StackNode* root;

static word_t swap_word(word_t num) {
    word_t beans = ((num>>24)&0xff) | ((num<<8)&0xff0000) | ((num>>8)&0xff00) | ((num<<24)&0xff000000);
    return beans;
}

//loads the data into the struct block-by-block
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

//converts the constants - currently stored as bytes - into an array of words
word_t* load_constant_pool(struct block constants) {
    word_t* temp = (word_t*)malloc(constants.block_size * sizeof(word_t));
    int index_at = 0;
    for(int i = 0; i < constants.block_size; i = i + 4) { //could've put this in a separate function but im lazy
        temp[index_at] = constants.block_instructions[i+3] | (word_t)constants.block_instructions[i+2] << 8 | (word_t)constants.block_instructions[i+1] << 16 | (word_t)constants.block_instructions[i] << 24;
        index_at++;
    }
    return temp;
}

int init_ijvm(char *binary_file) {

    //initialise the instance
    instance = (struct ijvm_instance) {
        .constants = {.block_instructions = NULL, .block_size = 0},
        .text = {.block_instructions = NULL, .block_size = 0}
    };

    big_frame = (struct frame*)malloc(sizeof(struct frame));
    big_frame->local_vars = (word_t*)malloc(sizeof(word_t)*1024);

    //default - overwritten if tests ask for alternative input/output
    instance.file_input = stdin;
    instance.file_output = stdout;

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
    instance.constant_pool = load_constant_pool(instance.constants);
    instance.text = read_block(fptr);

    fclose(fptr);
    return 0;
}

void destroy_ijvm() {
    program_counter = 0;
    instance = (struct ijvm_instance) {.constants = {.block_instructions = NULL, .block_size = 0},
            .text = {.block_instructions = NULL, .block_size = 0}};
    free(big_frame);
}

void run() {
    while(step()) {}
    return;
}

void set_input(FILE *fp) {
    instance.file_input = fp;
}

void set_output(FILE *fp) {
    instance.file_output = fp;
}

bool step() {
    switch (instance.text.block_instructions[program_counter]) {
        case OP_NOP:
            program_counter++;
            break;
        case OP_BIPUSH:
            bipush(instance.text.block_instructions[program_counter + 1]);
            program_counter = program_counter + 2;
            break;
        case OP_IADD:
            iadd();
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
        case OP_DUP:
            dup();
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
        case OP_OUT:
            out(instance.file_output);
            program_counter++;
            break;
        case OP_IN:
            in(instance.file_input);
            program_counter++;
            break;
        case OP_GOTO:
            go_to(&instance.text.block_instructions[program_counter + 1], &program_counter);
            program_counter++;
            break;
        case OP_IFEQ:
            ifeq(&instance.text.block_instructions[program_counter + 1], &program_counter);
            program_counter++;
            break;
        case OP_IFLT:
            iflt(&instance.text.block_instructions[program_counter + 1], &program_counter);
            program_counter++;
            break;
        case OP_ICMPEQ:
            icmpeq(&instance.text.block_instructions[program_counter + 1], &program_counter);
            program_counter++;
            break;
        case OP_LDC_W:
            ldc_w(&instance.text.block_instructions[program_counter + 1], instance.constant_pool);
            program_counter = program_counter + 3;
            break;
        case OP_ISTORE:
            istore(instance.text.block_instructions[program_counter + 1]);
            program_counter += 2;
            break;
        case OP_ILOAD:
            iload(instance.text.block_instructions[program_counter + 1]);
            program_counter += 2;
            break;
        case OP_IINC:
            iinc(instance.text.block_instructions[program_counter + 1], instance.text.block_instructions[program_counter + 2]);
            program_counter += 3;
        case OP_INVOKEVIRTUAL:

        case OP_HALT:
            return 0;
        default:
            printf("<!>Instruction unknown<!>\n");
            program_counter++;
            break;
    }
    return true;
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

word_t get_local_variable(int i) {
    return (signed char)big_frame->local_vars[i];
}

byte_t get_instruction() {
    return instance.text.block_instructions[program_counter];
}