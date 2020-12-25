#pragma once
#include "iostream"
#include "boost/format.hpp"
using namespace std;


#define  DEBUG
//=========================================================
//ƽ�������
//�����ϻ��ǲο��������������趨������Ҫ����һ������4����ת
//Ԫ�ز����ظ�
//=========================================================

//��һ��static��������¼��ǰ�ڵ������Ǹ��ڵ����߻����ұߣ������ж�ʧ�����
//�����root�Ļ����������д��Ĭ����0
typedef int _INSERT_POS;
const int _LEFT = 0;
const int _RIGHT = 1;
static int _CUR_POS = 0;

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
	void _balance(node*& root, _INSERT_POS pos);
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
		_CUR_POS = 0;
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
		cout << boost::format("�ڵ�:%1% �Ѿ�����") % val << endl;
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
#ifdef DEBUG
		cout << "=========================" << endl;
		cout << boost::format("����ڵ�:%1%") % val << endl;
		cout << "-------------------------" << endl;
#endif
		root = new node(val);
	}
	else
	{
		if (val > (root->data))
		{
			_CUR_POS = _RIGHT;
			_insert(val, root->right);
			_cal_balance(root);
			_balance(root, _CUR_POS);
		}
		else
		{
			_CUR_POS = _LEFT;
			_insert(val, root->left);
			_cal_balance(root);
			_balance(root, _CUR_POS);
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

void BalanceBinaryTree::_balance(node*& root, _INSERT_POS pos)
{
	if (root->balance_val >= -1 && root->balance_val <= 1)
	{
#ifdef DEBUG
		cout << boost::format("�ڵ�:%1% ƽ��") % root->data << endl;
#endif
		return;
	}
	else
	{
		if (root->balance_val < 0)
		{
			//�����ǰ�ڵ������Ǹ��ڵ���Ҳ࣬�Ǿ���RR
			if (pos)
			{
#ifdef DEBUG
				cout << boost::format("�ڵ�:%1% RRʧ��") % root->data << endl;
#endif
				node* temp = root->right;
				root->right = temp->left;
				temp->left = root;
				this->root = temp;
			}
			//������RL
			else
			{
#ifdef DEBUG
				cout << boost::format("�ڵ�:%1% RLʧ��") % root->data << endl;
#endif
			}
		}
		else
		{
			//�����ǰ�ڵ������Ǹ��ڵ���Ҳ࣬�Ǿ���LR
			if (pos)
			{
#ifdef DEBUG
				cout << boost::format("�ڵ�:%1% LRʧ��") % root->data << endl;
#endif
			}
			//������LL
			else
			{
#ifdef DEBUG
				cout << boost::format("�ڵ�:%1% LLʧ��") % root->data << endl;
#endif
				node* temp = root->left;
				root->left = temp->right;
				temp->right = root;
				this->root = temp;
			}
		}
	}
}

void BalanceBinaryTree::_PreTraversal(node* root)
{
	if (root == nullptr)
	{
		return;
	}
#ifdef DEBUG
	cout << boost::format("�ڵ�:%1% ƽ��ֵ:%2%") % root->data % root->balance_val << endl;
#else
	cout << root->data << " ";
#endif
	_PreTraversal(root->left);
	_PreTraversal(root->right);
}