#pragma once
#include "iostream"
using namespace std;


#define  DEBUG
//=========================================================
//平衡二叉树
//大体上还是参考二叉搜索树的设定，但需要更进一步考虑4种旋转
//元素不可重复
//=========================================================


//=========================================================
//节点
//重新定义一下，因为之前的树都是单向节点，平衡树用双向节点会方便很多
//=========================================================
typedef struct node
{
	node(int val) :data(val), left(nullptr), right(nullptr), father(nullptr), balance_val(0) {}

	int data;
	node* left;
	node* right;
	node* father;//多加一个父节点指针
	int balance_val;//当前节点的最大子树高度
}node;


//=========================================================
//结构
//=========================================================
class BalanceBinaryTree
{
public:
	BalanceBinaryTree() :root(nullptr) {}
	~BalanceBinaryTree() { delete root; }
public:
	void init();//初始化
	void insert(int val);//插入数据
	bool find(int val);//查找数据
	void PreorderTraversal() { _PreTraversal(root); cout << endl; }//前序遍历
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
	if (val<=0)//结束条件
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
		cout << "节点:" << root->data << " 左树高 " << root->balance_val << endl;
	}
	else if (root->balance_val < 0)
	{
		cout << "节点:" << root->data << " 右树高 " << -root->balance_val << endl;
	}
	else
	{
		cout << "节点:" << root->data <<"左右平衡"<< endl;
	}
}

void BalanceBinaryTree::_PreTraversal(node* root)
{
	if (root == nullptr)
	{
		return;
	}
#ifdef DEBUG
	cout <<"节点："<<root->data << " 平衡："<<root->balance_val<< endl;
#else
	cout << root->data << " ";
#endif
	_PreTraversal(root->left);
	_PreTraversal(root->right);
}