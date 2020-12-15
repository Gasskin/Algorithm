#include "BinarySearchTree.h"

int main()
{
	BinarySearchTree tree;
	tree.init();
	tree.PreorderTraversal();
	tree.remove(9);
	tree.PreorderTraversal();
	return 0;
}