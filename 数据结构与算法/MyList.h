#pragma once
#include<memory>
#include<iostream>
using namespace std;


//==============================
//节点
//==============================
template<class T>
struct _list_node
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
struct _list_iterator
{
	typedef _list_iterator<T>				self;//指向一个迭代器
	//STL规范所要求的5个相应型别
	typedef bidirectional_iterator_tag		iterator_category; //迭代器类型
	typedef T								value_type;//数据类型
	typedef T*								pointer;
	typedef T&								reference;
	typedef ptrdiff_t						difference_type;//一般用于记录两个迭代器之间的距离

	typedef _list_node<T>*					link_type; //链表的节点	

	link_type								node; //节点指针

	_list_iterator(link_type x) :node(x) {};
	_list_iterator() {}
	_list_iterator(const iterator& x) :node(x.node) {}

	bool		 operator==(const self& x) const { return node == x.node; }//比较两个迭代器是否相等，只要比较所指节点是否一样
	bool		 operator!=(const self& x) const { return node != x.node; }

	reference	 operator*() const { return (*node).data; }//ref返回的是T&，类似int&，直接对应于data数据
	//注意，如果我们node中的data是基本数据类型，则可以直接用*iter来访问，但如果我们的data也是一个结构体类型，那就需要用iter->
	pointer		 operator->() const { return &(operator*()); }

	//self是一个迭代器，而我们最终返回的就是本身，但我们令node=node->next，作为一次++操作
	self&		operator++()//前缀，相当于++i
	{
		node = (link_type)((*node).next);
		return *this;
	}
	//还需要注意的是，前缀++我们返回的就是迭代器本身，后缀++返回的是当前迭代器++前的拷贝，然后当前迭代器也会++
	self		operator++(int)//后缀，相当于i++(0)
	{
		self temp = *this;
		++* this;
		return temp;
	}
	self&		operator--()
	{
		node = (link_type)((*node).prev);
		return *this;
	}
	self		operator--(int)
	{
		self temp = *this;
		--* this;
		return temp;
	}
};

//==============================
//List实现
//==============================
template<class T>
class MyList
{
protected:
	typedef size_t				size_type;//大小类型
	typedef T					value_type;//数据类型
	typedef T* pointer;
	typedef T& reference;

	typedef _list_iterator<T>	iterator;//迭代器
	typedef _list_node<T>		_list_node;//保存一个节点
	typedef _list_node*			link_type;//指向节点的指针

	link_type					node;//保存当前节点
	allocator<_list_node>		alloc;//内存分配器
public:
	iterator	begin() { return (link_type)((*node).next); }
	iterator	end() { return node; }
	bool		empty() const { return node->next == node; }
	size_type	size() const
	{
		size_type result = 0;
		distance(begin(), end(), result);//全局函数，用于计算距离
	}
	reference	front() { return *begin(); }//*iter=data
	reference	back() { return *(--end()); }
	//这是插入到position之前的
	iterator	insert(iterator position, const T& x)
	{
		link_type tmp = create_node(x);
		tmp->next = position.node;
		tmp->prev = position.node->prev;
		(link_type(position.node->prev))->next = tmp;
		position.node->prev = tmp;
		return tmp;
	}
	void		push_back(const T& x) { insert(end(), x); }
	void		push_front(const T& x) { insert(begin(), x); }
	iterator	erase(iterator position)
	{
		link_type next_node = link_type(position.node->next);
		link_type prev_node = link_type(position.node->prev);
		prev_node->next = next_node;
		next_node->prev = prev_node;
		destroy_node(position.node);
		return iterator(next_node);
	}
	void		pop_front() { erase(begin()); }
	void		pop_back()
	{
		iterator tmp = end();
		erase(--tmp);
	}
	void		clear();
	void		remove(const T& value);
protected:
	link_type	get_node() { return alloc.allocate(1); }//分配一个node的内存，返回指针
	void		put_node(link_type p) { alloc.deallocate(p); }//销毁p指向的node的空间
	//构造一个node
	link_type	create_node(const T& x)
	{
		link_type p = get_node();
		alloc.construct(&p->data, x);
		return p;
	}
	//析构一个node
	void		destroy_node(link_type p)
	{
		alloc.destroy(&p->data);
		put_node(p);
	}
protected:
	void		empty_initialize()
	{
		node = get_node();
		node->prev = node;
		node->next = node;
	}

public:
	MyList() { empty_initialize(); }
};

template<class T>
inline void MyList<T>::clear()
{
	link_type cur = (link_type)node->next;//begin()
	while (cur != node)
	{
		link_type temp = cur;
		cur = (link_type)cur->next;
		destroy_node(temp);
	}
	node->next = node;
	node->prev = node;
}

template<class T>
inline void MyList<T>::remove(const T& value)
{
	iterator first = begin();
	iterator last = end();
	while (first != last)
	{
		iterator next = first;
		++next;
		if (*first == value)
		{
			erase(first);
		}
		first = next;
	}
}
