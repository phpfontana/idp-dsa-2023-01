# ifndef _QUEUE_H_
# define _QUEUE_H_

typedef struct queue Queue;

Queue* create_queue(void);
void enqueue(Queue* queue, float value);
float dequeue(Queue* queue);
int is_empty_queue(Queue* queue);
void free_queue(Queue* queue);
void display_queue(Queue* queue);

# endif