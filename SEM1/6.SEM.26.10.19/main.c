#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"

#define MAX 26
#define COUNT 10000

void Open_File(char const *file_in, char const *file_out){
	FILE *f_in	= fopen(file_in, "r");
	FILE *f_out	= fopen(file_out, "w");

	printf("function open file\n");

	if(f_in == NULL){
		perror("error 1");
		//return 1;
	} else {
		printf("file %s open\n", file_in);
	}
	if(f_out == NULL){
		perror("error 2");
		//return 2;
	} else {
		printf("file %s open\n", file_out);
	}
}

void Close_File(char *file_in, char *file_out){
	//fclose(file_in);
	//fclose(file_out);
	printf("file %d close", file_in);
	printf("file %d close", file_out);
}

int main(int argc, char const *argv[]){

	int i = 0;
	char c;
	int str[MAX][COUNT];

	for(int i = 0; i < MAX; ++i){
		str[0][i] = i + 65;
		str[1][i] = 0;
	}

	//Open_File(argv[1], argv[2]);
	//Close_File(argv[1], argv[2]);
	FILE *f_in = fopen(argv[1], "r");
	FILE *f_out = fopen(argv[2], "w");

	if(f_in == NULL){
	perror("error 1");
	return 1;

	}

	if(f_out == NULL){
		perror("error 2");
		return 2;
	}
	while ((c = toupper(fgetc(f_in))) != EOF){ 
		if(c >= 65 && c <= 90){
			str[1][(int)c]++;
		}
		i++;
	}

	for(int i = 0; i < MAX; ++i){
		if (str[1][i + 65] != 0){
        		printf("%c = %d\n", str[0][i], str[1][i + 65]);
			fprintf(f_out, "%c = %d\n", str[0][i], str[1][i + 65]);
        	}
	}

	fclose(f_in);
	fclose(f_out);

return 0;
}

