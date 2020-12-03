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
	//���Ǻ������ΪʲôҪ����->����Ϊʹ�õ�����ʱһ��Ҳֻ����*iter���������ﷵ�ص��ƺ�����&((*node).data)����&data���������к�����
	pointer		 operator->() const { return &(operator*()); }

	//self��һ�������������������շ��صľ��Ǳ�����������node=node->next����Ϊһ��++����
	self& operator++()//ǰ׺���൱��++i
	{
		node = (link_type)((*node).next);
		return *this;
	}
	//����Ҫע����ǣ�ǰ׺++���Ƿ��صľ��ǵ�����������׺++���ص��ǵ�ǰ������++ǰ�Ŀ�����Ȼ��ǰ������Ҳ��++
	self operaotr++(int)//��׺���൱��i++(0)
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
//Listʵ��
//==============================
class MyList
{

};