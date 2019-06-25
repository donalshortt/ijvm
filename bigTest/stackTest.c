//
// Created by donal on 21/06/19.
//

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct stack_node {
    int32_t data;
    struct stack_node* next_node;
} *root;

bool is_empty(struct stack_node* root) {
    if (root == NULL) {
        return false;
    } else {
        return true;
    }
}

struct stack_node* new_node(int32_t data) {
    struct stack_node* stackNode = malloc(sizeof(struct stack_node));
    stackNode->data = data;
    printf("Data in new node: %d\n", stackNode->data);
    stackNode->next_node = NULL;
    return stackNode;
}

void push(struct stack_node** root, int32_t data) {
    struct stack_node* stackNode = new_node(data);
    stackNode->next_node = *root;
    
    *root = stackNode;
    printf("Data pushed to stack: %d\n", data);
}

int32_t pop(struct stack_node** root) {
    if(is_empty(*root)) {
        return NULL;
    }
    struct stack_node* temp = *root;
    *root = (*root)->next_node;
    int32_t popped = temp->data;
    free(temp);

    return popped;
}

int32_t peek(struct stack_node* root) {
    if(is_empty(root)) {
        return NULL;
    }
    return root->data;
}

// int get_stack_size(struct stack_node* root) { //QUESTION: is iterative or recursive way faster?
//     if (root == NULL) {
//         return 0;
//     } else {
//         return 1 + get_stack_size(root->next_node);
//     }
// }

void traverseList()
{
    struct stack_node *temp;

    // Return if list is empty 
    // if(root == NULL)
    // {
    //     printf("List is empty.");
    //     return;
    // }
    
    temp = root;
    while(temp != NULL)
    {
        printf("Data = %d\n", temp->data); // Print data of current node
        temp = temp->next_node;                 // Move to next node
    }
}

int main() 
{ 
    struct stack_node* root = NULL;
  
    push(&root, 10); 
    push(&root, 20); 
    push(&root, 30); 
  
    printf("%d popped from stack\n", pop(&root)); 
  
    printf("Top element is %d\n", peek(root)); 
    
    traverseList();
    // printf("Count of all elements is: %d", get_stack_size());
  
    return 0; 
} 
