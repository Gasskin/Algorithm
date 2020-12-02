#pragma once
#include<memory>
using namespace std;

//�����ڴ��������ļ򵥷�װ�����˸о������õ���allocator<int>
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
//����
//=========================
template<typename T,typename Alloc=std::allocator<T>>
class MyVector
{
public:
	//Ƕ���ͱ�
	typedef T				value_type;//����
	typedef value_type*		pointer;//ָ��
	typedef value_type*		iterator;//������������vector��˵����������ָ�����û���
	typedef value_type&		reference;//����
	typedef size_t			size_type;//һ���ʾ��С
	typedef ptrdiff_t		difference_type;//���ڴ�����λ������֮��ľ���
protected:
	//�ڴ������
	//allocator<value_type>	alloc;
	typedef simple_alloc<value_type, Alloc>	data_allocator;
	//������
	iterator				start;//��Ԫ��
	iterator				finish;//βԪ��
	iterator				end_of_storage;//��ǰ�ռ��ĩβ
	//�ڴ����api
	void					insert_aux(iterator position, const T& x);
	void					deallocate();//�ͷſռ�
	void					fill_initialize(size_type n, const T& value);//���ռ�
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
		if (finish != end_of_storage)//���ռ�δ��ʱ
		{
			construct(finish, x);//��ʵ�ǵ����˹��캯������finishλ�ù���һ��x
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
		//�����ж�position�ǲ������һ��Ԫ��,�������
		if (position + 1 != end())
		{
			copy(position + 1, finish, position);
		}
		//���position�������һ��Ԫ�أ�����ʵ����pop_back
		--finish;
		destroy(finish);
		return position;//���Ƿ��صĻ����ʼ�Ǹ���������Ҳ��˿�����ɵ�����ʧЧ������
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
		//reszie�����·���size��capacity�ǲ���ģ��������·���Ĵ�С������capacity
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
		destroy(start, finish);//ע��ֻҪ����finish��Ԫ��
		deallocate();
	}
};


//=========================
//ʵ��
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
	end_of_storage = finish;//��һ�ι����ʱ��finish��end��һ����ģ�������������ˣ����ܾͲ�һ����
}

template<typename T, typename Alloc>
inline void MyVector<T, Alloc>::allocate_and_fill(size_type n, const T& x)
{
	iterator result = data_allocator::allocate(n);//����n��value_type��С�Ŀռ�
	uninitialized_fill_n(result, n, x);//����x�Ĺ��캯��������x�ĸ����壬result����ʼ��ַ
	return result;
}
