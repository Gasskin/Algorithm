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
	void _PreTraversal(node* root);
	void _cal_balance(node*& root);
	int _cal_height(node*& root);
	void _balance(node*& root, _INSERT_POS pos);
	node* _find_father(int val, node*& root);
	void _LL(node*& target);
	void _RR(node*& target);
	void _LR(node*& target);
	void _RL(node*& target);
private:
	node* root;
};

void BalanceBinaryTree::init()
{
	int val;
	cin >> val;
	if (val<0)//��������
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
		PreorderTraversal();
		cout << endl;
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
		//˵����������
		if (root->balance_val < 0)
		{
			//������������������ߣ�˵����RR���µ�
			if (root->right->balance_val < 0)
			{
#ifdef DEBUG
				cout << boost::format("�ڵ�:%1% RRʧ��") % root->data << endl;
#endif
				_LL(root);
			}
			//������RL����
			else
			{
#ifdef DEBUG
				cout << boost::format("�ڵ�:%1% RLʧ��") % root->data << endl;
#endif
				_RL(root);
			}
		}
		//��������������
		else
		{
			//������������������ߣ�˵����RL
			if (root->left->balance_val < 0)
			{
#ifdef DEBUG
				cout << boost::format("�ڵ�:%1% LRʧ��") % root->data << endl;
#endif
				_LR(root);
			}
			//������LL
			else
			{
#ifdef DEBUG
				cout << boost::format("�ڵ�:%1% LLʧ��") % root->data << endl;
#endif
				_RR(root);
			}
		}
	}
}

node* BalanceBinaryTree::_find_father(int val, node*& root)
{
	//���ֱ�����׽ڵ㣬�Ǿͷ���nullptr
	if (root->data == val)
	{
		return nullptr;
	}
	if (root->left != nullptr)
	{
		if (root->left->data == val)
		{
			return root;
		}
	}
	if (root->right != nullptr)
	{
		if (root->right->data == val)
		{
			return root;
		}
	}

	if (val > root->data)
	{
		_find_father(val, root->right);
	}
	else
	{
		_find_father(val, root->left);
	}
}

void BalanceBinaryTree::_PreTraversal(node* root)
{
	if (root == nullptr)
	{
		return;
	}
	cout << root->data << " ";
	_PreTraversal(root->left);
	_PreTraversal(root->right);
}

void BalanceBinaryTree::_LL(node*& target)
{
#ifdef DEBUG 
	cout << boost::format("�ڵ�:%1% ����") % target->data << endl;
#endif
	node* temp = target->right;
	target->right = temp->left;
	temp->left = target;
	
	node* father = _find_father(target->data, root);
	if (father != nullptr)
	{
		father->right = temp;
	}
	else
	{
		this->root = temp;
	}
}

void BalanceBinaryTree::_RR(node*& target)
{
#ifdef DEBUG 
	cout << boost::format("�ڵ�:%1% ����") % target->data << endl;
#endif
	node* temp = target->left;
	target->left = temp->right;
	temp->right = target;

	node* father = _find_father(target->data, root);
	if (father != nullptr)
	{
		father->left = temp;
	}
	else
	{
		this->root = temp;
	}
}

void BalanceBinaryTree::_LR(node*& target)
{
	node* leftChild = target->left;
	node* input = leftChild->right;
	leftChild->right = input->left;
	input->left = leftChild;
	target->left = input;

	target->left = input->right;
	input->left = target;
	node* father = _find_father(target->data, root);
	if (father != nullptr)
	{
		father->left = input;
	}
}

void BalanceBinaryTree::_RL(node*& target)
{
	node* rightChild = target->right;
	node* input = rightChild->left;
	rightChild->left = input->right;
	input->right = rightChild;
	target->right = input;
	
	target->right = input->left;
	input->left = target;
	node* father = _find_father(target->data, root);
	if (father != nullptr)
	{
		father->right = input;
	}
}