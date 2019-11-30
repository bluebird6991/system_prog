#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void push(void);
void pop(void);
void list(void);
void quit(void);
int menu(void);
void MenuView(void);

typedef struct Stack{
	char FIO[64];
	char NumberPhone[13];
	struct Stack *next;
} Stack;

Stack *StackTop = NULL; void(*ListMenu[])(void) = {push, pop, list, quit};

int main(){
	MenuView();
	return 0;
}

int menu(){
	char ch;
	printf("1 - push | 2 - pop | 3 - list | 4 - exit\n");
	do{
		ch = getchar();
	}while(!strchr("1234", ch));
	return ch - 49;
}

void push(void){
	system("clear");
	printf("Push\n");
	//printf("Enter Name: ");
	char *FIO = (char*)malloc(sizeof(char));
	//printf("\nEnter Numper Phone:");
	char *NumberPhone = (char*)malloc(sizeof(char));
	Stack *new = (Stack*)malloc(sizeof(Stack));
	printf("Enter Name: ");
	scanf("%s", new->FIO);
	printf("\nEnter Numper Phone:");
	scanf("%s", new->NumberPhone);
	new->next = StackTop;
	StackTop = new;
}

void pop(void){
	if(StackTop == NULL){
		printf("Stack is empty\n");
	}else{
		Stack *cur = StackTop;
		StackTop = cur->next;
		printf("%s              %s\n", cur->FIO, cur-> NumberPhone); free(cur);
	}
}

void list(void){
	system("clear");
	printf("List\n");
	printf("--------FIO---------|--- Number Phone---\n");
	do{
		pop();
	}while(StackTop != NULL);
}

void quit(void){
	system("clear");
	printf("EXIT\n");
	exit(0);
}

void MenuView(void){
	while(1){
		(*ListMenu[menu()])();
	}
}
