#include "MyList.h"
#include<list>

struct node
{
	node(int n)
		:data(n),next(nullptr),prev(nullptr){}

	int* next;
	int* prev;
	int data;
};

struct iter
{
	iter(node* node):n(node){}

	int& operator*()const
	{
		cout << "*" << endl;
		return (*n).data;
	}

	int* operator->()const
	{
		cout << "->" << endl;
		return &(operator*());
	}

	node* n;
};

int main()
{
	list<int> list;
	for (int i = 0; i < 5; i++)
	{
		list.push_back(i);
	}
	for (auto iter= list.begin();iter!= list.end();iter++)
	{
		cout << *iter << " ";
		iter->
	}
	return 0;
}