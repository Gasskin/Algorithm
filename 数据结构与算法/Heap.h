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
	void init(int* arr,int len);
	void init(vector<int> data);
	void insert(int val);
	void remove(int index);
	void show();
	void heapSort();
private:
	void floating(int index);
	void sunking(int index);
private:
	vector<int> data;
	vector<int> heap;
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

void MaxHeap::init(int* arr, int len)
{
	if (len <= 0)
	{
		return;
	}
	int val = arr[len - 1];
	insert(val);
	init(arr, len - 1);
}

void MaxHeap::init(vector<int> data)
{
	if (data.empty())
	{
		return;
	}
	insert(data[data.size() - 1]);
	data.pop_back();
	init(data);
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
	while (index < (int)data.size() - 1)
	{
		//如果当前节点比左孩子小
		if (data[index] < data[index * 2 + 1])
		{
			//如果同时还比右孩子小
			if (data[index] < data[(index + 1) * 2])
			{
				//那就和较大的孩子交换
				if (data[index * 2 + 1] > data[(index + 1) * 2])
				{
					swap(data[index], data[index * 2 + 1]);
					index = index * 2 + 1;
				}
				else
				{
					swap(data[index], data[(index + 1) * 2]);
					index = (index + 1) * 2;
				}
			}
			else
			{
				swap(data[index], data[index * 2 + 1]);
				index = index * 2 + 1;
			}
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

