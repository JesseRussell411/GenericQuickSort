// author: Jesse Russell

// This code demonstrates my proficiency in algorithms, structs, dynamic memory, function pointers, and generic code.
// I have also tried to make this code as compact as reasonably possible.
// Everything logic-oriented is allocated on the stack; everything data-oriented is allocated on the heap.


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Generic swap.
 */
void swap(void *a, void *b, const size_t s){
	unsigned char temp[s];

	memcpy(temp, a,    s);
	memcpy(a,    b,    s);
	memcpy(b,    temp, s);
}

// void* vs unsigned char*: void pointer can point to anything, but only unsigned char* safely allows arithmetic.

void quicksort_inner(unsigned char *start, unsigned char *end, const size_t s, int (*compare)(void*, void*)){
	// recursion break:
	if (end - start <= s) return;

	unsigned char *check = start;
	unsigned char *pivot = end - s;

	// I'm just picking the last item for the pivot. Should work fine with random input. Of course this will be O(n^2) with already sorted arrays, but it should be fine for a demonstration.

	// Main loop (partition):
	//	 move anything larger than pivot to the right of pivot.
	while(check < pivot){
		while ((*compare)(check, pivot) > 0) {
			swap(check, pivot - s, s);
			swap(pivot, pivot - s, s);
			pivot -= s;
		}
		check += s;
	}

	// Recursion call:
	// sizecheck to maximize tail recursion.
	if (pivot - start < end - pivot){
		quicksort_inner(start, pivot, s, compare);
		quicksort_inner(pivot, end,   s, compare);
	} else {
		quicksort_inner(pivot, end,   s, compare);
		quicksort_inner(start, pivot, s, compare);
	}
}

/**
 * In-Place generic quicksort
 */
void quicksort(void *arr, const size_t l, const size_t s, int (*compare)(void*, void*)){
	quicksort_inner((unsigned char*) arr, (unsigned char *) arr + l * s, s, compare);
}



/**
 * int-compare
 */
int icmp(void *a, void *b){
	return *((int*)a) - *((int*)b);
}


/**
 * float-compare
 */
int fcmp(void *a, void *b){
	if      (*((float*)a) == *((float*)b)) return 0;
	else if (*((float*)a) >  *((float*)b)) return 1;

	else return -1;
}


/**
 * example struct
 */
typedef struct {
	int id;
	int value;
} foo;


/**
 * foo-compare
 */
int fooCmp(void *a, void *b){
	return icmp(&(**((foo**)a)).value, &(**((foo**)b)).value);
}

int main(){
	// | Parameters |
	size_t count = 20;


	// o--------------o
	// | sorting ints |
	// o--------------o


	// Allocate nums:
	int *nums = (int*)malloc(sizeof(int) * count);


	// Fill nums with random numbers:
	for(size_t i = 0; i < count; i++)
		nums[i] =  rand() % 100;


	// Print unsorted:
	for(size_t i = 0; i < count; i++)
		printf("%d\n", nums[i]);
	printf("\n");


	// Sort:
	printf("Sorting...\n");
	quicksort(nums, count, sizeof(int), *icmp);; // <---------
	printf("done.\n");


	// Print sorted:
	for(size_t i = 0; i < count; i++)
		printf("%d\n", nums[i]);
	printf("\n");

	// De-Allocate nums:
	free(nums);




	// o----------------o
	// | sorting floats |
	// o----------------o


	// Allocate floats
	float *floats = (float*)malloc(sizeof(float) * count);


	// Fill floats with random numbers:
	for(size_t i = 0; i < count; i++)
		floats[i] = (float)rand() / (float)RAND_MAX * 10;


	//print unsorted:
	for(size_t i = 0; i < count; i++)
		printf("%f\n", floats[i]);
	printf("\n");


	//sort:
	printf("Sorting...\n");
	quicksort(nums, count, sizeof(float), *fcmp); // <---------
	printf("done.\n");


	//print sorted:
	for(size_t i = 0; i < count; i++)
		printf("%f\n", floats[i]);
	printf("\n");


	// De-Allocate floats.
	free(floats);



	// o-----------------o
	// | sorting structs |
	// o-----------------o

	// Allocate foos.
	foo **foos = (foo**)malloc(sizeof(foo*) * count);


	// fill foos with random foos:
	for(size_t i = 0; i < count; i++){
		foos[i] = (foo*)malloc(sizeof(foo*));
		*foos[i] = (foo) { .id = i, .value = rand() % 10000 };
	}

	// print unsorted:
	for(size_t i = 0; i < count; i++)
		printf("%2d: %d\n", foos[i]->id, foos[i]->value);
	printf("\n");

	// sort:
	printf("Sorting...\n");
	quicksort(foos, count, sizeof(foo), *fooCmp); // <----------
	printf("done.\n");

	// print sorted:
	for(size_t i = 0; i < count; i++)
		printf("%2d: %d\n", foos[i]->id, foos[i]->value);
	printf("\n");

	// De_Allocate foos:
	for(int i = 0; i < count; i++)
		free(foos[i]);

	free(foos);
}

