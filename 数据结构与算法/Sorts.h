#pragma once
#include <iostream>
using namespace std;

void show(int* arr, int len)
{
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

//冒泡排序 n^2 n^2
void BubbleSort(int* arr,int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

//选择排序 n^2 n^2
void SelectSort(int* arr, int len)
{
	int key;
	for (int i = 0; i < len - 1; i++)
	{
		key = i;
		for (int j = i + 1; j < len; j++)
		{
			if (arr[j] < arr[key])
			{
				key = j;
			}
		}
		if (key != i)
		{
			swap(arr[key], arr[i]);
		}
	}
}

//插入排序 数组越有序越接近n，越无序越接近n^2
void InsertSort(int* arr, int len)
{
	for (int i = 1; i < len; i++)
	{
		int j = i - 1;
		int temp = arr[i];//需要暂存arr[i]，因为会被while拷贝顶替
		while (arr[j] > temp && j >= 0)
		{
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = temp;
	}
}

//希尔排序，插入排序的改进
void ShellSort(int* arr,int len)
{
	//把数据分为n组
	for (int gap = len / 2; gap > 0; gap /= 2)
	{
		//局部插入排序
		for (int i = gap; i < len; i++)
		{
			int j = i - gap;
			int temp = arr[i];
			while (arr[j] > temp && j >= 0)
			{
				arr[j + gap] = arr[j];
				j = j - gap;
			}
			arr[j + gap] = temp;
		}
	}
}

//快速排序
int quick(int* arr, int start, int end)
{
	end = end - 1;//只是为了统一输入格式，可以直接输入数组大小
	int key = arr[start];
	while (start < end)
	{
		//从右往左找到第一个比key小的
		while (start < end && arr[end] >= key)
		{
			end--;
		}
		if (start < end)
		{
			arr[start] = arr[end];
		}
		//从左往右找到第一个比key大的
		while (start < end && arr[start] <= key)
		{
			start++;
		}
		if (start < end)
		{
			arr[end] = arr[start];
		}
	}
	arr[start] = key;
	return start;
}

void QuickSort(int* arr, int start, int end)
{
	if (start >= end)
	{
		return;
	}
	int flag = quick(arr, start, end);
	QuickSort(arr, start, flag - 1);
	QuickSort(arr, flag + 1, end);
}

//归并排序
void merge(int* arr, int start, int mid, int end)
{
	int* temp = new int[end - start + 1];
	int i = start;
	int m = mid+1;
	int k = 0;
	while (i <= mid && m <= end)
	{
		if (arr[i] < arr[m])
		{
			temp[k++] = arr[i++];
		}
		else
		{
			temp[k++] = arr[m++];
		}
	}
	while (i <= mid)
	{
		temp[k++] = arr[i++];
	}
	while (m <= end)
	{
		temp[k++] = arr[m++];
	}
	for (int i = 0; i < k; i++)
	{
		arr[start + i] = temp[i];
	}
	delete temp;
}

void MergeSort(int* arr,int start,int end)
{
	if (start >= end)
	{
		return;
	}
	int mid = (start + end) / 2;
	MergeSort(arr, start, mid);
	MergeSort(arr, mid + 1, end);
	merge(arr, start, mid, end);
}