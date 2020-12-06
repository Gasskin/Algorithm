#include "Heap.h"


int main()
{
	MaxHeap heap;
	heap.init();
	heap.show();
	heap.remove(0);
	heap.show();
	return 0;
}