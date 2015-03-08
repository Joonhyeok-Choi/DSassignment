#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
/*자료구조 과제1-1
void main(){
	char name[30];
	printf("enter your name:\n");
	gets(name);
	printf("your name is %s", name);
}*/
/*자료구조 과제1-2
void swap(char *a, char *b);
void main(){
	char num[11];
	FILE*file;
	file=fopen("p1_2.txt", "r");
	fgets(num, sizeof(num), file);
	fclose(file);
	swap(&num[0], &num[10]);
	file=fopen("int_output.txt", "w+");
	fputs(num, file);
	fclose(file);
}
void swap(char*a, char*b){
	char tmp;
	tmp=*a;
	*a=*b;
	*b=tmp;
}*/
//자료구조 과제1-4
void main(){
	int n,i;//n은 텍스트 파일에 있는 학생 숫자
	char*inputs;//텍스트 파일의 각 한 줄을 저장할 포인터변수
	char*tok;
	typedef struct student{
		char*name;
		char*id;
		char*major;
	}STU;//구조체 형성
	STU*stuinfo=NULL;
	FILE*fp;
	FILE*file=fopen("p1_4.txt", "r");
	fscanf(file, "%d", &n);//텍스트 파일의 숫자 가쟈오기
	stuinfo=(STU*)malloc(sizeof(STU)*n);//받은 숫자만큼 동적할당
	inputs=(char*)malloc(60);//이름,학번,전공이 있는 각 줄을 보관할 변수 동적할당
	fp=fopen("outputs.txt", "w+");
	for(i=0;i<n+1;i++){//첫번째 줄이 숫자이기에 학생 수보다 한번 더 작동
		fgets(inputs, 60, file);
		if(*inputs=='\n')//첫번째 줄에 줄바꿈 인자가 인식되어 다음 줄부터 작동
			continue;
		else{
			tok=strtok(inputs, " ");//띄어쓰기 기준으로 각각을 나눠서 구조체에 입력
			stuinfo[i-1].name=tok;
			tok=strtok(NULL, " ");
			stuinfo[i-1].id=tok;
			tok=strtok(NULL, " ");
			stuinfo[i-1].major=tok;
			fprintf(fp, "%s %s %s", stuinfo[i-1].name, stuinfo[i-1].id, stuinfo[i-1].major);//파일에 출력
		}			
	}
	fclose(file);fclose(fp);
	free(stuinfo);free(inputs);
}
//자료구조 과제1-3
void main(){
	char *name;
	int n;
	char*tok;
	scanf("%d", &n);fflush(stdin);//이름 숫자 입력
	name=(char*)malloc(31*n);//그 숫자 만큼 동적 할당
	printf("enter %d names:\n", n);
	fgets(name, 31*n, stdin);//이름 입력
	name[strlen(name)-1]='\0';//fgets는 마지막null앞에 '\n'이 들어감으로 바꿔준다.
	printf("the names you entered:\n");
	tok=strtok(name, " ");//strtok로 띄어쓰기에 맞춰 이름 분리
	while(tok!=NULL){//각 이름 차례대로 출력
		printf("%s\n", tok);
		tok=strtok(NULL, " ");
	}
	free(name);//동적할당 해제
}
