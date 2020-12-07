#include "Heap.h"
#include "Sorts.h"

int main()
{
	int arr[] = { 3,2,1,5,7,8,4,9,6 };

	show(arr,9);
	MergeSort(arr,0,8);
	show(arr,9);

	return 0;
}

