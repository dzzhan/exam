#include "pch.h"

#define MAX_PEOPLES 1100

#define SWAP(a, b) do {\
		int t = 0;\
		t = a[0]; a[0] = b[0]; b[0] = t;\
		t = a[1]; a[1] = b[1]; b[1] = t;\
	}while (0)

int compare(const void *a, const void *b)
{
	const int *pa = *(const int **)a;
	const int *pb = *(const int **)b;
	return (pa[0] == pb[0]) ? (pa[1] - pb[1]) : (pb[0] - pa[0]);
}

void MoveResult(int** result, int peopleSize, int pos) {
	int i = 0;
	for (i = peopleSize - 1; i > pos; i--) {
		result[i][0] = result[i - 1][0];
		result[i][1] = result[i - 1][1];
	}
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** reconstructQueue(int** people, int peopleSize, int* peopleColSize, int* returnSize, int** returnColumnSizes) {
	int i = 0;
	int j = 0;
	int k = 0;
	int m = 0;
	int colSize = 0; 
	int** result = NULL; 

	if (peopleSize <= 0) {
		*returnSize = 0;
		return NULL;
	}

	colSize = peopleColSize[0];
	result = (int**)malloc(sizeof(int*) * peopleSize);
	if (result == NULL) {
		return NULL;
	}

	*returnColumnSizes = (int*)malloc(sizeof(int) * peopleSize);
	for (i = 0; i < peopleSize; i++) {
		returnColumnSizes[0][i] = colSize;
		result[i] = (int*)malloc(sizeof(int) * colSize);
		result[i][0] = -1;
		result[i][1] = -1;
	}

	// 按身高排序
	qsort(people, peopleSize, sizeof(int*), compare);

	// 按指定位置插入
	for (i = 0; i < peopleSize; i++) {
		if (result[people[i][1]][0] != -1) {
			MoveResult(result, peopleSize, people[i][1]);
		}
		result[people[i][1]][0] = people[i][0];
		result[people[i][1]][1] = people[i][1];
	}
	*returnSize = peopleSize;
	return result;
}

TEST_F(ExamCodeTest, reconstructQueueTest0) {
	int peopleIn[][2] = { {7, 0}, {4, 4}, {7, 1}, {5, 0}, {6, 1}, {5, 2} };
	int peopleSize = sizeof(peopleIn) / sizeof(peopleIn[0]);
	int** people = (int**)malloc(sizeof(int*) * peopleSize);
	int* peopleColSize = (int*)malloc(sizeof(int) * peopleSize);
	for (int i = 0; i < peopleSize; i++) {
		peopleColSize[i] = 2;
		people[i] = (int*)malloc(sizeof(int) * 2);
		people[i][0] = peopleIn[i][0];
		people[i][1] = peopleIn[i][1];
	}
	int returnSize = 0;
	int* returnColSize = NULL;
	int** result = reconstructQueue(people, peopleSize, peopleColSize, &returnSize, &returnColSize);

	EXPECT_NE((int**)NULL, result);
	EXPECT_EQ(returnSize, peopleSize);
	EXPECT_NE((int*)NULL, returnColSize);
	int peopleOut[][2] = { {5,0},{7,0},{5,2},{6,1},{4,4},{7,1} };
	for (int i = 0; i < peopleSize; i++) {
		EXPECT_EQ(returnColSize[i], 2);
		EXPECT_EQ(result[i][0], peopleOut[i][0]);
		EXPECT_EQ(result[i][1], peopleOut[i][1]);
	}
}
