#pragma once
#include<memory>
#include<iostream>
using namespace std;


//==============================
//节点
//==============================
template<class T>
struct __list_node
{
	typedef void*	void_pointer; 
	void_pointer	prev;
	void_pointer	next;
	T				data;
};
//==============================
//list迭代器
//vector中的迭代器其实就是一个普通指针，因为vector本质就是数组，指针的++--已经可以满足其需求
//但是list是双向链表，每个节点都是离散的，不储存在连续空间内，所以其迭代器必须额外设计
//==============================
template<class T>
struct __list_iterator
{
	typedef __list_iterator<T>				self;//指向一个迭代器
	//STL规范所要求的5个相应型别
	typedef bidirectional_iterator_tag		iterator_category; //迭代器类型
	typedef T								value_type;//数据类型
	typedef T*								pointer;
	typedef T&								reference;
	typedef ptrdiff_t						difference_type;//一般用于记录两个迭代器之间的距离

	typedef __list_node<T>*					link_type; //链表的节点	

	link_type								node; //节点指针

	bool		 operator==(const self& x) const { return node == x.node; }//比较两个迭代器是否相等，只要比较所指节点是否一样
	bool		 operator!=(const self& x) const { return node != x.node; }

	reference	 operator*() const { return (*node).data; }//ref返回的是T&，类似int&，直接对应于data数据
	//不是很能理解为什么要重载->，因为使用迭代器时一般也只是用*iter，而且这里返回的似乎就是&((*node).data)，即&data，不明白有何作用
	pointer		 operator->() const { return &(operator*()); }

	//self是一个迭代器，而我们最终返回的就是本身，但我们令node=node->next，作为一次++操作
	self& operator++()//前缀，相当于++i
	{
		node = (link_type)((*node).next);
		return *this;
	}
	//还需要注意的是，前缀++我们返回的就是迭代器本身，后缀++返回的是当前迭代器++前的拷贝，然后当前迭代器也会++
	self operaotr++(int)//后缀，相当于i++(0)
	{
		self temp = *this;
		++* this;
		return tmp;
	}
	self& operator--()
	{
		node = (link_type)((*node).prev);
		return *this;
	}
	self operaotr--(int)
	{
		self temp = *this;
		--* this;
		return tmp;
	}
};

//==============================
//List实现
//==============================
class MyList
{

};