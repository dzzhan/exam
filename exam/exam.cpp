﻿// exam.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"

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

int DfsSearch(char* W, char* MAP, int M, int N, int L, int S, int Founded, int* Visited)
{
	if (Founded == L) {
		return 1;
	}
	int i = S >> 16;
	int j = S & 0xffff;

	int tmp = (i - 1) * N + j;
	if ((i > 0) && (Visited[tmp] == 0) && (MAP[tmp] == W[S])) {
		Visited[tmp] = 1;
		if (1 == DfsSearch(W, MAP, M, N, L, ((i - 1) << 16) + j, Founded + 1, Visited)) {
			return 1;
		}
		Visited[tmp] = 0;
	}

	tmp = (i + 1) * N + j;
	if ((i < (M - 1)) && (Visited[tmp] == 0) && (MAP[tmp] == W[S])) {
		Visited[tmp] = 1;
		if (1 == DfsSearch(W, MAP, M, N, L, ((i + 1) << 16) + j, Founded + 1, Visited)) {
			return 1;
		}
		Visited[tmp] = 0;
	}

	tmp = i * N + j - 1;
	if ((j > 0) && (Visited[tmp] == 0) && (MAP[tmp] == W[S])) {
		Visited[tmp] = 1;
		if (1 == DfsSearch(W, MAP, M, N, L, (i << 16) + (j - 1), Founded + 1, Visited)) {
			return 1;
		}
		Visited[tmp] = 0;
	}

	tmp = i * N + j + 1;
	if ((i < (M - 1)) && (Visited[tmp] == 0) && (MAP[tmp] == W[S])) {
		Visited[tmp] = 1;
		if (1 == DfsSearch(W, MAP, M, N, L, (i << 16) + (j + 1), Founded + 1, Visited)) {
			return 1;
		}
		Visited[tmp] = 0;
	}

	return 0;
}

int SolveWordMaze(char* W, char* MAP, int M, int N)
{
	int i = 0;
	int j = 0;
	int L = strlen(W);
	int* VisitedPath = (int*)malloc(M * N * sizeof(int));
	memset(VisitedPath, 0, sizeof(int) * M * N);
	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
			if (W[0] == MAP[(i * N) + j]) {
				VisitedPath[i * N + j] = 1;
				if (1 == DfsSearch(W, MAP, M, N, L, (i << 16) + j, 1, VisitedPath)) {
					return 1;
				}
				VisitedPath[i * N + j] = 0;
			}
		}
	}
	return 0;
}



char * licenseKeyFormatting(char * S, int K) {
	int len = strlen(S);
	int i = 0;
	int j = 0;
	int pad = 0;
	int sep = 0;
	char* ss = (char*)malloc(len + 1);

	for (i = 0; i < len; i++) {
		if ((S[i] >= 'a') && (S[i] <= 'z')) {
			S[j] = S[i] - 'a' + 'A';
			j++;
		}
		else if (S[i] != '-') {
			j++;
		}
	}
	pad = j % K;
	sep = (j + pad) / K;

	j = pad;
	for (i = 0; i < len; i++) {
		if ((j != 0) && ((j % K) == 0)) {
			ss[0] = '-';
			ss++;
		}
		if (S[i] != '-') {
			ss[0] = S[i];
			ss++;
			j++;
		}
	}

	return ss;
}

#define MAX_STACK_SIZE 20000
#define MAX_OP_STACK   10000
#define IS_DIGITAL(x) (((x) >= '0') && ((x) <= '9'))
#define OP_ADD -2
#define OP_SUB -3

int calculate(char * s) {
	int stack[MAX_STACK_SIZE] = { -1 };
	int top = -1;
	int val = 0;
	char opcode[MAX_OP_STACK] = {0};
	int opTop = 0;
	int optop = 0;
	int i = 0;
	int len = strlen(s);
	int lastIsDigital = 0;
	memset(stack, 0xff, sizeof(stack));
	for (i = 0; i < len; i++) {
		if (IS_DIGITAL(s[i])) {
			if (lastIsDigital) {
				val = val * 10 + (s[i] - '0');
				stack[top] = val;
			}
			else {
				top++;
				val = s[i] - '0';
				stack[top] = val;
			}
			lastIsDigital = 1;
		}
		else if (s[i] == '(') {
			opcode[opTop] = s[i];
			opTop++;
			lastIsDigital = 0;
		}
		else if (s[i] == ')') {
			while (opcode[opTop - 1] != '(') {
				if (opcode[opTop - 1] == '+') {
					stack[top - 1] += stack[top];
					stack[top] = -1;
					top -= 1;
					//stack[top] = OP_ADD;
					//top++;
				}
				else if (opcode[opTop - 1] == '-') {
					stack[top - 1] -= stack[top];
					stack[top] = -1;
					top -= 1;
					//stack[top] = OP_SUB;
					//top++;
				}
				opcode[opTop - 1] = 0;
				opTop--;
			}
			opcode[opTop - 1] = 0;
			opTop--;
			val = 0;
			lastIsDigital = 0;
		}
		else if ((s[i] == '+') || (s[i] == '-')) {
			if ((opTop > 0) && ((opcode[opTop - 1] == '+') || (opcode[opTop - 1] == '-'))) {
				stack[top - 1] = (opcode[opTop - 1] == '+') ? (stack[top - 1] + stack[top]) : (stack[top - 1] - stack[top]);
				stack[top] = -1;
				top--;
				val = 0;
				opcode[opTop - 1] = 0;
				opTop--;
			}
			opcode[opTop] = s[i];
			opTop++;
			lastIsDigital = 0;
		}
	}
	opTop--;
	while (opTop >= 0) {
		stack[top - 1] = (opcode[opTop] == '+') ? (stack[top - 1] + stack[top]) : (stack[top - 1] - stack[top]);
		stack[top] = -1;
		top -= 1;
		//stack[top] = opcode[opTop] == '+' ? OP_ADD : OP_SUB;
		opTop--;
	}
	return stack[0];
}

char ** findMissingRanges(int* nums, int numsSize, int lower, int upper, int* returnSize) {
	int i = 0;
	int rangeCnt = 0;
	long long rangeStart = -1;
	long long rangeEnd = 0;
	char** missingRange = (char**)malloc(sizeof(char*) * (numsSize + 10));
	memset(missingRange, 0, sizeof(char*) * (numsSize + 10));

	if (numsSize == 0) {
		rangeStart = lower;
		rangeEnd = upper;
		if (rangeEnd == rangeStart) {
			missingRange[rangeCnt] = (char*)malloc(sizeof(char) * 20);
			sprintf(missingRange[rangeCnt], "%lld", rangeEnd);
			rangeCnt++;
			rangeStart = nums[0] + 1;
		}
		else if (rangeEnd > rangeStart) {
			missingRange[rangeCnt] = (char*)malloc(sizeof(char) * 20);
			sprintf(missingRange[rangeCnt], "%lld->%lld", rangeStart, rangeEnd);
			rangeCnt++;
			rangeStart = nums[0] + 1;
		}
		*returnSize = 1;
		return missingRange;
	}
	else if ((numsSize == 2) && (lower == nums[0]) && (upper == nums[1])) {
		*returnSize = 0;
		return missingRange;
	}

	rangeStart = lower;
	rangeEnd = nums[0] - 1;
	if (rangeEnd == rangeStart) {
		missingRange[rangeCnt] = (char*)malloc(sizeof(char) * 20);
		sprintf(missingRange[rangeCnt], "%lld", rangeEnd);
		rangeCnt++;
		rangeStart = nums[0] + 1;
	}
	else if (rangeEnd > rangeStart) {
		missingRange[rangeCnt] = (char*)malloc(sizeof(char) * 20);
		sprintf(missingRange[rangeCnt], "%lld->%lld", rangeStart, rangeEnd);
		rangeCnt++;
		rangeStart = nums[0] + 1;
	}
	else if (rangeEnd < lower) {
		rangeStart = lower - 1;
	}

	for (i = 1; i < numsSize; i++) {
		if (rangeStart < lower) {
			rangeStart = nums[i] + 1;
		}
		if ((rangeStart == nums[i]) || (nums[i] == (nums[i - 1] + 1))) {
			rangeStart = nums[i] + 1;
			continue;
		}
		rangeEnd = nums[i] - 1;
		if (rangeEnd == rangeStart) {
			missingRange[rangeCnt] = (char*)malloc(sizeof(char) * 20);
			sprintf(missingRange[rangeCnt], "%lld", rangeEnd);
			rangeCnt++;
		}
		else if (rangeEnd > rangeStart) {
			missingRange[rangeCnt] = (char*)malloc(sizeof(char) * 20);
			sprintf(missingRange[rangeCnt], "%lld->%lld", rangeStart, rangeEnd);
			rangeCnt++;
		}
		rangeStart = nums[i] + 1;
	}
	if (nums[numsSize - 1] < upper) {
		rangeStart = nums[numsSize - 1] + 1;
		rangeEnd = upper;
		if (rangeEnd == rangeStart) {
			missingRange[rangeCnt] = (char*)malloc(sizeof(char) * 20);
			sprintf(missingRange[rangeCnt], "%lld", rangeEnd);
			rangeCnt++;
		}
		else if (rangeEnd > rangeStart) {
			missingRange[rangeCnt] = (char*)malloc(sizeof(char) * 20);
			sprintf(missingRange[rangeCnt], "%lld->%lld", rangeStart, rangeEnd);
			rangeCnt++;
		}
	}

	*returnSize = rangeCnt;
	return missingRange;
}
