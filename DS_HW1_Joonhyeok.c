//
//  main.c
//  DS_HW1_Joonhyeok
//
//  Created by 준혁 on 2015. 3. 29..
//  Copyright (c) 2015년 준혁. All rights reserved.
//
/*
 텍스트파일로 부터 입력 값을 받아 연결리스트로 다항식의 덧셈과 곱셈을 한 뒤
 다시 텍스트파일에 그 결과 값을 출력하는 코드
 */

#include <stdio.h>
#include <stdlib.h>
/*
 계수와 지수를 가지는 자기 참조 구조체 Node 선언
 */
typedef struct Node{
    int coeff;
    int expon;
    struct Node* next;
}polyPTN;
typedef polyPTN* PPTN;

/*
 attach함수
 리스트 rear, 계수, 지수를 매개 변수로 받아 리스트 rear에 입력받은 계수와 지수를 갖는 노드를 연결하는 함수이다.
 */
void attach(PPTN rear, int coeff, int expon){
    PPTN temp, p;
    
    temp=(PPTN)malloc(sizeof(polyPTN));//연결할 노드에 입력받은 계수와 지수를 입력
    temp->coeff=coeff;
    temp->expon=expon;
    temp->next=NULL;
    if(rear->next==NULL){//리스트 rear가 비어있다면 첫 번째 노드로 temp를 연결
        temp->next=rear->next;
        rear->next=temp;
    }
    else{//리스트 rear가 비어있지 않다면 젤 끝 노드 뒤에 temp를 연결
        p=rear;
        while(p->next!=NULL)
            p=p->next;
        temp->next=p->next;
        p->next=temp;
    }
}

/*
 Init함수
 뒤에 나올 pmultiply함수에서 리스트를 초기화 시켜줄 경우가 
 있기에 그것을 위한 함수이다
 */
PPTN Init(PPTN temp){
    PPTN tmpcell, tmpcell2;
    tmpcell=(PPTN)malloc(sizeof(polyPTN));//모든 값을 0으로 초기화하기 위한 노드 초기화
    tmpcell->coeff=0;
    tmpcell->expon=0;
    tmpcell->next=NULL;
    
    while(temp->next!=NULL)//가장 마지막 노드 뒤에 0으로 초기화된 노드를 연결
        temp=temp->next;
    tmpcell->next=temp->next;
    temp->next=tmpcell;
    
    while(temp->next!=NULL){//마지막에 0으로 초기화한 노드를 제외한 노드를 제거
        tmpcell2=temp;
        temp=temp->next;
        free(tmpcell2);
    }return temp;//모든 값이 0인 노드하나만 있는 리스트 반환
}

/*
 perase함수
 모든 다항식을 제거해주는 함수이다.
 */
void perase(PPTN a){
    PPTN temp;
    
    while(a){//리스트 a가 없어질 때까지 반복
        temp=a;
        a=a->next;
        free(temp);
    }
}

/*
 compare함수
 지수 비교를 하여 각 경우의 수에 맞는 값을 반환하는 함수이다.
 */
int compare(int a, int b){
    if(a>b)//다항식 a와 b의 지수를 입력받아 a가 큰 경우 1을 반환하고
        return 1;
    else if(a==b)//두 수가 같을 경우 0을 반환하고
        return 0;
    else//b가 큰 경우 -1을 반환.
        return -1;
}

/*
 padd함수
 다항식 a, b를 입력받아 두 다항식을 더한 결과를 반환하는 함수이다.
 */
PPTN padd(PPTN a, PPTN b){
    PPTN rear;
    int sum;
    rear=(PPTN)malloc(sizeof(polyPTN));//두 다항식의 합을 저장하는 다항식 리스트
    
    while(a&&b){
        switch(compare(a->expon, b->expon)){//a와 b의 지수들을 비교하여 반환값에 따라 switch문이 작동
            case -1://-1 즉, b의 지수가 더 크기에 b의 계수와 지수를 갖는 노드를 rear에 연결
                attach(rear, b->coeff, b->expon);
                b=b->next;//b를 다음 노드로 변경
                break;
            case 0://0 즉, 두 지수가 같기에 두 계수를 더하여 sum에 넣는다.
                sum=a->coeff+b->coeff;
                if(sum)
                    attach(rear, sum, a->expon);//sum을 계수, a를 지수로 갖는 노드를 rear에 연결
                a=a->next;b=b->next;break;//a, b를 다음 노드로 변경
            case 1://1 즉, a의 지수가 더 크기에 a의 계수와 지수를 갖는 노드를 rear에 연결
                attach(rear, a->coeff, a->expon);
                a=a->next;//a를 다음 노드로 변경
                break;
        }
    }//while문이 끝났다는 것은 a, b 모두 다 rear에 연결되었거나 둘 중 하나만 다 연결되었다는 뜻
    for(; a; a=a->next)attach(rear, a->coeff, a->expon);//그러므로 a, b 노드를 돌며 남은 것을 rear에 연결
    for(; b; b=b->next)attach(rear, b->coeff, b->expon);
    return rear;//모든 결과인 rear를 반환
}

/*
 pmultiply함수
 다항식 a, b를 입력받아 두 다항식을 곱한 결과를 반환하는 함수이다.
 a의 모든 항은 한 항씩 차례대로 돌며 b의 모든 항과 곱한다. 그리고 그 값을 모두 더한 것이 다항식 곱의 결과이다.
 그래서 바깥 for문을 다항식 a로 정했고 안의 for문을 b로 정하여 a의 모든 항이 한 항씩 차례대로 b의 모든 항과 곱할 수
 있게 하였다.
 */
PPTN pmultiply(PPTN a, PPTN b){
    /*
     ta, tb는 아래 for문에서 초기값 설정을 위한 다항식리스트 변수
     temp는 바깥 for문의 a가 안의 for문의 b의 모든 항과 곱한 값을 담는 변수
     temp2는 바깥 for문의 a의 한 항이 안의 for문의 b의 모든 항과 곱하여 만들어진 모든 값을 더한 것을 담는 변수 즉, 결과값이다.
     */
    PPTN ta, tb, temp, temp2;
    int mp, sum;
    temp=(PPTN)malloc(sizeof(polyPTN));
    temp2=(PPTN)malloc(sizeof(polyPTN));
    temp2->next=NULL;
    
    for(ta=a; ta; ta=ta->next){
        for(tb=b; tb; tb=tb->next){
            mp=ta->coeff*tb->coeff;
            sum=ta->expon+tb->expon;
            attach(temp, mp, sum);//a의 한 항이 b의 모든 항과 곱한 결과를 temp에 연결
        }
        temp=temp->next;temp2=temp2->next;//temp와 temp2는 첫 노드가 0이기에 그 다음부터 시작하도록 만듦
        temp2=padd(temp2, temp);//temp2에 temp들을 더 함
        temp=Init(temp);//a의 다음 항이 b의 모든 항과 곱한 것을 담으려면 새로운 노드가 필요하기에 temp를 초기화시킴
    }
    return temp2;//모든 결과인 temp2를 반환
}

void insert(PPTN a, int x, int y){
    PPTN temp, p;
    
    temp=(PPTN)malloc(sizeof(polyPTN));
    temp->coeff=x;
    temp->expon=y;
    temp->next=NULL;
    if(a->next==NULL){
        temp->next=a->next;
        a->next=temp;
    }
    else{
        p=a;
        while(p->next!=NULL)
            p=p->next;
        temp->next=p->next;
        p->next=temp;
    }
}

void printlist(PPTN a){
    while(1){
        printf("%d %d\n", a->coeff, a->expon);
        if(a->next==NULL)break; //리스트의 끝이면 중지한다.
        a=a->next;
    }
}

void det(int dcoeff, PPTN a){
    PPTN tmpcell;
    tmpcell=(PPTN)malloc(sizeof(polyPTN));
    while(a->coeff!=dcoeff){//삭제하고자 하는 노드의 앞 노드까지 돈다
        if(a->next==NULL)
            printf("Deletion failed.");
        tmpcell=a;//a는 삭제하고자 하는 노드의 앞 노드
        a=a->next;//a를 삭제하고자 하는 노드로 한 칸 이동
    }
    tmpcell->next=tmpcell->next->next;//삭제하고자 하는 노드의 앞 노드를 삭제하고자하는 노드 다음 노드와 연결
    free(a);//삭제하고자 하는 노드 제거
}


int main(){
    int i, n;
    int x, y;
    PPTN a;
    PPTN b;
    PPTN c, d;
    a=(PPTN)malloc(sizeof(polyPTN));
    b=(PPTN)malloc(sizeof(polyPTN));
    
    FILE*fp;
    
    fp=fopen("/Users/Joonhyeok/Documents/datastructure/DS_HW1_Joonhyeok/input.txt", "r");
    if(fp==NULL)
        printf("file is not found\n");
    fscanf(fp, "%d", &n);
    for(i=0;i<n;i++){
        fscanf(fp, "%d %d", &x, &y);
        insert(a, x, y);
    }
    fscanf(fp, "%d", &n);
    for(i=0;i<n;i++){
        fscanf(fp, "%d %d", &x, &y);
        insert(b, x, y);
    }
    fclose(fp);
    
    a=a->next;b=b->next;
    c=padd(a, b);
    c=c->next;
    d=pmultiply(a, b);
    d=d->next;
    fp=fopen("/Users/Joonhyeok/Documents/datastructure/DS_HW1_Joonhyeok/output.txt", "w+");
    fprintf(fp, "%s", "Addition\n");
    for(; c; c=c->next){
        fprintf(fp, "%d %d\n", c->coeff, c->expon);
    }fprintf(fp, "%s", "Multiplication\n");
    for(; d; d=d->next){
        fprintf(fp, "%d %d\n", d->coeff, d->expon);
    }
    //printlist(c);
    
    //printlist(d);
}