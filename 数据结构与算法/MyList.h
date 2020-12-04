#pragma once
#include<memory>
#include<iostream>
using namespace std;


//==============================
//�ڵ�
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
//list������
//vector�еĵ�������ʵ����һ����ָͨ�룬��Ϊvector���ʾ������飬ָ���++--�Ѿ���������������
//����list��˫������ÿ���ڵ㶼����ɢ�ģ��������������ռ��ڣ����������������������
//==============================
template<class T>
struct __list_iterator
{
	typedef __list_iterator<T>				self;//ָ��һ��������
	//STL�淶��Ҫ���5����Ӧ�ͱ�
	typedef bidirectional_iterator_tag		iterator_category; //����������
	typedef T								value_type;//��������
	typedef T*								pointer;
	typedef T&								reference;
	typedef ptrdiff_t						difference_type;//һ�����ڼ�¼����������֮��ľ���

	typedef __list_node<T>*					link_type; //����Ľڵ�	

	link_type								node; //�ڵ�ָ��

	bool		 operator==(const self& x) const { return node == x.node; }//�Ƚ������������Ƿ���ȣ�ֻҪ�Ƚ���ָ�ڵ��Ƿ�һ��
	bool		 operator!=(const self& x) const { return node != x.node; }

	reference	 operator*() const { return (*node).data; }//ref���ص���T&������int&��ֱ�Ӷ�Ӧ��data����
	//ע�⣬�������node�е�data�ǻ����������ͣ������ֱ����*iter�����ʣ���������ǵ�dataҲ��һ���ṹ�����ͣ��Ǿ���Ҫ��iter->
	pointer		 operator->() const { return &(operator*()); }

	//self��һ�������������������շ��صľ��Ǳ�����������node=node->next����Ϊһ��++����
	self& operator++()//ǰ׺���൱��++i
	{
		node = (link_type)((*node).next);
		return *this;
	}
	//����Ҫע����ǣ�ǰ׺++���Ƿ��صľ��ǵ�����������׺++���ص��ǵ�ǰ������++ǰ�Ŀ�����Ȼ��ǰ������Ҳ��++
	self operator++(int)//��׺���൱��i++(0)
	{
		self temp = *this;
		++* this;
		return temp;
	}
	self& operator--()
	{
		node = (link_type)((*node).prev);
		return *this;
	}
	self operator--(int)
	{
		self temp = *this;
		--* this;
		return temp;
	}
};

//==============================
//Listʵ��
//==============================
template<class T>
class MyList
{
protected:
	typedef size_t				size_type;//��С����
	typedef T					value_type;//��������
	typedef T* pointer;
	typedef T& reference;

	typedef __list_iterator<T>	iterator;//������
	typedef __list_node<T>		list_node;//����һ���ڵ�
	typedef list_node*			link_type;//ָ��ڵ��ָ��

	link_type					node;//���浱ǰ�ڵ�
	allocator<T>				alloc;//�ڴ������
public:
	iterator	begin() { return (link_type)((*node).next); }
	iterator	end() { return node; }
	bool		empty() const { return node->next == node; }
	size_type	size() const
	{
		size_type result = 0;
		distance(begin(), end(), result);//ȫ�ֺ��������ڼ������
	}
	reference	front() { return *begin(); }//*iter=data
	reference	back() { return *(--end()); }
	//���ǲ��뵽position֮ǰ��
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
protected:
	link_type	get_node() { return alloc.allocate(); }//����һ��node���ڴ棬����ָ��
	void		put_node(link_type p) { alloc.deallocate(p); }//����pָ���node�Ŀռ�
	//����һ��node
	link_type	create_node(const T& x)
	{
		link_type p = get_node();
		alloc.construct(&p->data, x);
		return p;
	}
	//����һ��node
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