#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct Stack {
    int items[100];
    int top;
    int minEle;
};

void createEmptyStack(struct Stack* s) {
    s->top = -1;
}

void push(struct Stack* s, int data) {
    if(s->top == 99) {
        printf("Stack is Full!!!");
    } else {
        s->top++;
        s->items[s->top] = data;
        if(data<s->minEle) {
            s->minEle = data;
        }
    }
}

int pop(struct Stack* s) {
    if(s->top == -1) {
        printf("Stack is Empty!!!");
    } else {
        s->top--;
        return s->items[s->top+1];
    }
}

int main() {
    struct Stack* intStack = (struct Stack*)malloc(sizeof(struct Stack));
    createEmptyStack(intStack);
    printf("Enter 10 integers to push in stacks:");
    for(int i=0;i<10;i++) 
    {
        int input;
        scanf("%d", &input);
        push(intStack, input);
        if(i==0) {
            intStack->minEle = input;
        }
        else {
            if(input<intStack->minEle) {
                intStack->minEle = input;
            }
        }
    }
    int inputcmd;
    while(1) {
        printf("\ni) Push\nd) Pop\nm) min\nt) top\nq) quit\nEnter your choice: ");
        inputcmd = getche();
        if(inputcmd=='q') {
            break;
        } else if(inputcmd=='t') {
            printf("\ntop == %d", (intStack->top+1));
        } else if(inputcmd=='m') {
            printf("\nmin == %d", intStack->minEle);
        } else if(inputcmd=='d') {
            printf("\n%d Popped", pop(intStack));
        } else if(inputcmd=='i') {
            int newItem;
            printf("\nEnter Element to be pushed: ");
            scanf("%d", &newItem);
            push(intStack, newItem);
        }
    }
    return 0;
}
