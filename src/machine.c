#include <ijvm.h>

byte_t byte_array[128]; //temp global variable
int program_counter = 0; //temp global variable

int get_program_counter() {
    return program_counter;
}

int pool_size() {
    int size = 0;
    size = byte_array[4] + byte_array[5] + byte_array[6] + byte_array[7];
    return size;
}

int text_size() {
    int size = 0;
    int offset = pool_size();
    size = byte_array[offset + 12] + byte_array[offset + 13] + byte_array[offset + 14] + byte_array[offset + 15];
    return size;
}

byte_t *get_text() {
    byte_t text[text_size()];
    int text_counter = 0;
    int text_start = pool_size() + 8;
    for (int i = text_start; i < text_size(); ++i) {
        text[text_counter] = byte_array[i];
        printf("Text array at %d: %X", i, text[text_counter]);
        text_counter++;
    }
    return text;
}

int get_current_instruction () {
    int instruction_start = pool_size() + 16;
    return instruction_start + get_program_counter();
}

static word_t swap_word_t(word_t num) {
    return ((num>>24)&0xff) | ((num<<8)&0xff0000) |
           ((num>>8)&0xff00) |
           ((num<<24)&0xff000000);
}

int init_ijvm(char *binary_file) {
    FILE *fptr;
    word_t magic_number;
    byte_t byte_buffer;
    int counter = 0;

    fptr = fopen(binary_file, "rb");
    fread(&magic_number, sizeof(word_t), 1, fptr);
    magic_number = swap_word_t(magic_number);

    // check if the file to be loaded is a valid binary file
    if (magic_number != MAGIC_NUMBER) {
        printf("Invalid file! \n");
        return -1;
    }

    //load the bytes into a byte array
    while (fread(&byte_buffer, sizeof(byte_t), 1, fptr) == 1) {
        byte_array[counter] = byte_buffer;
        counter++;
    }

    fclose(fptr);

    return 0;
}

void destroy_ijvm() {
  // Reset IJVM state
}

bool step() {
    switch (byte_array[get_current_instruction()]) {
        case OP_BIPUSH:
            printf("BIPUSH\n");
            program_counter++;
            break;
        case OP_IADD:
            printf("IADD\n");
            program_counter++;
            break;
        case OP_OUT:
            printf("OUT\n");
            program_counter++;
            break;
        case OP_NOP:
            printf("NOP\n");
            program_counter++;
            break;
        case OP_LDC_W:
            printf("LDC_W\n");
            program_counter++;
            break;
        case OP_DUP:
            printf("DUP\n");
            program_counter++;
            break;
        case OP_HALT:
            printf("HALT\n");
            program_counter++;
            break;
        default:
            program_counter++;
    }
    return 1;
}

void run() {
    for (int i = 0; i < text_size(); ++i) {
        if (step() == 0) {
            printf("Step error \n");
            break;
        }
    }
}

void set_input(FILE *fp) {

}

void set_output(FILE *fp) {

}
