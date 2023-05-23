# include <stdio.h>
# include <stdlib.h>
# include "stack.h"

struct stack
{
    int top;  // index of the top element
    int capacity;  // capacity of the stack
    float *array;  // array to store the elements
};

int main(int argc, char const *argv[])
{
    Stack* stack = create_stack();
    push_stack(stack, 1.0);
    push_stack(stack, 2.0);
    push_stack(stack, 3.0);
    push_stack(stack, 4.0);
    push_stack(stack, 5.0);
    push_stack(stack, 6.0);

    display_stack(stack);
    
    printf("pop: %f\n", pop_stack(stack));
    printf("pop: %f\n", pop_stack(stack));
    printf("pop: %f\n", pop_stack(stack));
    printf("pop: %f\n", pop_stack(stack));

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
    stack->top = 0;
    stack->capacity = STACK_SIZE;
    stack->array = (float*) malloc(stack->capacity * sizeof(float));
    if (stack->array == NULL) {
        printf("Error: memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    return stack;
}

void push_stack(Stack* stack, float value) {
    if (stack->top == stack->capacity) {
        printf("WARNING: stack overflow.\n");
        stack->capacity += STACK_SIZE;
        stack->array = (float*) realloc(stack->array, stack->capacity * sizeof(float));
        if (stack->array == NULL) {
            printf("Error: memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
    }
    stack->array[stack->top++] = value;
}

float pop_stack(Stack* stack) {
    if (is_empty_stack(stack)) {
        printf("WARNING: stack underflow.\n");
        return 0;
    }
    return stack->array[--stack->top];
}

int is_empty_stack(Stack* stack) {
    return stack->top == 0;
}

void free_stack(Stack* stack) {
    free(stack->array);
    free(stack);
}

void display_stack(Stack* stack) {
    printf("Stack: \n");
    // display last inserted element first
    for (int i = stack->top - 1; i >= 0; i--) {
        printf("%f\n", stack->array[i]);
    }
}

