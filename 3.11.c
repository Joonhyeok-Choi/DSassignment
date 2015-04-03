//
//  main.c
//  datastructure
//
//  Created by 준혁 on 2015. 3. 12..
//  Copyright (c) 2015년 준혁. All rights reserved.
//

#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
    int data;
    struct Node*next;
}ND;
typedef ND*PTN; //struct 포인터 ND를 PTN으로 쓰겠다.
typedef PTN list; //뒤에서 list와 position의 구분을 두기 위해 같은 ND지만 타입지정을 따로 해줌
typedef PTN position;

/*
 insert함수
 p뒤에 x를 가진 노드를 추가
*/
void insert(int x, position p){
    position tmpcell;
    
    tmpcell=(position)malloc(sizeof(ND));
    if(tmpcell==NULL)
        printf("out of space");
    
    tmpcell->data=x;
    tmpcell->next=NULL;
    
    tmpcell->next=p->next;
    p->next=tmpcell;
}
/*
 find함수
 l에서 x의 노드 위치를 반환
 */
position find(int x, list l){
    position p;
    
    p=l->next; //l의 첫번째 노드를 p로 지정
    if(x<0) //찾는 값이 음수이면 첫 번째 노드의 주소를 반환
        return l;
    else
        while(p!=NULL && p->data!=x)//마지막 노드가 아니고 찾고자 하는 x가 아닐 때 계속 진행
            p=p->next; //못 찾았으니 그 다음 노드로 다시 지정
    return p; //찾았다면 그 위치를 반환
    
}
/*
 findp함수
 x의 앞의 주소를 반환
 */
position findp(int x, list l){
    position p;
    position address;
    address=find(x, l); //find함수를 이용해서 x값이 리스트 안에 있는지 확인
    p=l;
    if(address!=NULL){ //없다면 NULL을 반환하기에 NULL이 아니라면 찾기 시작
        while(p->next!=NULL && p->next->data!=x) //p의 다음 것의 data가 x인지 확인
            p=p->next; //못 찾았으니 그 다음 노드로 다시 지정
        return p; //찾았다면 그 위치를 반환
    }else
        return 0; //x가 리스트 안에 없다면 0을 반환
}
/*
 det함수
 리스트에서 x를 삭제
 */
void det(int x, list l){
    position p, tmpcell;
    
    p=findp(x, l); //x의 앞 주소를 찾는다
    if(p){ //x가 리스트 안에 있다면 0이 아닌 값을 반환하기에 p를 인자로 둠
        tmpcell=p->next;
        p->next=tmpcell->next;
        free(tmpcell);
    }
}
/*
 datainsert함수
 리스트에 y 뒤에 x를 삽입
 */
void datainsert(list l, int x, int y){
    position tmp=find(y, l); //y가 리스트 안에 있는지 확인
    while(tmp){ //안에 있다면 0이 아닌 수를 반환함으로 인자로 tmp를 둠
        insert(x, tmp); //tmp뒤에 x를 삽입
        break;
    }
}
/*
 printlist함수
 리스트의 모든 값들을 출력해준다.
 */
void printlist(list l){
    l=l->next; //첫 노드는 값이 주소 값이기에 다음 것부터 시작한다.
    while(1){
        printf("%d\n", l->data);
        if(l->next==NULL)break; //리스트의 끝이면 중지한다.
        l=l->next;
    }
}
/*
 main함수
 printlist함수 후에 0을 반환하며 프로그램 종료
 */
int main(){
    list l; //리스트 초기화
    position p;
    char command;
    int x, y;
    l=(list)malloc(sizeof(list));
    l->next=NULL;
    while(1){
        scanf("%c[^ ]", &command); //scanf할 때 엔터가 아닌 스페이스바만 눌러도 입력 가능하게 함.
        switch(command){
            case 'i':
                scanf("%d %d", &x, &y);
                datainsert(l, x, y);
                break;
            case 'p':
                printlist(l);
                return 0; //프로그램 종료
            case 'd':
                scanf("%d", &x);
                det(x, l);
                break;
            case 'f':
                scanf("%d", &x);
                p=findp(x, l);
                if(p!=l){ //x가 리스트의 첫번째라면 그 앞에 것이 없기에 첫번째가 아닌 경우에만 실행
                    while(p){ //x가 리스트안에 없다면 0이 반환되기에 진행 인자를 p로 잡음
                        //p=p->next;
                        printf("%d\n", p->data);
                        break;
                    }break;
                }else
                    break;
        }
    }
}