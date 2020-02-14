#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "ctype.h"
#include "wchar.h"
#include "locale.h"

#define MAX 33
#define COUNT 10000

int main(int argc, char const *argv[]){
	setlocale(LC_CTYPE, "");
	int i = 0;
	wchar_t c;
	int str[2][MAX];

	for(int i = 0; i < MAX; ++i){
		str[0][i] = i + 1040;
		str[1][i] = 0;
	}

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

	while ((c = fgetwc(f_in)) != EOF){
		if( c >= 1040 && c <= 1103 ){
			if (c >= 1072 && c <= 1103){
				c -= 32;
			}
			str[1][(int)c - 1040]++;
		}
		i++;
	}

	for(int i = 0; i < MAX; ++i){
		if (str[1][i] != 0){
        		wprintf(L"%lc = %d\n", str[0][i], str[1][i]);
			fwprintf(f_out, L"%lc = %d\n", str[0][i], str[1][i]);
        	}
	}

	fclose(f_in);
	fclose(f_out);

return 0;
}

