#pragma once
#include <iostream>

using namespace std;

//========================================
//节点
//========================================
typedef struct node
{
	node(int val) :data(val),left(nullptr),right(nullptr){}

	int data;
	node* left;
	node* right;
}node;

//========================================
//二叉树结构
//========================================
class BinaryTree
{
public:
	BinaryTree() :size(0), root(nullptr) {}
	~BinaryTree() { delete root; }
public:
	void	initTree() { init(&root); }//初始化
	int		Size() { return size; }
	void	PreorderTraversal() { PreTraversal(root);cout << endl; }//前序遍历，中，左，右
	void	InorderTraversal() { InTraversal(root); cout << endl; }//中序遍历，左，中，右
	void	PostorderTraversal() { PostTraversal(root); cout << endl; }//后序遍历，左，右，中
	int		maxDepth() { return maxdepth(root); }//最大深度
	int		minDepth() { return mindepth(root); }//最小深度
private:
	void init(node** pos);
	void PreTraversal(node* root);
	void InTraversal(node* root);
	void PostTraversal(node* root);
	int maxdepth(node* root);
	int mindepth(node* root);
private:
	int size;
	node* root;
};
//========================================
//方法
//========================================
void BinaryTree::init(node** pos)
{
	//读取数据，如果≤0，表示结束当前子树的插入
	int val;
	cin >> val;
	if (val <= 0)
	{
		return;
	}
	//否则，递归初始化二叉树
	else
	{
		(*pos) = new node(val);
		size++;
		init(&( (*pos)->left) );
		init(&( (*pos)->right) );
	}
}

void BinaryTree::PreTraversal(node* root)
{
	if (root == nullptr)
	{
		return;
	}
	cout << root->data << " ";
	PreTraversal(root->left);
	PreTraversal(root->right);
}

void BinaryTree::InTraversal(node* root)
{
	if (root == nullptr)
	{
		return;
	}
	InTraversal(root->left);
	cout << root->data << " ";
	InTraversal(root->right);
}

void BinaryTree::PostTraversal(node* root)
{
	if (root == nullptr)
	{
		return;
	}
	PostTraversal(root->left);
	PostTraversal(root->right);
	cout << root->data << " ";
}

int BinaryTree::maxdepth(node* root)
{
	if (root == nullptr)
	{
		return 0;
	}
	int left = 1 + maxdepth(root->left);
	int right = 1 + maxdepth(root->right);
	return max(left, right);
}

int BinaryTree::mindepth(node* root)
{
	if (root == nullptr)
	{
		return 0;
	}
	int left = 1 + maxdepth(root->left);
	int right = 1 + maxdepth(root->right);
	return min(left, right);
}
