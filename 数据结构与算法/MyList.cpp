#include "MyList.h"

int main()
{
	MyList<int> list;
	for (int i = 0; i < 5; i++)
	{
		list.push_back(i);
	}
	auto iter = list.begin();
	for (int i = 0; i < 5; i++)
	{
		cout << *iter << " ";
		iter++;
	}
	/*for (auto iter = list.begin(); iter != list.end(); iter++)
	{
		cout << *iter << endl;
	}*/
	return 0;
}