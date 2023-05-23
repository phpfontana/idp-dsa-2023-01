# ifndef _STACK_H_
# define _STACK_H_

typedef struct stack Stack;

# define STACK_SIZE 5

Stack* create_stack(void);
void push_stack(Stack* stack, float value);
float pop_stack(Stack* stack);
int is_empty_stack(Stack* stack);
void free_stack(Stack* stack);
void display_stack(Stack* stack);

# endif