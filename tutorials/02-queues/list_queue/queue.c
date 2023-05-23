# include <stdio.h>
# include <stdlib.h>
# include "queue.h"

typedef struct node Node;
struct node {
    float value;  // value of the node
    Node* next;  // pointer to the next node
};

struct queue {
    Node* front;  // pointer to the front element
    Node* rear;  // pointer to the rear element
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
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

void enqueue(Queue* queue, float value) {
    Node* node = (Node*) malloc(sizeof(Node));
    if (node == NULL) {
        printf("Error: memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    node->value = value;  // set the value of the new node
    node->next = NULL;  // the new node is the last node

    if (queue->rear != NULL) // if the queue is not empty
        queue->rear->next = node;  // set the next of the rear node to the new node
    else  // if the queue is empty
        queue->front = node;  // set the front to the new node
    queue->rear = node;  // set the rear to the new node
}

float dequeue(Queue* queue) {
    Node* temp = queue->front;  // get the front node
    float value = temp->value;  // get the value of the front node
    queue->front = temp->next; // set the front to the next node
    if (queue->front == NULL)  // if the queue is empty
        queue->rear = NULL;  // set the rear to NULL
    free(temp);  // free the memory of the front node
    return value;  // return the value of the front node
}

int is_empty_queue(Queue* queue) {
    return queue->front == NULL;
}
void free_queue(Queue* queue) {
    Node* node = queue->front;
    while (node != NULL) {
        Node* temp = node->next;
        free(node);
        node = temp;
    }
    free(queue);
}

void display_queue(Queue* queue) {
    Node* node = queue->front;
    printf("Queue: \n");
    while (node != NULL) {
        printf("%f\n", node->value);
        node = node->next;
    }
    printf("\n");
}

