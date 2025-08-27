/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef struct Deque{
    int *indxarr;
    int front, back;
}Deque;

void initDeque(Deque *dq, int size){
    dq->indxarr = malloc(sizeof(Deque)*size);
    dq->front = 0;
    dq->back = -1;
}

void push_back(Deque *dq, int x){
    dq->indxarr[++dq->back]=x;
}

void pop_back(Deque *dq){
    dq->back--;
}
void pop_front(Deque *dq){
    dq->front++;
}
int front(Deque *dq){
    return dq->indxarr[dq->front];
}
int back(Deque *dq){
    return dq->indxarr[dq->back];
}
bool isEmpty(Deque *dq){
    return dq->front>dq->back;
}

int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (numsSize == 0 || k == 0) {
        *returnSize = 0;
        return NULL;
    }
    int size = numsSize-k+1;
    int indx = 0;
    int *ans = malloc(sizeof(int)*size);
    Deque dq;
    initDeque(&dq, numsSize);

    for(int i=0; i<numsSize; i++){
        if(!isEmpty(&dq) && front(&dq)<=i-k){
            pop_front(&dq);
        }

        while(!isEmpty(&dq) && nums[back(&dq)]<=nums[i]){
            pop_back(&dq);
        }
        push_back(&dq, i);
        if(i>=k-1){
            ans[indx++] = nums[front(&dq)];
        }
    }
    *returnSize = indx;
    return ans;
}