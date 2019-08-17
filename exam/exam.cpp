// exam.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
using namespace std;

void Swap(int* a, int* b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void QuickSort(int* s, int left, int right) {
	if (left >= right) {
		return;
	}
	int x = s[left];
	int i = left;
	int j = right;
	while (i < j) {
		while ((i < j) && (s[j] >= x)) {		//从右向左找比x小的数
			j--;
		}
		if (i < j) {
			s[i] = s[j];
			i++;
		}
		while ((i < j) && (s[i] < x)) {			//从左向右找比x大的数
			i++;
		}
		if (i < j) {
			s[j] = s[i];
			j--;
		}
	}
	s[i] = x;
	QuickSort(s, left, i - 1);
	QuickSort(s, i + 1, right);
}


void MaxHeapify(int arr[], int start, int end) {
	// 建立父節點指標和子節點指標
	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end) { // 若子節點指標在範圍內才做比較
		if (((son + 1) <= end) && (arr[son] < arr[son + 1])) // 先比較兩個子節點大小，選擇最大的
			son++;
		if (arr[dad] > arr[son]) //如果父節點大於子節點代表調整完畢，直接跳出函數
			return;
		else { // 否則交換父子內容再繼續子節點和孫節點比較
			Swap(&arr[dad], &arr[son]);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}

void HeapSort(int arr[], int len) {
	int i;
	// 初始化，i從最後一個父節點開始調整
	for (i = len / 2 - 1; i >= 0; i--)
		MaxHeapify(arr, i, len - 1);
	// 先將第一個元素和已排好元素前一位做交換，再重新調整，直到排序完畢
	for (i = len - 1; i > 0; i--) {
		Swap(&arr[0], &arr[i]);
		MaxHeapify(arr, 0, i - 1);
	}
}

int main()
{
	int s[] = { 1, 2, 4, 3, 8, 9 };
	//QuickSort(s, 0, (sizeof(s) / sizeof(int)) - 1);
	HeapSort(s, (sizeof(s) / sizeof(int)));
}
