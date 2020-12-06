#pragma once
#include <vector>
#include <iostream>
using namespace std;

//大根堆，父节点大于孩子
class MaxHeap
{
public:
	MaxHeap() { data.reserve(10); }
public:
	void init();
	void insert(int val);
	void remove(int index);
	void show();
private:
	void floating(int index);
	void sunking(int index);
private:
	vector<int> data;
};

void MaxHeap::init()
{
	int val;
	cin >> val;
	if (val > 0)
	{
		insert(val);
		init();
	}
}

void MaxHeap::insert(int val)
{
	data.push_back(val);
	floating(data.size() - 1);
}

void MaxHeap::remove(int index)
{
	swap(data[index], data[data.size() - 1]);
	data.pop_back();
	sunking(index);
}

void MaxHeap::show()
{
	for (auto iter = data.begin(); iter != data.end(); iter++)
	{
		cout << *iter << " ";
	}
	cout << endl;
}

void MaxHeap::floating(int index)
{
	while (index > 0)
	{
		//节点序号为偶数，那么是右节点
		if (index % 2 == 0)
		{
			//如果当前节点大于他的夫节点，那么交换两个位置
			if (data[index] > data[(index - 1) / 2])
			{
				swap(data[index], data[(index - 1) / 2]);
				index = (index - 1) / 2;
			}
			else
			{
				break;
			}
		}
		//否则就是左节点
		else
		{
			if (data[index] > data[index / 2])
			{
				swap(data[index], data[index / 2]);
				index = index / 2;
			}
			else
			{
				break;
			}
		}
	}
}

void MaxHeap::sunking(int index)
{
	while (index < data.size() - 1)
	{
		//如果当前节点比左孩子小
		if (data[index] < data[index * 2 + 1])
		{
			swap(data[index], data[index * 2 + 1]);
			index = index * 2 + 1;
		}
		//如果当前节点比右孩子小
		else if (data[index] < data[(index + 1) * 2])
		{
			swap(data[index], data[(index + 1) * 2]);
			index = (index + 1) * 2;
		}
		else
		{
			break;
		}
	}
}
