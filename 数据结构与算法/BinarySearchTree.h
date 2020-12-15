#pragma once
#include "BinaryTree.h"//���ö������Ľڵ㶨��

//=========================================================
//����������
//�Ͷ������Ĳ���С��������ƣ�����Ҫ��������С�ڸ������������ڸ�
//��Σ�Ԫ�ز����ظ�
//=========================================================

#define DEBUG

//========================================
//�ṹ
//========================================
class BinarySearchTree
{
public:
	BinarySearchTree():size(0),root(nullptr){}
	~BinarySearchTree() { delete root; }
public:
	bool find(int val);//����ĳ���ڵ��Ƿ��Ѿ������ڶ�����
	void insert(int val);//����
	void init();//��ʼ��
	void remove(int val);//ɾ��
	void PreorderTraversal() { _PreTraversal(root); cout << endl; }//ǰ�����
private:
	void _insert(int val, node** root);//���븨������
	void _PreTraversal(node* root);
	void _remove(int val,node **root);
private:
	int size;
	node* root;//���ڵ�
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
	//���ֵ�Ѿ����ڣ�ֱ�ӷ���
	if (find(val))
	{
#ifdef DEBUG
		cout << val << " �Ѿ�����" << endl;
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
	//����Ҫʹ�ö���ָ�룬��Ȼ�ǲ���������
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
	if (val <= 0)//�Դ�Ϊ��������
	{
		return;
	}
	else
	{
		insert(val);
		init();
	}
}

//ɾ������ӵĲ�������3�����
//1.ɾ������Ҷ�ӽڵ㣬����򵥣�ֱ���ÿ�
//2.ɾ���Ľڵ���1���ӽڵ㣬��ɾ���ڵ�ĸ��ڵ�ָ��ɾ���ڵ���ӽڵ㣬��ɾ��Ŀ��ڵ�
//3.ɾ���Ľڵ���2���ӽڵ㣬�ǿ����ҵ�ɾ���ڵ������������ֵ��������������Сֵ����ɾ���ڵ㽻������ɾ��Ŀ��ڵ�
void BinarySearchTree::remove(int val)
{
	//���������val��ֱ�ӷ���
	if (!find(val))
	{
#ifdef DEBUG
		cout << "û���ҵ�" << val << endl;
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
	//���Ŀ��ֵ�ȵ�ǰ�ڵ���Ǿ�ȥ������
	if ((*r)->data < val)
	{
		_remove(val, &((*r)->right));
	}
	//ͬ�����Ŀ��ֵ��С���Ǿ�ȥ������
	else if ((*r)->data > val)
	{
		_remove(val,&((*r)->left));
	}
	//��ʱ���ҵ���������Ҫɾ���Ľڵ���
	else
	{
		////1.Ŀ��ڵ���Ҷ�ӽڵ㣬û���ӽڵ���
		//if ((*r)->left == nullptr && (*r)->right == nullptr)
		//{
		//	//���Ŀ��ڵ��Ǹ��ڵ����ڵ�
		//	if (parent->left == *r)
		//	{
		//		parent->left = nullptr;
		//	}
		//	//��������ҽڵ�
		//	else
		//	{
		//		parent->right = nullptr;
		//	}
		//	delete (*r);
		//}
		////2_1.ɾ���Ľڵ�ֻ��������
		//else if ((*r)->left != nullptr && (*r)->right == nullptr)
		//{
		//	//���Ŀ��ڵ��Ǹ��ڵ����ڵ�
		//	if (parent->left == *r)
		//	{
		//		parent->left = (*r)->left;
		//	}
		//	//��������ҽڵ�
		//	else
		//	{
		//		parent->right = (*r)->left;
		//	}
		//	delete (*r);
		//}
		////2_2.ɾ���Ľڵ�ֻ��������
		//else if ((*r)->left == nullptr && (*r)->right != nullptr)
		//{
		//	//���Ŀ��ڵ��Ǹ��ڵ����ڵ�
		//	if (parent->left == *r)
		//	{
		//		parent->left = (*r)->right;
		//	}
		//	//��������ҽڵ�
		//	else
		//	{
		//		parent->right = (*r)->right;
		//	}
		//	delete (*r);
		//}
		////3.���һ���������Ŀ��ڵ�ͬʱ����������
		//else
		//{
		//	cout << "����" << endl;
		//}

		//Ŀ��ڵ�ͬʱ����������
		if ((*r)->left != nullptr && (*r)->right != nullptr)
		{
			node* temp;
			//�ҵ�Ŀ��ڵ�����������Сֵ
			temp = (*r)->right;
			while (temp->left != nullptr)
			{
				temp = temp->left;
			}
			(*r)->data = temp->data;
			_remove(temp->data, &((*r)->right));
		}
		//ֻ������������ֻ��������
		else
		{
			node* temp = *r;
			if ((*r)->left != nullptr)//ֻ��������
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

