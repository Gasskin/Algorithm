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

	bool operator==(const self& x) const { return node == x.node; }//比较两个迭代器是否相等，只要比较所指节点是否一样
	bool operator!=(const self& x) const { return node != x.node; }

	reference operator*() const { return (*node).data; }//ref返回的是T&
	pointer operator->() const { return &(operator*()); }
};

//==============================
//List实现
//==============================
class MyList
{

};