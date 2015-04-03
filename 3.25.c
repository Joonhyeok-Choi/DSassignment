//
//  main.c
//  3.25
//
//  Created by 준혁 on 2015. 3. 25..
//  Copyright (c) 2015년 준혁. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct StackRecord{
    int capacity;
    int TopOfStack;
    char *array;
};
typedef struct StackRecord *Stack;
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
void Push(char x, Stack s){
    if(IsFull(s))
        printf("Full of stack");
    else
        s->array[++s->TopOfStack]=x;//if s is not full than it pushes x to s by increasing TopOfStack.
}
/*
 function CreateStack
 It creates Stack s and initializes all the variables.
 */

Stack CreateStack(int MaxElements){
    Stack s;
    
    if(MaxElements<MinStackSize)
        printf("Stack size is too small");
    
    s=(Stack)malloc(sizeof(struct StackRecord));
    
    /*if(s->array == NULL)
        printf("Out of space");*/
    s->array=(char*)malloc(sizeof(char)*MaxElements);
    s->capacity=MaxElements;
    MakeEmpty(s);
    
    return s;
}
/*
 function Top
 It returns the value at the top of the stack.
 */
char Top(Stack s){
    if(!IsEmpty(s))
        return s->array[s->TopOfStack];
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
/*
 function precedence
 It returns the precedence number of the input character.
 */
int precedence(char c){
    int a=0;
    switch(c){
            case '(':
                a= 0;
            break;
            
            case '*':
            case '%':
            case '/':
                a= 2;
            break;
            case '+':
            case '-':
                a= 1;
            break;
        default:
            break;
    }
    return a;
}
/*
 function main
 
 */

int main(){
    unsigned long slength;
    int i;
    char c;//current character
    char *input=(char*)malloc(sizeof(char)*40);//initialize the input
    int cp;//current precedence
    int tosp;//top of stack precedence
    Stack s=CreateStack(40);
    printf("original infix form : ");
    scanf("%[^#]s", input);fflush(stdin);
    printf("converted postfix form : ");
    slength=strlen(input);
    for(i=0;i<slength;i++){//for loop runs until the end of input.
        c=input[i];
        if('1'<=c&&c<='9'&&i==slength-1){//if c is int and the last number
            putchar(c);//print the number
            while(s->TopOfStack!=-1){//print the remainders in the stack.
                putchar(Top(s));
                Pop(s);
            }
        }
        else if('1'<=c&&c<='9')//if c is number but not the last one.
            putchar(c);//print it
        else if(IsEmpty(s)){//if c is an operator and the stack is empty.
            Push(c, s);//push it to the s.
        }
        else{//if c is an operator but the stack is not empty.
            cp=precedence(c);//cp is the precedence of c.
            tosp=precedence(s->array[s->TopOfStack]);//tosp is the precedence of the value at the top of the stack.
            if(cp>tosp){
                Push(c, s);
            }
            else if(c=='('){
                Push(c, s);
            }
            else if(c==')'){
                if(i==slength-1){//if c is ')' and it is the last one
                    while(s->array[s->TopOfStack]!='('){//print all operators until '('.
                        putchar(Top(s));
                        Pop(s);
                    }Pop(s);
                    while(s->TopOfStack!=-1){//and print the rest operators after '('.
                        putchar(Top(s));
                        Pop(s);
                    }
                }
            
                else{//if c is ')' but not the last one.
                    while(s->array[s->TopOfStack]!='('){//print all operators until '('.
                        putchar(Top(s));
                        Pop(s);
                    }Pop(s);
                }
            }else{//if tosp is bigger than cp or same with cp,
                while(cp<=tosp){
                    putchar(Top(s));//print the top value.
                    Pop(s);
                    if(s->TopOfStack==-1){//if the top value just printed was the last one in the stack
                        
                        Push(c,s);//push c to the s.
                        break;
                    }
                    tosp=precedence(s->array[s->TopOfStack]);//if the top value was not the last one than change tosp.
                }
                if(s->TopOfStack==0)//if the top value was the last one than skip to the next process.
                    continue;
                else//if cp > tosp than push c to s.
                    Push(c,s);
            }
        }
    }
}
