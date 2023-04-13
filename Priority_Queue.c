#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Location {
    int x, y, value;
} Location;
Location EMPTY = {INT_MIN, INT_MIN, INT_MIN};
typedef struct {
    Location *val;
    int head, tail, entries, size;
} Queue;
void swap(Location *a, Location *b) {
    Location temp = *a;
    *a = *b;
    *b = temp;
}
void max_heapify(Location *a, int heapSize, int i) {
    int L = 2 * i + 1;
    int R = 2 * i + 2;
    int largest = i;

    if (L <= heapSize && a[L].value > a[i].value) largest = L;
    if (R <= heapSize && a[R].value > a[largest].value) largest = R;
    if (largest != i) {
        swap(&a[i], &a[largest]);
        max_heapify(a, heapSize, largest);
    }
}
void min_heapify(Location *a, int heapSize, int i) {
    int L = 2 * i + 1;
    int R = 2 * i + 2;
    int smallest = i;

    if (L <= heapSize && a[L].value < a[i].value) smallest = L;
    if (R <= heapSize && a[R].value < a[smallest].value) smallest = R;
    if (smallest != i) {
        swap(&a[i], &a[smallest]);
        min_heapify(a, heapSize, smallest);
    }
}
void build_max_heap(Queue *q) {
    for (int i = q->tail / 2; i >= q->head; i--)
        max_heapify(q->val, q->tail, i);
}
void build_min_heap(Queue *q) {
    for (int i = q->tail / 2; i >= 0; i--) min_heapify(q->val, q->tail, i);
}
bool Qempty(Queue *q) { return (q->entries == 0); }
bool Qfull(Queue *q) { return (q->entries == q->size); }
int Qinit(Queue *q, int size) {
    q->size = size;
    q->head = q->tail = q->entries = 0;
    q->val = malloc(sizeof(Location) * size);
    return 1;
}
void Qdestroy(Queue *q) { free(q->val); }
int Qpush(Queue *q, int x, int y, int value) {
    if (Qfull(q)) return -1;
    q->val[q->tail].x = x, q->val[q->tail].y = y, q->val[q->tail].value = value;
    q->entries++;
    // build_min_heap(q);
    build_max_heap(q);
    q->tail++;
    return 1;
}
Location Qpop(Queue *q) {
    if (Qempty(q)) return EMPTY;
    Location a = q->val[q->head];
    swap(&q->val[q->head], &q->val[q->tail - 1]);
    q->tail -= 2;
    q->entries--;
    // build_min_heap(q);
    build_max_heap(q);
    q->tail++;
    return a;
}
Location Qpeek(Queue *q) {
    if (Qempty(q)) return EMPTY;
    return q->val[q->head];
}

int main() {
    int a[] = {99, 0, 5, 20, 123, 0, -1, 72, 21, 22, 13, 8, 7, 67, 29, 1, 2, 4};
    int asize = sizeof(a) / sizeof(*a);
    Queue Q;
    Qinit(&Q, 100);

    for (int i = 0; i < asize; i++) Qpush(&Q, 0, i, a[i]);

    Qpush(&Q, 5, 6, 100);
    Qpush(&Q, 2, 1, 70);
    Qpush(&Q, 7, 2, 300);
    Qpush(&Q, 7, 2, 3);
    Qpush(&Q, 9, 0, 50);
    Qpush(&Q, 0, 3, 12);
    Qpush(&Q, 0, 3, 30);
    Qpush(&Q, 0, 3, 500);

    while (!Qempty(&Q)) {
        Location temp = Qpop(&Q);
        printf("[%d,%d] P:%d\n", temp.x, temp.y, temp.value);
    }
    Qdestroy(&Q);
    return 0;
}
