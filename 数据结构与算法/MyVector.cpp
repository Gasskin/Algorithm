#include "MyVector.h"

void show(MyVector<int>& vec)
{
	for (auto iter = vec.begin(); iter != vec.end(); iter++)
	{
		cout << *iter << " ";
	}
	cout << endl<<endl;
}

int main()
{
	MyVector<int> vec(5);
	for (int i = 0; i < 5; i++)
	{
		vec[i] = i;
	}
	show(vec);
	
	vec.insert(vec.end()-2, 9, 0);
	show(vec);
	return 0;
}