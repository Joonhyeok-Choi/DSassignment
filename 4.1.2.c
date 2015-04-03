//
//  main.c
//  4.1.2
//
//  Created by 준혁 on 2015. 4. 1..
//  Copyright (c) 2015년 준혁. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

struct QueRecord{
    int Capacity;
    int Front;
    int Rear;
    int Size;
    int *Array;
};
typedef struct QueRecord *Que;

int IsFull(Que Q){
    return Q->Capacity==Q->Size;
}
void MakeEmpty(Que Q){
    Q->Size = 0;
    Q->Front = 1;
    Q->Rear = 0;
}

int Succ(int value, Que Q){
    if(++value==Q->Capacity)
        value=0;
    return value;
}

void EnQue(int X, Que Q){
    if(IsFull(Q))
        printf("Full Que\n");
    else{
        Q->Size++;
        Q->Rear = Succ(Q->Rear, Q);
        Q->Array[Q->Rear]=X;
    }
}

int IsEmpty(Que Q){
    return Q->Size == 0;
}

Que CreateQue(int Capacity){
    Que Q;
    Q=(Que)malloc(sizeof(struct QueRecord));
    Q->Array=(int*)malloc(sizeof(int)*Capacity);
    Q->Capacity=Capacity;
    MakeEmpty(Q);
    
    return Q;
}

void DeQue(Que Q){
    if(IsEmpty(Q))
        printf("Empty Que\n");
    else{
        Q->Size--;
        Q->Front=Succ(Q->Front, Q);
    }
}

void PrintFront(Que Q){
    if(IsEmpty(Q))
        printf("Empty Que\n");
    else{
        printf("%d\n", Q->Array[Q->Front]);
    }
}

void PrintRear(Que Q){
    if(IsEmpty(Q))
        printf("Empty Que\n");
    else{
        printf("%d\n", Q->Array[Q->Rear]);
    }
}

int main(){
    int n;
    char command;
    Que Q=CreateQue(0);
    while(1){
        scanf("%c[^ ]", &command);
        switch(command){
            case 'n':
                scanf("%d", &n);
                Q=CreateQue(n);
                
                break;
            case 'e':
                scanf("%d", &n);
                EnQue(n, Q);
                
                break;
            case 'd':
                DeQue(Q);
                
                break;
            case 'f':
                PrintFront(Q);
                
                break;
            case 'r':
                PrintRear(Q);
                
                break;
            
        }

    }
}


