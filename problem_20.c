#define STACK_SIZE 10000
typedef struct stack{
    int top;
    int size;
    char arr[STACK_SIZE];
} stack;

void initStack(stack *st){
    st->top = -1;
    st->size = 0;
}
void push(stack *st, const char ch){
    if(st->size==STACK_SIZE){
        printf("stack is full");
        return;
    }
    st->arr[++st->top] = ch;
    st->size++;
}

void pop(stack *st){
    if(st->size==0){
        printf("stack is empty..");
        return;
    }
    st->top--;
    st->size--;
}
bool isEmpty(stack *st){
    return st->size==0;
}
char top(stack *st) {
    if (st->size == 0) {
        printf("stack is empty..\n");
        return '\0';
    }
    return st->arr[st->top];
}

bool isValid(char* s) {
    stack st;
    initStack(&st);

    for (int i = 0; s[i] != '\0'; i++) {
        char curr = s[i];

        if (curr == '(' || curr == '[' || curr == '{') {
            push(&st, curr);
        } else if (curr == ')' || curr == ']' || curr == '}') {
            if (isEmpty(&st)) {
                return false;
            }
            char ch = top(&st);
            if ((curr == ')' && ch != '(') ||
                (curr == ']' && ch != '[') ||
                (curr == '}' && ch != '{')) {
                return false;
            }
            pop(&st);
        }
    }

    return isEmpty(&st);
}