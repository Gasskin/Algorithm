#pragma once
#include "iostream"
#include "boost/format.hpp"
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
	node(int val) :data(val), left(nullptr), right(nullptr), balance_val(0) {}
	~node()
	{
#ifdef DEBUG
		cout << "析构节点:" << data << endl;
#endif
		delete left;
		delete right;
	}
	int data;
	node* left;
	node* right;
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
	void remove(int val);//删除数据
	void PreorderTraversal() { _PreTraversal(root); cout << endl; }//前序遍历
private:
	void _insert(int val, node*& root);
	void _remove(int val, node*& root);
	void _PreTraversal(node* root);
	void _cal_balance(node*& root);
	int _cal_height(node*& root);
	void _balance(node*& root);
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
	if (val<0)//结束条件
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
		cout << boost::format("节点:%1% 已经存在") % val << endl;
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

void BalanceBinaryTree::remove(int val)
{
	if (!find(val))
	{
#ifdef DEBUG
        cout << "没有找到" << val << endl;
#endif
		return;
	}
	_remove(val, root);
}

//删除操作参考搜索树，大致思路相同
void BalanceBinaryTree::_remove(int val, node*& root)
{
	if (root->data > val)
	{
		_remove(val, root->left);
		_cal_balance(root);
		_balance(root);
	}
	else if (root->data < val)
	{
		_remove(val, root->right);
		_cal_balance(root);
		_balance(root);
	}
	else
	{
		if (root->left != nullptr && root->right != nullptr)
		{
			node* temp = root->right;
			while (temp->left != nullptr)
			{
				temp = temp->left;
			}
			root->data = temp->data;
			_remove(temp->data, root->right);
		}
		else
		{
			node* temp = root;
			if (root->left != nullptr)
			{
				root = root->left;
			}
			else
			{
				root = root->right;
			}
			delete temp;
		}
	}
}

void BalanceBinaryTree::_insert(int val, node*& root)
{
	if (root == nullptr)
	{
#ifdef DEBUG
		cout << "=========================" << endl;
		cout << boost::format("插入节点:%1%") % val << endl;
		cout << "-------------------------" << endl;
#endif
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
	if (root->balance_val >= -1 && root->balance_val <= 1)
	{
#ifdef DEBUG
		cout << boost::format("节点:%1% 平衡") % root->data << endl;
#endif
		return;
	}
	else
	{
		//说明右子树高
		if (root->balance_val < 0)
		{
			//如果右子树的右子树高，说明是RR导致的
			if (root->right->balance_val < 0)
			{
#ifdef DEBUG
				cout << boost::format("节点:%1% RR失衡") % root->data << endl;
#endif
				_LL(root);
			}
			//否则是RL导致
			else
			{
#ifdef DEBUG
				cout << boost::format("节点:%1% RL失衡") % root->data << endl;
#endif
				_RL(root);
			}
		}
		//否则是左子树高
		else
		{
			//如果左子树的右子树高，说明是RL
			if (root->left->balance_val < 0)
			{
#ifdef DEBUG
				cout << boost::format("节点:%1% LR失衡") % root->data << endl;
#endif
				_LR(root);
			}
			//否则是LL
			else
			{
#ifdef DEBUG
				cout << boost::format("节点:%1% LL失衡") % root->data << endl;
#endif
				_RR(root);
			}
		}
	}
}

node* BalanceBinaryTree::_find_father(int val, node*& root)
{
	//如果直接是首节点，那就返回nullptr
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
	cout << boost::format("节点:%1% 左旋") % target->data << endl;
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
	cout << boost::format("节点:%1% 右旋") % target->data << endl;
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