#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
/*�ڷᱸ�� ����1-1
void main(){
	char name[30];
	printf("enter your name:\n");
	gets(name);
	printf("your name is %s", name);
}*/
/*�ڷᱸ�� ����1-2
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
//�ڷᱸ�� ����1-4
void main(){
	int n,i;//n�� �ؽ�Ʈ ���Ͽ� �ִ� �л� ����
	char*inputs;//�ؽ�Ʈ ������ �� �� ���� ������ �����ͺ���
	char*tok;
	typedef struct student{
		char*name;
		char*id;
		char*major;
	}STU;//����ü ����
	STU*stuinfo=NULL;
	FILE*fp;
	FILE*file=fopen("p1_4.txt", "r");
	fscanf(file, "%d", &n);//�ؽ�Ʈ ������ ���� �������
	stuinfo=(STU*)malloc(sizeof(STU)*n);//���� ���ڸ�ŭ �����Ҵ�
	inputs=(char*)malloc(60);//�̸�,�й�,������ �ִ� �� ���� ������ ���� �����Ҵ�
	fp=fopen("outputs.txt", "w+");
	for(i=0;i<n+1;i++){//ù��° ���� �����̱⿡ �л� ������ �ѹ� �� �۵�
		fgets(inputs, 60, file);
		if(*inputs=='\n')//ù��° �ٿ� �ٹٲ� ���ڰ� �νĵǾ� ���� �ٺ��� �۵�
			continue;
		else{
			tok=strtok(inputs, " ");//���� �������� ������ ������ ����ü�� �Է�
			stuinfo[i-1].name=tok;
			tok=strtok(NULL, " ");
			stuinfo[i-1].id=tok;
			tok=strtok(NULL, " ");
			stuinfo[i-1].major=tok;
			fprintf(fp, "%s %s %s", stuinfo[i-1].name, stuinfo[i-1].id, stuinfo[i-1].major);//���Ͽ� ���
		}			
	}
	fclose(file);fclose(fp);
	free(stuinfo);free(inputs);
}
//�ڷᱸ�� ����1-3
void main(){
	char *name;
	int n;
	char*tok;
	scanf("%d", &n);fflush(stdin);//�̸� ���� �Է�
	name=(char*)malloc(31*n);//�� ���� ��ŭ ���� �Ҵ�
	printf("enter %d names:\n", n);
	fgets(name, 31*n, stdin);//�̸� �Է�
	name[strlen(name)-1]='\0';//fgets�� ������null�տ� '\n'�� ������ �ٲ��ش�.
	printf("the names you entered:\n");
	tok=strtok(name, " ");//strtok�� ���⿡ ���� �̸� �и�
	while(tok!=NULL){//�� �̸� ���ʴ�� ���
		printf("%s\n", tok);
		tok=strtok(NULL, " ");
	}
	free(name);//�����Ҵ� ����
}
