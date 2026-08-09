#include "adt.h"
#include <stdio.h>
void stackInit(Stack *s) { s->top = -1; }
int stackIsEmpty(const Stack *s) { return s->top < 0; }
int stackIsFull(const Stack *s) { return s->top == CAPACITY - 1; }
int stackPush(Stack *s, int value) {
    /* TODO: reject a full stack, then add value at the top. */
    if (stackIsFull(s)) {
        printf("Stack is full");
        return 0;
    } 
    s->top++;
    s->data[s->top] = value;
    (void)s; (void)value; return 1;
}
int stackPop(Stack *s, int *value) {
    /* TODO: reject an empty stack, then remove the top value. */
    // If top == -1 indicates an empty stack
    if (stackIsEmpty(s)) {
      printf("Stack is Empty");  
    return 0; 
    }
    *value = s->data[s->top];
    s->top--;
    (void)s; (void)value; return 1;
}
void queueInit(Queue *q) { q->front = 0; q->rear = -1; q->count = 0; }
int queueIsEmpty(const Queue *q) { return q->count == 0; }
int queueIsFull(const Queue *q) { return q->count == CAPACITY; }
int enqueue(Queue *q, int value) {
    /* TODO: wrap rear with % CAPACITY, store value, update count. */
    if (queueIsFull(q)) {
        printf("Queue is full.");
        return 0;
    }
    q->rear = (q->rear + 1) % CAPACITY;
    q->data[q->rear] = value;
    q->count++;
    (void)q; (void)value; return 1;
}
int dequeue(Queue *q, int *value) {
    /* TODO: read front, wrap front with % CAPACITY, update count. */
    if (queueIsEmpty(q)) {
        printf("Queue is Empty");
        return 0;
    }
    *value = q->data[q->front];
    q->front = (q->front + 1) % CAPACITY;
    q->count--;

    (void)q; (void)value; return 1;
}
