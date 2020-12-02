#pragma once
#include<memory>
using namespace std;

//对于内存配置器的简单封装，个人感觉还是用的是allocator<int>
template<typename T, typename Alloc>
class simple_alloc
{
public:
	static T* allocate(size_t n)
	{
		return 0 == n ? 0 : (T*)Alloc::allocate(n * sizeof(T));
	}
	static T* allocate(void)
	{
		return (T*)Alloc::allocate(sizeof(T));
	}
	static void deallocate(T* p, size_t n)
	{
		if (0 != n) Alloc::deallocate(p, n * sizeof(T));
	}
	static void deallocate(T* p)
	{
		Alloc::deallocate(p, sizeof(T));
	}
};

//=========================
//声明
//=========================
template<typename T,typename Alloc=std::allocator<T>>
class MyVector
{
public:
	//嵌套型别
	typedef T				value_type;//类型
	typedef value_type*		pointer;//指针
	typedef value_type*		iterator;//迭代器，对于vector来说，迭代器和指针基本没差别
	typedef value_type&		reference;//引用
	typedef size_t			size_type;//一般表示大小
	typedef ptrdiff_t		difference_type;//用于储存首位迭代器之间的距离
protected:
	//内存分配器
	//allocator<value_type>	alloc;
	typedef simple_alloc<value_type, Alloc>	data_allocator;
	//迭代器
	iterator				start;//首元素
	iterator				finish;//尾元素
	iterator				end_of_storage;//当前空间的末尾
	//内存分配api
	void					insert_aux(iterator position, const T& x);
	void					deallocate();//释放空间
	void					fill_initialize(size_type n, const T& value);//填充空间
	void					allocate_and_fill(size_type n, const T& x);
public:
	iterator	begin()
	{
		return start;
	}
	iterator	end()
	{
		return finish;
	}
	size_type	size()const
	{
		return size_type(end()-begin());
	}
	size_type	capacity()const
	{
		return size_type(end_of_storage-start);
	}
	bool		empty()
	{
		return begin() == end();
	}
	reference	operator[](size_type n)
	{
		return *(begin() + n);
	}
	reference	front()
	{
		return *begin();
	}
	reference	back()
	{
		return *end();
	}		
	void		push_back(const T& x)
	{
		if (finish != end_of_storage)//当空间未满时
		{
			construct(finish, x);//其实是调用了构造函数，在finish位置构造一个x
			++finish;
		}
		else
		{
			insert_aux(end(), x);
		}
	}
	void		pop_back()
	{
		--finish;
		destroy(finish);
	}
	iterator	erase(iterator position)
	{
		//这是判断position是不是最后一个元素,如果不是
		if (position + 1 != end())
		{
			copy(position + 1, finish, position);
		}
		//如果position就是最后一个元素，那其实就是pop_back
		--finish;
		destroy(finish);
		return position;//我们返回的还是最开始那个迭代器，也因此可能造成迭代器失效的问题
	}
	iterator	erase(iterator first, iterator last)
	{
		iterator i = copy(last, finish, first);
		destroy(i, finish);
		finish = finish - (last - first);
		return first;
	}
	void		resize(size_type new_size, const T& x)
	{
		//reszie是重新分配size，capacity是不变的，除非重新分配的大小超过了capacity
		if (new_size < size())
		{
			erase(begin() + new_size, end());
		}
		else
		{
			insert(end(), new_size - size(), x);
		}
	}
	void		resize(size_type new_size)
	{
		resize(new_size, T());
	}
public:
	MyVector():start(0),finish(0),end_of_storage(0){}
	MyVector(size_type n, const T& value)
	{
		fill_initialize(n, value);
	}
	explicit MyVector(size_type n)
	{
		fill_initialize(n, T());
	}
	~MyVector()
	{
		destroy(start, finish);//注意只要销毁finish个元素
		deallocate();
	}
};


//=========================
//实现
//=========================
template<typename T, typename Alloc>
inline void MyVector<T, Alloc>::insert_aux(iterator position, const T& x)
{
}

template<typename T, typename Alloc>
inline void MyVector<T, Alloc>::deallocate()
{
	if (start)
	{
		data_allocator::deallocate(start, end_of_storage - start);
	}
}

template<typename T, typename Alloc>
inline void MyVector<T, Alloc>::fill_initialize(size_type n, const T& value)
{
	start = allocate_and_fill(n, value);
	finish = start + n;
	end_of_storage = finish;//第一次构造的时候，finish和end是一样大的，不过如果扩容了，可能就不一样了
}

template<typename T, typename Alloc>
inline void MyVector<T, Alloc>::allocate_and_fill(size_type n, const T& x)
{
	iterator result = data_allocator::allocate(n);//分配n个value_type大小的空间
	uninitialized_fill_n(result, n, x);//调用x的构造函数来生成x的复制体，result是起始地址
	return result;
}
