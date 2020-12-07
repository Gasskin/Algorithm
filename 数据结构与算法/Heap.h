#pragma once
#include <vector>
#include <iostream>
using namespace std;

//����ѣ����ڵ���ں���
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
		//�ڵ����Ϊż������ô���ҽڵ�
		if (index % 2 == 0)
		{
			//�����ǰ�ڵ�������ķ�ڵ㣬��ô��������λ��
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
		//���������ڵ�
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
		//�����ǰ�ڵ������С
		if (data[index] < data[index * 2 + 1])
		{
			//���ͬʱ�����Һ���С
			if (data[index] < data[(index + 1) * 2])
			{
				//�Ǿͺͽϴ�ĺ��ӽ���
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
		//�����ǰ�ڵ���Һ���С
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

