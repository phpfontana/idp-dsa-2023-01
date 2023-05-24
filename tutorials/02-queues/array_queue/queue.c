# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "queue.h"

struct queue {
    float* data;  // pointer to the array that stores the data
    int start;  // index of the first element
    int dim;  // dimension of the array
    int n;  // number of elements in the queue
};

int main(int argc, char const *argv[])
{
    Queue* queue = create_queue();
    enqueue(queue, 1.0);
    enqueue(queue, 2.0);
    enqueue(queue, 3.0);
    enqueue(queue, 4.0);
    enqueue(queue, 5.0);
    
    display_queue(queue);
    
    printf("Dequeue: %f\n", dequeue(queue));
    printf("Dequeue: %f\n", dequeue(queue));
    printf("Dequeue: %f\n", dequeue(queue));

    display_queue(queue);
    free_queue(queue);
    return 0;
}


Queue* create_queue(void) {
    Queue* queue = (Queue*) malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Error: memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    queue->dim = QUEUE_SIZE;  // initial dimension
    queue->data = (float*) malloc(queue->dim * sizeof(float));  // initial allocation
    if (queue->data == NULL) {
        printf("Error: memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    queue->start = 0;  // initial index
    queue->n = 0;  // initial size
    return queue;
}

void enqueue(Queue* queue, float value) {
    int last;  // index of the last element
    if (queue->n == queue->dim) { // if the queue is full
        queue->dim += QUEUE_SIZE;  // increase the dimension
        queue->data = (float*) realloc(queue->data, queue->dim * sizeof(float));
        if (queue->data == NULL) {
            printf("Error: memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }
        if (queue->start != 0) {  // if the initial index is not 0
            float* destination = & queue->data[queue->dim - queue->start];
            float* source = & queue->data[queue->start];
            int bytes = (queue->n - queue->start) * sizeof(float);
            memmove(destination, source, bytes);
        }
    }
    last = (queue->start + queue->n) % queue->dim;
    queue->data[last] = value;
    queue->n++;
}

float dequeue(Queue* queue) {
    float value;
    value = queue->data[queue->start];
    queue->start = (queue->start + 1) % queue->dim;
    queue->n--;
    return value;
}

int is_empty_queue(Queue* queue) {
    return queue->n == 0;
}

void free_queue(Queue* queue) {
    free(queue->data);
    free(queue);
}

void display_queue(Queue* queue) {
    printf("Queue: \n");
    for (int i = 0; i < queue->n; i++) {
        printf("%f ", queue->data[(queue->start + i) % queue->dim]);
    }
    printf("\n");
}

