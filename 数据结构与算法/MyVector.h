#include <memory>
#include <iostream>
using namespace std;

#define DEBUG

//对于内存配置器的简单封装，个人感觉还是用的是allocator<int>
//template<typename T, typename Alloc>
//class simple_alloc
//{
//public:
//	static T* allocate(size_t n)
//	{
//		return 0 == n ? 0 : (T*)Alloc::allocate(n * sizeof(T));
//	}
//	static T* allocate(void)
//	{
//		return (T*)Alloc::allocate(sizeof(T));
//	}
//	static void deallocate(T* p, size_t n)
//	{
//		if (0 != n) Alloc::deallocate(p, n * sizeof(T));
//	}
//	static void deallocate(T* p)
//	{
//		Alloc::deallocate(p, sizeof(T));
//	}
//};



/*
	vector[5]  size=5 capcacity=10

	↓start														↓finish														↓end_of_storage
	0			1			2			3			4			5			6			7			8			9			10
	1			2			3			4			5			nullptr		nullptr		nullptr		nullptr		nullptr		×
*/

//=========================
//声明
//=========================
template<typename T>
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
	allocator<value_type>	alloc;
	//typedef simple_alloc<value_type, Alloc>	data_allocator;

	//迭代器
	iterator				start;//首元素
	iterator				finish;//尾元素
	iterator				end_of_storage;//当前空间的末尾
	//内存分配api
	void					deallocate();//deallocate是释放空间，理解为free，而destroy只是调用析构函数
	void					fill_initialize(size_type n, const T& value);//填充空间
	iterator				allocate_and_fill(size_type n, const T& x)
	{
		iterator result = alloc.allocate(n);//分配n个value_type大小的空间
		uninitialized_fill_n(result, n, x);//调用x的构造函数来生成x的复制体，result是起始地址
		return result;
	}
public:
	iterator	begin()const
	{
		return start;
	}
	iterator	end()const
	{
		return finish;
	}
	size_type	size()const
	{
		return (size_type)(end()-begin());
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
#ifdef DEBUG
		cout<<"push_back "<<x<<endl;
#endif
		if (finish != end_of_storage)//当空间未满时
		{
			alloc.construct(finish, x);//其实是调用了构造函数，在finish位置构造一个x
			++finish;
		}
		else
		{
			insert_aux(end(), x);
		}
	}
	void		pop_back()
	{
#ifdef DEBUG
		cout << "pop_back " << *(finish-1) << endl;
#endif
		--finish;
		alloc.destroy(finish);
	}
	iterator	erase(iterator position)
	{
#ifdef DEBUG
		cout<<"erase "<<*position<<endl;
#endif
		//这是判断position是不是最后一个元素,如果不是
		if (position + 1 != end())
		{
			copy(position + 1, finish, position);
		}
		//如果position就是最后一个元素，那其实就是pop_back
		--finish;
		alloc.destroy(finish);
		return position;//我们返回的还是最开始那个迭代器，也因此可能造成迭代器失效的问题
	}
	iterator	erase(iterator first, iterator last)
	{
#ifdef DEBUG
		cout<<"erase ["<<*first<<","<<*(last-1)<<")"<<endl;
#endif
		iterator i = copy(last, finish, first);
		_Destroy_range(i, finish);
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
	void		insert_aux(iterator position, const T& x);//插入一个元素
	void		insert(iterator position, size_type n, const T& x);//插入n个x
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
		_Destroy_range(start, finish);//allocator中没有这个函数
		deallocate();
	}
};


//=========================
//实现
//=========================
template<typename T>
inline void MyVector<T>::deallocate()
{
	if (start)
	{
#ifdef DEBUG
		cout<<"deallocate 释放内存空间"<<endl;
#endif
		alloc.deallocate(start, end_of_storage - start);
	}
}

template<typename T>
inline void MyVector<T>::fill_initialize(size_type n, const T& value)
{
	start = allocate_and_fill(n, value);
	finish = start + n;
	end_of_storage = finish;//第一次构造的时候，finish和end是一样大的，不过如果扩容了，可能就不一样了
}

template<typename T>
inline void MyVector<T>::insert_aux(iterator position, const T& x)
{
#ifdef DEBUG
	cout<<"insert_aux "<<size_type(position-start)<<"->"<<x<<endl;
#endif
	//如果空间还没满
	if (finish != end_of_storage)
	{
#ifdef DEBUG
		cout << "insert_aux 当前空间未满，直接插入" << endl;
#endif 
		//在末端构造一个元素，它的值是vector当前的最后一个元素
		alloc.construct(finish, *(finish - 1));
		++finish;
		T x_copy = x;
		copy_backward(position, finish - 2, finish - 1);//这个只是倒着拷贝，先拷贝finish-2到finish-1，然后finish-3到finish-2，直到position
		*position = x_copy;
	}
	//如果空间满了，那就需要扩容，先分配一个更大的vector，然后把原始数据挪过去
	else
	{
#ifdef DEBUG
		cout << "insert_aux 当前空间已满，重新分配空间" << endl;
#endif 
		const size_type old_size = size();
		const size_type len = (old_size != 0 ? 2 * old_size : 1);//如果原始内存长度是0，那这次分配为1，否则每次扩容为2倍
		
		iterator new_start = alloc.allocate(len);
		iterator new_finish = new_start;

		//这一步是拷贝了[start,position)
		new_finish = uninitialized_copy(start, position, new_start);
		//这一步相当于插入，在finish位置构建一个x元素
		alloc.construct(new_finish, x);
		++new_finish;
		//然后拷贝[position,finish)
		new_finish = uninitialized_copy(position, finish, new_finish);

		_Destroy_range(begin(), end());
		deallocate();
		start = new_start;
		finish = new_finish;
		end_of_storage = new_start + len;
	}

}

template<typename T>
inline void MyVector<T>::insert(iterator position, size_type n, const T& x)
{
	if (n != 0)
	{
#ifdef DEBUG
		cout << "insert " << size_type(position - start) << "->" << n << "个" << x << endl;
#endif
		//如果备用空间的大小，大于n，那就还够用，不用重新分配空间
		if (size_type(end_of_storage - finish) >= n)
		{
#ifdef DEBUG
			cout << "空间足够" << endl;
#endif 
			T x_copy = x;
			//这里计算的是[position,finish)，也就是position之后的元素个数，即需要后移的元素
			const size_type elems_after = finish - position;
			
			iterator old_finish = finish;

			/*
						↓position 插入2个0						↓finish
				1		2		3		4		5		6		_		_		_
				
				可以看到，插入元素数量是2，后移元素数量是5
				我们考虑直接uninitialized_copy(position, finish, position+2);
				但这样拷贝是会出问题的，举例来说
				123456，拷贝一次后就会变成123256，4没了，拷贝就出错了

				因为要插入2个元素，那我们其实也只要后移2位，那我们先把最后2位拷贝到finish，这样拷贝是不会出错的，即

						↓position 插入2个0						↓old_finish		↓finish
				1		2		3		4		5		6		5		6		_

				然后倒叙拷贝剩下几个需要移动的数据

						↓position 插入2个0						↓old_finish		↓finish
				1		2		3		2		3		4		5		6		_
			*/

			//如果插入元素比后移元素少，
			if (elems_after > n)
			{
#ifdef DEBUG
				cout<<"插入元素数 < 后移元素数"<<endl;
#endif
				uninitialized_copy(finish - n, finish, finish);
				finish += n;
				copy_backward(position, old_finish, finish);
				fill(position, position + n, x_copy);

				//如下操作也能满足要求
				//copy_backward(position, finish, finish + n);
				//finish += n;
				//fill(position, position + n, x_copy);
			}
			else
			{
#ifdef DEBUG
				cout << "插入元素数 > 后移元素数" << endl;
#endif
				uninitialized_fill_n(finish, n - elems_after, x_copy);
				finish += n - elems_after;
				uninitialized_copy(position, old_finish, finish);
				finish += elems_after;
				fill(position, old_finish, x_copy);
			}
		}
		else
		{
#ifdef DEBUG
			cout<<"空间大小不足"<<endl;
#endif			
			//新空间为原来的2倍，如果2倍还存不下n个，那新空间就是原来空间+n
			const size_type old_size = size();
			const size_type len = old_size + max(old_size, n);

			iterator new_start = alloc.allocate(len);
			iterator new_finish = new_start;
			//先拷贝[start,position)
			new_finish = uninitialized_copy(start, position, new_start);
			//插入n个x
			new_finish = uninitialized_fill_n(new_finish, n, x);
			//拷贝[position,finish)
			new_finish = uninitialized_copy(position, finish, new_finish);
			
			_Destroy_range(start, finish);
			deallocate();
			start = new_start;
			finish = new_finish;
			end_of_storage = new_start + len;
		}
	}
}



