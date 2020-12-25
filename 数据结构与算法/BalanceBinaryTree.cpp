#include "BalanceBinaryTree.h"

int main()
{
	BalanceBinaryTree tree;
	tree.init();
	tree.PreorderTraversal();
	tree.insert(1);
	tree.PreorderTraversal();
	return 0;
}