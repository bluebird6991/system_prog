#include "stdio.h"
#include "string.h"
#include "sys/stat.h"
#include "sys/types.h"

int main(int argc, char const *argv[]){

	FILE *f = fopen(argv[2], "r");

	if(strcmp(argv[1], "-c") == 0){
		if(f != NULL){
			printf("the file exists\n");
		} else {
			f = fopen(argv[2], "w");
			printf("%s created\n", argv[2]);
		}
	} else if (strcmp(argv[1], "-d") == 0){
		printf("vveli -d\n");
		if(f != NULL){
			remove(argv[2]);
			printf("%s deleted\n", argv[2]);
		} else {
			printf("file does not exist\n");
		}
	} else {
		printf("there is no such function\n");
	}

	return 0;
}
