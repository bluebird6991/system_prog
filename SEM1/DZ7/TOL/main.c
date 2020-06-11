#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"
#include "math.h"

int lendth = 0;

int showMenu(int*menuChoosedItemPtr);
int heapSwap(int* str1_ptr, int* str2_ptr);
int heapAtomAsc(int* atomTopHeapPtr, int i, int n);
int heapAtomDesc(int* atomTopHeapPtr, int i, int n);
int exitHeapSort(int* topHeapPtr);
int heapPrint(int* topHeapPtr);
int heapAsc(int* topHeapPtr);
int heapEnter(int* topHeapPtr);
int heapDesc(int* topHeapPtr);


int showMenu(int *menuChoosedItemPtr){
	printf("\n\rChoose action:\n\r");
	printf("1. Enter data\n\r");
	printf("2. Print data\n\r");
	printf("3. Heapsort ascending\n\r");
	printf("4. Heapsort descending\n\r");
    printf("5. Exit\n\n\r>>");
	scanf("%d", menuChoosedItemPtr);
	return 0;
}

int heapSwap(int* str1_ptr, int* str2_ptr){
	int tmp = *str1_ptr;
	*str1_ptr = *str2_ptr;
	*str2_ptr = tmp;
	return 0;
}

int heapAtomAsc(int* atomTopHeapPtr, int i, int n){
	int great = i;
	int left = 2*i + 1;
	int right = 2*i +2; if (left < n && atomTopHeapPtr[left] > atomTopHeapPtr[great]){
                great = left;
        }
        if (right < n && atomTopHeapPtr[right] > atomTopHeapPtr[great]){
                great = right;
        }
        if (great != i){
		heapSwap(&atomTopHeapPtr[i], &atomTopHeapPtr[great]);
		heapAtomAsc(atomTopHeapPtr, great, n);
        }
        return 0;
}

int heapAtomDesc(int* atomTopHeapPtr, int i, int n){
	int least = i;
	int left = 2*i + 1;
	int right = 2*i +2;
	if (left < n && atomTopHeapPtr[left] < atomTopHeapPtr[least]){
                least = left;
        }
        if (right < n && atomTopHeapPtr[right] < atomTopHeapPtr[least]){
		 least = right;
        }
        if (least != i){
		heapSwap(&atomTopHeapPtr[i],  &atomTopHeapPtr[least]);
		heapAtomDesc(atomTopHeapPtr, least, n);
        }
        return 0;
}

int exitHeapSort(int* topHeapPtr){
	free((void*)topHeapPtr);
	printf("Heap killed\n\n\r");
	return 1;
}


int heapPrint(int* topHeapPtr){
	if (lendth == 0){
		printf("Array is empty!!!\n\r");
	} else {
		for (int i = 0; i < lendth; ++i){
			//printf("%d - %d \n", i + 1, topHeapPtr[i]);
			printf("%d ", topHeapPtr[i]);
		}
		printf("\n");
	}
	return 0;
}

int heapAsc(int* topHeapPtr){
	int nHeap;
	nHeap = lendth;
	if (nHeap == 0){
                printf("Array is empty!!!\n\r");
        }else{
                for (int i = nHeap / 2 - 1; i >= 0; i--){
			heapAtomAsc(topHeapPtr, i, nHeap);
		}
		for (int i=nHeap-1; i>=0; i--){
			heapSwap(&(topHeapPtr[0]), &(topHeapPtr[i]));
			heapAtomAsc(topHeapPtr, 0, i);
		}
		printf("Succesfully sorted ascending...\n\r");
		heapPrint(topHeapPtr);

	}
	return 0;
}

int heapEnter(int* topHeapPtr){
	memset(topHeapPtr, 0, 1050);
	lendth = 0;
	int n = 0;
	unsigned int start_time;
	unsigned int stop_time;

	FILE *f_out = fopen("time.csv", "w");

	int count = 0;
	int i = 1;
	while(count <= 1000){
		count = pow(2, i + 1) - 1;
		i++;

		for (int i = 0; i < count; ++i){
			//printf("%d ", -1 + rand() % 100);
			topHeapPtr[lendth++] = rand() % 100;
		}
		printf("count = %d\n", count);
		heapPrint(topHeapPtr);
		printf("\n");
		start_time = clock();
		heapAsc(topHeapPtr);
		stop_time = clock();
		printf("\nstrat time = %d\nstop time = %d\ntotal time = %d\n", start_time, stop_time, stop_time - start_time);
		fprintf(f_out, "%d;%d\n", count, stop_time - start_time);
		printf("\n\n");
		lendth = 0;
	}
	//while(n != -1){
	//	scanf("%d", &n);
	//	topHeapPtr[lendth++] = n;
	//}
	lendth--;
	fclose(f_out);
	return 0;
}

int heapDesc(int* topHeapPtr){
	int nHeap;
	nHeap = lendth;
	if(nHeap == 0){
                printf("Array is empty!!!\n\r");
        }else{
                for (int i = nHeap / 2 - 1; i >= 0; i--){
			heapAtomDesc(topHeapPtr, i, nHeap);
                }
                for (int i=nHeap-1; i>=0; i--){
                        heapSwap(&(topHeapPtr[0]), &(topHeapPtr[i]));
                        heapAtomDesc(topHeapPtr, 0, i);
                }
		printf("Succesfully sorted descending...\n\r");
		heapPrint(topHeapPtr);
        }
	return 0;
}

int main (){
	
	srand(time(NULL));

	int * heapPtr;
	heapPtr = (int*)malloc(1050*sizeof(int));
	int doProgram = 0;
	int choosedParameter = 5;
	while(doProgram == 0){
                showMenu(&choosedParameter);
                printf("\n\r");
                switch(choosedParameter){
                        case 1:{
									doProgram = heapEnter(heapPtr);
									break;
                               }
                        case 2:{
									doProgram = heapPrint(heapPtr);
									break;
                               }
                        case 3:{
									doProgram = heapAsc(heapPtr);
									break;
                               }
                        case 4: {
									doProgram = heapDesc(heapPtr);
									break;
                                }
                        case 5: {
									doProgram = exitHeapSort(heapPtr);
									break;
                                }
                        default:
				printf("Invalid entered menu option. It should be 1-5...\n\r");
                }
        }
        return 0;
}
