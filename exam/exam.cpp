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

int main()
{
	int s[] = { 1, 2, 4, 3, 8, 9 };
	QuickSort(s, 0, (sizeof(s) / sizeof(int)) - 1);
}
