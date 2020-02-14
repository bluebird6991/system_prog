#include "stdio.h"
#include "locale.h"
//#include "Windows.h"
#include "wchar.h"
#include "ctype.h"

int main(int argv, char **argc){
	setlocale(LC_CTYPE, "");
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
	//char a;
	FILE *in = fopen("in.txt", "r");
	FILE *out = fopen("out.txt", "w");
	wchar_t a;
	while((a = fgetwc(in)) != EOF){
		wprintf(L"%d - %lc\n", a, a);
		fwprintf(out, L"%d - %lc\n", a, a);
	}
	//wchar_t str[100];
	//if (fgetws(str, 100, in) != NULL){
	//	fputws(str, out);
	//	for (int i = 0; i <= 10; ++i){
	//		wprintf(L"%lc - %d\n", str[i], str[i]);
	//	}
	//}

	fclose(in);
	fclose(out);
return 0;
}
