#include <stdio.h>
#include <stdlib.h>
#define MAX 99

struct node {
    int vertex;
    struct node* next;
};
typedef struct node* GNODE;

GNODE graph[20];
int visited[20];
int queue[MAX], front = -1, rear = -1;
int n;

void insertQueue(int vertex) {
    if (rear == MAX - 1)
        printf("Queue Overflow.\n");
    else {
        if (front == -1)
            front = 0;
        rear++;
        queue[rear] = vertex;
    }
}

int isEmptyQueue() {
    return (front == -1 || front > rear);
}

int deleteQueue() {
    if (isEmptyQueue()) {
        printf("Queue Underflow\n");
        exit(1);
    }
    return queue[front++];
}

void BFS(int v) {
    GNODE p;

    insertQueue(v);
    visited[v] = 1;
    
    while (!isEmptyQueue()) {

        v = deleteQueue();
        printf("\n%d", v);
        

        p = graph[v];
        while (p != NULL) {
            int adjacentVertex = p->vertex;
            if (!visited[adjacentVertex]) {
                insertQueue(adjacentVertex);
                visited[adjacentVertex] = 1;
            }
            p = p->next;
        }
    }
}

void main() {
    int N, E, s, d, i, v;
    GNODE p, q;

    printf("Enter the number of vertices: ");
    scanf("%d", &N);
