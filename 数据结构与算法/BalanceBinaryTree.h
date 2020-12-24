#pragma once
#include "iostream"
using namespace std;


#define  DEBUG
//=========================================================
//ƽ�������
//�����ϻ��ǲο��������������趨������Ҫ����һ������4����ת
//Ԫ�ز����ظ�
//=========================================================


//=========================================================
//�ڵ�
//���¶���һ�£���Ϊ֮ǰ�������ǵ���ڵ㣬ƽ������˫��ڵ�᷽��ܶ�
//=========================================================
typedef struct node
{
	node(int val) :data(val), left(nullptr), right(nullptr), father(nullptr), balance_val(0) {}

	int data;
	node* left;
	node* right;
	node* father;//���һ�����ڵ�ָ��
	int balance_val;//��ǰ�ڵ����������߶�
}node;


//=========================================================
//�ṹ
//=========================================================
class BalanceBinaryTree
{
public:
	BalanceBinaryTree() :root(nullptr) {}
	~BalanceBinaryTree() { delete root; }
public:
	void init();//��ʼ��
	void insert(int val);//��������
	bool find(int val);//��������
	void PreorderTraversal() { _PreTraversal(root); cout << endl; }//ǰ�����
private:
	void _insert(int val, node*& root);
	void _cal_balance(node*& root);
	int _cal_height(node*& root);
	void _balance(node*& root);
	void _PreTraversal(node* root);
private:
	node* root;
};

void BalanceBinaryTree::init()
{
	int val;
	cin >> val;
	if (val<=0)//��������
	{
		return;
	}
	else
	{
		insert(val);
		init();
	}
}

void BalanceBinaryTree::insert(int val)
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
		_insert(val, root);
	}
}

bool BalanceBinaryTree::find(int val)
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

void BalanceBinaryTree::_insert(int val, node*& root)
{
	if (root == nullptr)
	{
		root = new node(val);
	}
	else
	{
		if (val > (root->data))
		{
			_insert(val, root->right);
			_cal_balance(root);
			_balance(root);
		}
		else
		{
			_insert(val, root->left);
			_cal_balance(root);
			_balance(root);
		}
	}
}

void BalanceBinaryTree::_cal_balance(node*& root)
{
	int left = _cal_height(root->left);
	int right = _cal_height(root->right);
	root->balance_val = left - right;
}

int BalanceBinaryTree::_cal_height(node*& root)
{
	if (root == nullptr)
	{
		return 0;
	}
	int left = 1 + _cal_height(root->left);
	int right = 1 + _cal_height(root->right);
	return max(left, right);
}

void BalanceBinaryTree::_balance(node*& root)
{
	if (root->balance_val > 0)
	{
		cout << "�ڵ�:" << root->data << " ������ " << root->balance_val << endl;
	}
	else if (root->balance_val < 0)
	{
		cout << "�ڵ�:" << root->data << " ������ " << -root->balance_val << endl;
	}
	else
	{
		cout << "�ڵ�:" << root->data <<"����ƽ��"<< endl;
	}
}

void BalanceBinaryTree::_PreTraversal(node* root)
{
	if (root == nullptr)
	{
		return;
	}
#ifdef DEBUG
	cout <<"�ڵ㣺"<<root->data << " ƽ�⣺"<<root->balance_val<< endl;
#else
	cout << root->data << " ";
#endif
	_PreTraversal(root->left);
	_PreTraversal(root->right);
}