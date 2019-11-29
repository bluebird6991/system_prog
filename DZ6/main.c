#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int menu(void);
void MenuView(void);
void push(void);
void pop(void);
void list(void);
void prev(void);
void next(void);
void quit(void);

void(*ListMenu[])(void) = {push, pop, list, prev, next, quit};
typedef struct Ring{
	struct Ring *prev;
	char Data[64];
	struct Ring *next;
} Ring;

Ring *RingListPtr = NULL;
int ListLendthPtr = 0;
int main(int argc, char const *argv[]){
	MenuView();
	return 0;
}

int menu(){
	char ch;
	printf("1 - push | 2 - pop | 3 - list | 4 - prev | 5 - next | 6 - exit\n");
	do{
		ch = getchar();
	}while(!strchr("123456", ch));
	return ch - 49;
}

void MenuView(void){
	while(1){
	(*ListMenu[menu()])();
	}
}

void push(void){
	system("clear");
	printf("Push\n");
	Ring *new = (Ring*)malloc(sizeof(Ring));
	scanf("%s", new->Data);
	if (RingListPtr == NULL){
		new->prev = new;
		new->next = new;
		RingListPtr = new;
	} else {
		new->prev = RingListPtr;
		new->next = RingListPtr->next;
		RingListPtr->next = new;
		(new->next)->prev = new;
		RingListPtr = new;
	}
}

void pop(void){
	if(RingListPtr == NULL){
		printf("List is empty\n");
	}else if(RingListPtr->prev == RingListPtr){
		printf("%s\n", RingListPtr->Data);
		free(RingListPtr);
		RingListPtr = NULL;
	}else{
		Ring *cur = RingListPtr;
		(cur->prev)->next = cur->next;
		(cur->next)->prev = cur->prev;
		printf("%s\n", cur->Data);
		RingListPtr = cur->prev;
		free(cur);
	}
}

void list(void){
	system("clear");
	Ring *startPtr = RingListPtr;
	if(RingListPtr == NULL){
			printf("List is empty\n");
	}else{
		printf("Current: \n");
		do{
			printf("%s\n", RingListPtr->Data);
			ListLendthPtr++; RingListPtr = RingListPtr->next;
		}while(RingListPtr != startPtr);
	}
	printf("List Length: %d\n", ListLendthPtr);
	ListLendthPtr = 0;
}

void prev(void){
	system("clear");
	if(RingListPtr == NULL){
		printf("List is empty\n");
	}else{
		RingListPtr = RingListPtr->prev;
		printf("%s\n", RingListPtr->Data);
	}
}

void next(void){
	system("clear");
	if (RingListPtr == NULL){
	printf("List is empty\n");
	}else{
		RingListPtr = RingListPtr->next;
		printf("%s\n", RingListPtr->Data);
	}
}

void quit(void){
	system("clear");
	printf("EXIT\n");
	exit(0);
}
