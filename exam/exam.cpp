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

//堆排序是将数据看成是完全二叉树、根据完全二叉树的特性来进行排序的一种算法
//最大堆要求节点的元素都要不小于其孩子，最小堆要求节点元素都不大于其左右孩子
//那么处于最大堆的根节点的元素一定是这个堆中的最大值
//构造一个最大堆
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

//全排列算法
//比如，假设集合是{ a,b,c }, 那么这个集合中元素的全部排列是{ (a,b,c),(a,c,b),(b,a,c),(b,c,a),(c,a,b),(c,b,a) }，
//显然，给定n个元素共同拥有n!种不同的排列，假设给定集合是{ a,b,c,d }，能够用以下给出的简单算法产生其全部排列，
//即集合(a, b, c, d)的全部排列有以下的排列组成：
//（1）以a开头后面跟着(b, c, d)的排列
//（2）以b开头后面跟着(a, c, d)的排列
//（3）以c开头后面跟着(a, b, d)的排列
//（4）以d开头后面跟着(a, b, c)的排列
void Permutation(int* a, int k, int m)
{
	int i, j;
	if (k == m)
	{
		for (i = 0; i <= m; i++)
			cout << a[i];
		cout << endl;
	}
	else
	{
		for (j = k; j <= m; j++)
		{
			Swap(&a[j], &a[k]);
			Permutation(a, k + 1, m);
			swap(a[j], a[k]);
		}
	}
}

//求幂次
double qpow(double a, long long b) {
	double res = 1;
	while (b) {
		if (b & 1) res = res * a;
		b >>= 1;
		a *= a;
	}
	return res;
}


double myPow(double x, long long n) {
	if (n == 0) return 1;
	if (n > 0) return qpow(x, n);
	if (n < 0) return 1 / qpow(x, -n);
	return 1.0;
}

int main()
{
	int s[] = { 1, 2, 4, 3, 8, 9 };
	//QuickSort(s, 0, (sizeof(s) / sizeof(int)) - 1);
	HeapSort(s, (sizeof(s) / sizeof(int)));

	int a[] = { 1, 2, 3, 4, 5 };
	Permutation(a, 0, 4);
}
