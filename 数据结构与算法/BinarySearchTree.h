#pragma once
#include "BinaryTree.h"//复用二叉树的节点定义

//=========================================================
//二叉搜索树
//和二叉树的差别很小，与堆类似，但是要求左子树小于根，右子树大于根
//其次，元素不可重复
//=========================================================

#define DEBUG

//========================================
//结构
//========================================
class BinarySearchTree
{
public:
	BinarySearchTree():size(0),root(nullptr){}
	~BinarySearchTree() { delete root; }
public:
	bool find(int val);//查找某个节点是否已经存在于二叉树
	void insert(int val);//插入
	void init();//初始化
	void remove(int val);//删除
	void PreorderTraversal() { _PreTraversal(root); cout << endl; }//前序遍历
private:
	void _insert(int val, node** root);//插入辅助函数
	void _PreTraversal(node* root);
	void _remove(int val,node **root);
private:
	int size;
	node* root;//根节点
};

bool BinarySearchTree::find(int val)
{
	node* temp = root;
	while (temp != nullptr)
	{
		if (temp->data == val)
		{
			return true;
		}
		else if (temp->data > val)
		{
			temp = temp->left;
		}
		else
		{
			temp = temp->right;
		}
	}
	return false;
}

void BinarySearchTree::insert(int val)
{
	//如果值已经存在，直接返回
	if (find(val))
	{
#ifdef DEBUG
		cout << val << " 已经存在" << endl;
#endif
		return;
	}
	else
	{
		_insert(val, &root);
	}
}

void BinarySearchTree::_insert(int val, node** root)
{
	//依旧要使用二级指针，不然是操作拷贝体
	if (*root == nullptr)
	{
		*root = new node(val);
	}
	else
	{
		if (val > ( (*root)->data ) )
		{
			_insert(val, &((*root)->right));
		}
		else
		{
			_insert(val, &((*root)->left));
		}
	}
}

void BinarySearchTree::_PreTraversal(node* root)
{
	if (root == nullptr)
	{
		return;
	}
	cout << root->data << " ";
	_PreTraversal(root->left);
	_PreTraversal(root->right);
}

void BinarySearchTree::init()
{
	int val;
	cin >> val;
	if (val <= 0)//以此为结束条件
	{
		return;
	}
	else
	{
		insert(val);
		init();
	}
}

//删除是最复杂的操作，分3种情况
//1.删除的是叶子节点，那最简单，直接置空
//2.删除的节点有1个子节点，则删除节点的父节点指向删除节点的子节点，并删除目标节点
//3.删除的节点有2个子节点，那可以找到删除节点左子树中最大值或者右子树中最小值，与删除节点交换，并删除目标节点
void BinarySearchTree::remove(int val)
{
	//如果不存在val，直接返回
	if (!find(val))
	{
#ifdef DEBUG
		cout << "没有找到" << val << endl;
#endif
		return;
	}
	else
	{
		_remove(val, &root);
	}
}

void BinarySearchTree::_remove(int val,node** r)
{
	//如果目标值比当前节点大，那就去右子树
	if ((*r)->data < val)
	{
		_remove(val, &((*r)->right));
	}
	//同理如果目标值较小，那就去左子树
	else if ((*r)->data > val)
	{
		_remove(val,&((*r)->left));
	}
	//此时就找到了我们想要删除的节点了
	else
	{
		////1.目标节点是叶子节点，没有子节点了
		//if ((*r)->left == nullptr && (*r)->right == nullptr)
		//{
		//	//如果目标节点是父节点的左节点
		//	if (parent->left == *r)
		//	{
		//		parent->left = nullptr;
		//	}
		//	//否则就是右节点
		//	else
		//	{
		//		parent->right = nullptr;
		//	}
		//	delete (*r);
		//}
		////2_1.删除的节点只有左子树
		//else if ((*r)->left != nullptr && (*r)->right == nullptr)
		//{
		//	//如果目标节点是父节点的左节点
		//	if (parent->left == *r)
		//	{
		//		parent->left = (*r)->left;
		//	}
		//	//否则就是右节点
		//	else
		//	{
		//		parent->right = (*r)->left;
		//	}
		//	delete (*r);
		//}
		////2_2.删除的节点只有右子树
		//else if ((*r)->left == nullptr && (*r)->right != nullptr)
		//{
		//	//如果目标节点是父节点的左节点
		//	if (parent->left == *r)
		//	{
		//		parent->left = (*r)->right;
		//	}
		//	//否则就是右节点
		//	else
		//	{
		//		parent->right = (*r)->right;
		//	}
		//	delete (*r);
		//}
		////3.最后一种情况就是目标节点同时有左右子树
		//else
		//{
		//	cout << "补充" << endl;
		//}

		//目标节点同时有左右子树
		if ((*r)->left != nullptr && (*r)->right != nullptr)
		{
			node* temp;
			//找到目标节点右子树的最小值
			temp = (*r)->right;
			while (temp->left != nullptr)
			{
				temp = temp->left;
			}
			(*r)->data = temp->data;
			_remove(temp->data, &((*r)->right));
		}
		//只有左子树或者只有右子树
		else
		{
			node* temp = *r;
			if ((*r)->left != nullptr)//只有左子树
			{
				*r = (*r)->left;
			}
			else
			{
				*r = (*r)->right;
			}
			delete temp;
			temp = nullptr;
		}
	}
}

