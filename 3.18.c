//
//  main.c
//  3.18
//
//  Created by 준혁 on 2015. 3. 18..
//  Copyright (c) 2015년 준혁. All rights reserved.
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node *PtrToNode;
typedef PtrToNode list;
typedef PtrToNode position;
typedef struct{
    int ID;
    char name[30];
}ElementType;
struct Node{
    ElementType element;
    PtrToNode next;
};
/*
 find 함수
 중복 된 id 입력을 피하기 위해
 id값을 받아서 리스트 안에 있는지 확인한다.
 있다면 1을 리턴한다.
 */
int find(int id, list l){
    position p=l;//주 리스트인 l 대신 p를 만들어 사용
    while(p!=NULL&&p->element.ID!=id)
        p=p->next;
    if(p!=NULL)
        return 1;
    else
        return 0;
}
/*
 find2함수
 delete함수를 사용하기 위해 id 앞의 값을 구하려고
 id의 위치를 찾는 함수이다.
 */
position find2(int id, list l){
    position p=l; //주 리스트인 l 대신 p를 만들어 사용
    while(p!=NULL&&p->element.ID!=id)
        p=p->next;
    return p;
}
/*
 findposition함수
 리스트를 id의 순서대로 정리하기 위한 함수.
 id가 다음에 오는 값보다 작아질 때 그 값의 앞에 위치한 리스트의 주소를 리턴한다.
 그 이유는 입력받은 값을 리스트에 연결하려면 앞의 값이 필요하기 때문이다.
 */
position findposition(int id, list l){
    position p;//주 리스트인 l 대신 p를 만들어 사용
    position q;//id<aa이 순간에 aa의 앞에 위치한 리스트의 위치
    p=l;
    q=(position)malloc(sizeof(position));
    if(p!=NULL){
        
        while(p!=NULL&&id>=p->element.ID){
            q=p;//id<p가 될 때 while문을 빠져나가므로 그 앞의 값을 저장하는 것.
            p=p->next;
        }return q;
    }else
        return 0;
}
/*
 findp함수
 id의 앞에 위치한 리스트의 주소를 반환.
 delete를 위한 함수.
 */
position findp(int id, list l){
    position p;//주 리스트인 l 대신 p를 만들어 사용
    position address;
    address=find2(id, l); //find2함수를 이용해서 x값이 리스트 안에 있는지 확인
    p=l;
    if(address!=p&&address!=NULL){ //없다면 NULL을 반환하기에 NULL이 아니라면 찾기 시작
        while(p->next!=NULL && p->next->element.ID!=id) //p의 다음 것의 data가 x인지 확인
            p=p->next; //못 찾았으니 그 다음 노드로 다시 지정
        return p; //찾았다면 그 위치를 반환
    }else if(address==NULL)
        return 0;//x가 리스트 안에 없다면 0을 반환
    else//이 때는 address와 p가 일치하는 경우 즉, 찾고자하는 id의 리스트가 첫번째인 것이다. 그러므로 address를 반환한다. delete함수에서 가장 첫번째 것을 지우려할 때를 해결하기 위한 부분
        return address;
}


int isempty(list l){
    return l->next==NULL;
}

void printlist(list l){
    l=l->next; //첫 노드는 값이 주소 값이기에 다음 것부터 시작한다.
    while(1){
        printf("%d %s ", l->element.ID, l->element.name);
        if(l->next==NULL)break; //리스트의 끝이면 중지한다.
        l=l->next;
    }printf("\n");
}
/*insert함수
 우선 리스트가 비었는지 확인한다. 비었다면 입력받은 초기값을 입력한다.
 만약 리스트가 비어있지 않다면, 입력받은 id가 이미 존재하는지 확인한다.
 그것이 a가 하는 일이다. 리스트에 존재하지 않는다면 순서대로 입력하기 위해
 findposition함수를 이용해 id<aa 순간에 aa앞에 위치한 주소를 얻는다.
 그 뒤에 입력받은 정보를 입력한다.
 */
void insert(ElementType x, list l, int id, char name[30]){
    position tmpcell;
    position p;
    tmpcell=(position)malloc(sizeof(struct Node));
    int a,b;
    a=find(id, l);
    b=isempty(l);
    
    if(b==1){
        tmpcell->element.ID=x.ID;
        strcpy(tmpcell->element.name, name);
        tmpcell->next=NULL;
        
        tmpcell->next=l->next;
        l->next=tmpcell;
        
        printf("Insertion Success : %d\n", id);
        printf("Current List ");printlist(l);
        }else if(a==1){
            printf("%d already exist\n", id);
        }else{
            p=findposition(id, l);
            tmpcell->element.ID=x.ID;
            strcpy(tmpcell->element.name, name);
            tmpcell->next=NULL;
        
            tmpcell->next=p->next;
            p->next=tmpcell;
            
            printf("Insertion Success : %d\n", id);
            printf("Current List ");printlist(l);
            }
    
}

void delete(int id, list l){
    position p, tmpcell;
    p=findp(id, l);
    if(p){
        tmpcell=p->next;
        p->next=tmpcell->next;
        free(tmpcell);
    }else
        printf("Deletion failed : element %d is not in the list\n", id);
}

int main(){
    list l;
    l=(list)malloc(sizeof(list));
    l->next=NULL;
    char command;
    int id;
    char name[30];
    ElementType x;
    while(1){
        scanf("%c", &command);
        
        switch (command) {
            case 'i':
                scanf("%d", &x.ID);
                id=x.ID;
                scanf("%[^\n]s", name);
                insert(x, l, id, name);
                break;
            case 'd':
                scanf("%d", &id);
                delete(id, l);
                break;
            case 'p':
                printlist(l);
                return 0;
                
            default:
                break;
        }
    }
}




