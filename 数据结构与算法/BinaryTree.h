#pragma once
#include <iostream>

using namespace std;

//========================================
//�ڵ�
//========================================
typedef struct node
{
	node(int val) :data(val),left(nullptr),right(nullptr){}

	int data;
	node* left;
	node* right;
}node;

//========================================
//�������ṹ
//========================================
class BinaryTree
{
public:
	BinaryTree() :size(0), root(nullptr) {}
	~BinaryTree() { delete root; }
public:
	void	initTree() { init(&root); }//��ʼ��
	int		Size() { return size; }
	void	PreorderTraversal() { PreTraversal(root);cout << endl; }//ǰ��������У�����
	void	InorderTraversal() { InTraversal(root); cout << endl; }//������������У���
	void	PostorderTraversal() { PostTraversal(root); cout << endl; }//������������ң���
	int		maxDepth() { return maxdepth(root); }//������
	int		minDepth() { return mindepth(root); }//��С���
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
//����
//========================================
void BinaryTree::init(node** pos)
{
	//��ȡ���ݣ������0����ʾ������ǰ�����Ĳ���
	int val;
	cin >> val;
	if (val <= 0)
	{
		return;
	}
	//���򣬵ݹ��ʼ��������
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
