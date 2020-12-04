#include "MyList.h"
#include <iostream>

struct test
{
	test(int x)
	{ 
		cout << "默认构造" << endl;
	}
	test(const test& t)
	{
		cout << "拷贝构造" << endl;
	}
};

test fun1(int a)
{
	return a;
}

test fun2(test a)
{
	return a;
}

int main()
{
	fun1(1);
	cout << "=======" << endl;
	test t(1);
	cout << "=======" << endl;
	fun2(t);

	/*MyList<int> list;
	for (int i = 0; i < 5; i++)
	{
		list.push_back(i);
	}

	for (auto iter = list.begin(); iter != list.end(); iter++)
	{
		cout << *iter << endl;
	}*/
	
	return 0;
}