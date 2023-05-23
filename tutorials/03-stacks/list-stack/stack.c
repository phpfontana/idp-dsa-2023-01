# include <stdio.h>
# include <stdlib.h>
# include "stack.h"

typedef struct node Node;
struct node {
    float value;  // value of the node
    Node* next;  // pointer to the next node
};

struct stack
{
    Node* top;  // pointer to the top element
};

int main(int argc, char const *argv[])
{
    Stack* stack = create_stack();
    push_stack(stack, 1.0);
    push_stack(stack, 2.0);
    push_stack(stack, 3.0);
    push_stack(stack, 4.0);
    push_stack(stack, 5.0);
    
    display_stack(stack);

    printf("Pop: %f\n", pop_stack(stack));
    printf("Pop: %f\n", pop_stack(stack));
    printf("Pop: %f\n", pop_stack(stack));
    printf("Pop: %f\n", pop_stack(stack));

    display_stack(stack);

    free_stack(stack);
    return 0;
}

Stack* create_stack(void) {
    Stack* stack = (Stack*) malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Error: memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    stack->top = NULL;
    return stack;
}

void push_stack(Stack* stack, float value) {
    Node* node = (Node*) malloc(sizeof(Node));
    if (node == NULL) {
        printf("Error: memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    node->value = value;
    node->next = stack->top;
    stack->top = node;
}

float pop_stack(Stack* stack) {
    Node* node = stack->top;  // get the top node
    float value = node->value;  // get the value of the top node
    stack->top = node->next;  // move the top to the next node
    free(node);  // free the top node

    return value;
}

int is_empty_stack(Stack* stack) {
    return stack->top == NULL;
}

void free_stack(Stack* stack) {
    Node* node = stack->top;
    while (node != NULL) {
        Node* temp = node->next;
        free(node);
        node = temp;
    }
    free(stack);
}

void display_stack(Stack* stack) {
    Node* node = stack->top;
    printf("Stack:\n");
    while (node != NULL) {
        printf("%f\n", node->value);
        node = node->next;
    }
}

