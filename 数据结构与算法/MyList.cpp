#include "MyList.h"
#include <iostream>

struct test
{
	test(int& x) :t(x) { cout << "¹¹Ôì" << endl; }
	int t;
};

test fun(int a)
{
	return a;
}

int main()
{
	/*MyList<int> list;
	for (int i = 0; i < 5; i++)
	{
		list.push_back(i);
	}

	for (auto iter = list.begin(); iter != list.end(); iter++)
	{
		cout << *iter << endl;
	}*/

	fun(1);
	return 0;
}