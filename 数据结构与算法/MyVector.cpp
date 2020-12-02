#include "MyVector.h"
#include "iostream"

int main()
{
	MyVector<int> vec(9, 9);
	for (auto iter=vec.begin();iter!=vec.end();iter++)
	{
		cout << *iter;
	}
	return 0;
}