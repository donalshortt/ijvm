#include <ijvm.h>
#include <stdlib.h>

typedef struct {
    word_t c_origin;
    word_t c_size;
    word_t *c_data;

    word_t t_origin;
    word_t t_size;
    byte_t *t_data;

    int pc;
} block_t;

block_t *ijvm;

static word_t swap_word(word_t num) {
    return ((num>>24)&0xff) | ((num<<8)&0xff0000) | ((num>>8)&0xff00) | ((num<<24)&0xff000000);
}

int init_ijvm(char *binary_file) {
    // Implement loading of binary here

    FILE *fp;
    fp = fopen(binary_file, "rb");
    if(fp == NULL) {
        printf("could not open file\n");
        return -1;
    }

    word_t buffer;
    fread(&buffer, sizeof(word_t), 1, fp); //reading the header to check

    buffer = swap_word(buffer);

    if(buffer != MAGIC_NUMBER) {
        printf("invalid file\n");
        return -1;
    }

    ijvm = malloc(sizeof(block_t));

    //constant pool
    fread(&buffer, sizeof(word_t), 1, fp); //reading const. pool origin
    ijvm->c_origin = swap_word(buffer);

    fread(&buffer, sizeof(word_t), 1, fp); //reading const. pool size
    ijvm->c_size = swap_word(buffer);

    ijvm->c_data = malloc((ijvm->c_size/4)*sizeof(word_t));
    fread(ijvm->c_data, sizeof(word_t), ijvm->c_size/4, fp); //reading const. pool data

    //text
    fread(&buffer, sizeof(word_t), 1, fp); //reading text origin
    ijvm->t_origin = swap_word(buffer);

    fread(&buffer, sizeof(word_t), 1, fp); //reading text size
    ijvm->t_size = swap_word(buffer);

    ijvm->t_data = malloc(ijvm->t_size*sizeof(byte_t));
    fread(ijvm->t_data, sizeof(byte_t), ijvm->t_size, fp); //reading text data

    ijvm->pc = 0;

    fclose(fp);

    return 0;
}

void destroy_ijvm() {
    // Reset IJVM state
    free(ijvm->c_data);
    free(ijvm->t_data);
    free(ijvm);
}

void run() {
    // Step while you can

    while(!finished()) {
        //if(!step())
        //{
        //printf("");
        //}

        //printf("\n");
        //ijvm->pc++;
    }

}

void set_input(FILE *fp) {
    // TODO: implement me
}

void set_output(FILE *fp) {
    // TODO: implement me
}

byte_t *get_text() {
    return ijvm->t_data;
}

int text_size() {
    return ijvm->t_size;
}

int get_program_counter() {
    return ijvm->pc;
}

word_t get_local_variable(int i) {
    return 0;
}

word_t get_constant(int i) {
    return swap_word(*(ijvm->c_data+i));
}

bool step() {
    /*printf("%d. ", get_program_counter());*/
    switch(get_instruction()){
        case OP_BIPUSH:
            printf("OP_BIPUSH");
            break;
        case OP_DUP:
            printf("OP_DUP");
            break;
        case OP_ERR:
            printf("OP_ERR");
            break;
        case OP_GOTO:
            printf("OP_GOTO");
            break;
        case OP_HALT:
            printf("OP_HALT");
            break;
        case OP_IADD:
            printf("OP_IADD");
            break;
        case OP_IAND:
            printf("OP_IAND");
            break;
        case OP_IFEQ:
            printf("OP_IFEQ");
            break;
        case OP_IFLT:
            printf("OP_IFLT");
            break;
        case OP_ICMPEQ:
            printf("OP_ICMPEQ");
            break;
        case OP_IINC:
            printf("OP_IINC");
            break;
        case OP_ILOAD:
            printf("OP_ILOAD");
            break;
        case OP_IN:
            printf("OP_IN");
            break;
        case OP_INVOKEVIRTUAL:
            printf("OP_INVOKEVIRTUAL");
            break;
        case OP_IOR:
            printf("OP_IOR");
            break;
        case OP_IRETURN:
            printf("OP_IRETURN");
            break;
        case OP_ISTORE:
            printf("OP_ISTORE");
            break;
        case OP_ISUB:
            printf("OP_ISUB");
            break;
        case OP_LDC_W:
            printf("OP_LDC_W");
            break;
        case OP_NOP:
            printf("OP_NOP");
            break;
        case OP_OUT:
            printf("OP_OUT");
            break;
        case OP_POP:
            printf("OP_POP");
            break;
        case OP_SWAP:
            printf("OP_SWAP");
            break;
        case OP_WIDE:
            printf("OP_WIDE");
            break;
        default:
            printf("%.2X", get_instruction());
    }
    ijvm->pc++;
    printf("\n");
    return true;
}

bool finished() {
    if(ijvm->pc+1==ijvm->t_size) {
        return true;
    }

    if(get_instruction()==OP_HALT || get_instruction()==OP_ERR) {
        return true;
    }

    if(step() == false) {
        return true;
    }

    return false;
}

byte_t get_instruction() {
    return *(ijvm->t_data+ijvm->pc); //currently pointed to instruction at pc;
}