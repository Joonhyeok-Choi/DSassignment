//
//  main.c
//  4.1
//
//  Created by 준혁 on 2015. 4. 1..
//  Copyright (c) 2015년 준혁. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StackRecord{
    float *data;
    int TopOfStack;
    int capacity;
};
typedef struct StackRecord* Stack;

#define EmptyTOS (-1)
#define MinStackSize (5)
#define MAXELEMENT 100
/*
 function MakeEmpty
 It makes Stack s empty by initializing TopOfStack to -1.
 It sets TopOfStack by -1 because array of Stack starts at 0.
 */
void MakeEmpty(Stack s){
    s->TopOfStack=EmptyTOS;
}
/*
 function IsFull
 It checks whether Stack s is full or not.
 If TopOfStack is over 100 than it return 1 which means it is full.
 */
int IsFull(Stack s){
    if(s->TopOfStack>100)
        return 1;
    else
        return 0;
}
/*
 function IsEmpty
 It checks whether Stack s is empty or not.
 If TopOfStack is -1 which means it is empty than it returns 1.
 */
int IsEmpty(Stack s){
    if(s->TopOfStack==-1)
        return 1;
    else
        return 0;
}
/*
 function Push
 It pushes x to Stack s.
 */
void Push(float x, Stack s){
    if(IsFull(s))
        printf("Full of stack");
    else
        s->data[++s->TopOfStack]=x;//if s is not full than it pushes x to s by increasing TopOfStack.
}
Stack CreateStack(int MaxElements){
    Stack s;
    
    if(MaxElements<MinStackSize)
        printf("Stack size is too small");
    
    s=(Stack)malloc(sizeof(struct StackRecord));
    
    /*if(s->array == NULL)
     printf("Out of space");*/
    s->data=(float*)malloc(sizeof(float)*MaxElements);
    s->capacity=MaxElements;
    MakeEmpty(s);
    
    return s;
}
/*
 function Top
 It returns the value at the top of the stack.
 */
float Top(Stack s){
    if(!IsEmpty(s))
        return s->data[s->TopOfStack];
    else{
        printf("Empty stack");
        return 0;
    }
}
/*
 function Pop
 It erases the value at the top of the stack and decreases TopOfStack.
 */
void Pop(Stack s){
    if(IsEmpty(s))
        printf("Empty stack");
    else
        s->TopOfStack--;
}
float change(float b, float a, char c){
    switch(c){
            case '+':
            return b+a;
            break;
            case '-':
            return b-a;
            break;
            case '*':
            return b*a;
            break;
            case '/':
            return b/a;
            break;
        default:
            return 0;
            break;
            
    }
}
int main(){
    unsigned long slength;
    int i;
    float a=0, b=0, result=0;
    char c;
    char *input=(char*)malloc(sizeof(char)*30);
    Stack s=CreateStack(30);
    printf("converted postfix form : ");
    scanf("%s", input);fflush(stdin);
    printf("evaluation result : ");
    slength=strlen(input);
    for(i=0;i<slength;i++){
        c=input[i];
        if('1'<=c&&c<='9'){
            Push(c-'0',s);
            //printf("%f\n",Top(s));
        }
        else{
            a=Top(s);
            Pop(s);
            b=Top(s);
            Pop(s);
            result=change(b, a, c);
            //printf("%f\n", result);
            Push(result, s);
        }
    }printf("%f\n", Top(s));
}


