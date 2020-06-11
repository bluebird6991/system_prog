#include "stdio.h"

int main(int argc, char **argv){

	printf("argv[1][1] - %c\n", argv[1][1]);

	printf("argv[1][1] - %c\n", *(argv[1] + 1));

	printf("argv[1][1] - %c\n", *(*(argv + 1) + 1));

return 0;
}
