#include "MyVector.h"

void show(MyVector<int>& vec)
{
	for (auto iter = vec.begin(); iter != vec.end(); iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;
}

int main()
{
	MyVector<int> vec(9, 9);
	show(vec);
	vec.pop_back();
	show(vec);
	vec.push_back(8);
	show(vec);
	return 0;
}