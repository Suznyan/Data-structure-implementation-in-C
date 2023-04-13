#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *val;
    int top, entries, size;
} Stack;
void Stack_init(Stack *S, int maxSize) {
    S->val = malloc(sizeof(int) * maxSize);
    S->top = -1;
    S->entries = 0;
    S->size = maxSize;
}
bool Stack_empty(Stack *S) { return (S->entries == 0); }
bool Stack_full(Stack *S) { return (S->entries == S->size); }
int Stack_push(Stack *S, int a) {
    if (Stack_full(S)) return -1;
    S->val[++S->top] = a;
    S->entries++;
    return 1;
}
int Stack_pop(Stack *S) {
    if (Stack_empty(S)) return INT_MIN;
    int temp = S->val[S->top--];
    S->entries--;
    return temp;
}
int Stack_peek(Stack *S) {
    if (Stack_empty(S)) return INT_MIN;
    return S->val[S->top];
}
void Stack_destroy(Stack *S) { free(S->val); }
