#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
    int isMinHeap; // 1 for min-heap, 0 for max-heap
} Heap;

Heap* createHeap(int capacity, int isMinHeap) {
    Heap* h = (Heap*)malloc(sizeof(Heap));
    h->data = (int*)malloc(sizeof(int) * capacity);
    h->size = 0;
    h->capacity = capacity;
    h->isMinHeap = isMinHeap;
    return h;
}

void swap(int *a, int *b) {
    int t = *a; *a = *b; *b = t;
}

int compare(Heap* h, int a, int b) {
    if (h->isMinHeap) return a < b;   // min-heap
    else return a > b;                // max-heap
}

void heapPush(Heap* h, int val) {
    if (h->size == h->capacity) return; 
    h->data[h->size] = val;
    int i = h->size++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (compare(h, h->data[i], h->data[p])) {
            swap(&h->data[i], &h->data[p]);
            i = p;
        } else break;
    }
}

int heapPop(Heap* h) {
    if (h->size == 0) return 0;
    int root = h->data[0];
    h->data[0] = h->data[--h->size];
    int i = 0;
    while (1) {
        int l = 2*i+1, r = 2*i+2, target = i;
        if (l < h->size && compare(h, h->data[l], h->data[target])) target = l;
        if (r < h->size && compare(h, h->data[r], h->data[target])) target = r;
        if (target != i) {
            swap(&h->data[i], &h->data[target]);
            i = target;
        } else break;
    }
    return root;
}

int heapTop(Heap* h) {
    return h->size ? h->data[0] : 0;
}

typedef struct {
    Heap *left;  // max heap
    Heap *right; // min heap
} MedianFinder;

MedianFinder* medianFinderCreate() {
    MedianFinder* mf = (MedianFinder*)malloc(sizeof(MedianFinder));
    mf->left = createHeap(100000, 0);  // max heap
    mf->right = createHeap(100000, 1); // min heap
    return mf;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    if (obj->left->size == 0 || num <= heapTop(obj->left))
        heapPush(obj->left, num);
    else
        heapPush(obj->right, num);

    // Balance heaps
    if (obj->left->size > obj->right->size + 1) {
        heapPush(obj->right, heapPop(obj->left));
    } else if (obj->right->size > obj->left->size) {
        heapPush(obj->left, heapPop(obj->right));
    }
}

double medianFinderFindMedian(MedianFinder* obj) {
    if (obj->left->size > obj->right->size)
        return heapTop(obj->left);
    else
        return ((double)heapTop(obj->left) + heapTop(obj->right)) / 2.0;
}

void medianFinderFree(MedianFinder* obj) {
    free(obj->left->data);
    free(obj->right->data);
    free(obj->left);
    free(obj->right);
    free(obj);
}
