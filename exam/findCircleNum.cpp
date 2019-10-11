#include "pch.h"

void ColorBlock(int** M, int MSize, int MColSize, int x, int y)
{
	int i = 0;

	//找同一行连续的1
	for (i = y + 1; i < MColSize; i++) {
		if (M[x][i] == 1) {
			M[x][i] = 2;
			ColorBlock(M, MSize, MColSize, x, i);
		}
	}

	// 找同一列连续的1
	for (i = x + 1; i < MSize; i++) {
		if (M[i][y] == 1) {
			M[i][y] = 2;
			ColorBlock(M, MSize, MColSize, i, y);
		}
	}
}

int findCircleNum(int** M, int MSize, int* MColSize) {
	int num = 0;
	int i = 0; 
	int j = 0;
	for (i = 0; i < MSize; i++) {
		for (j = 0; j < MColSize[i]; j++) {
			if (M[i][j] == 1) {
				num++;
				M[i][j] = 2; 
				ColorBlock(M, MSize, MColSize[i], i, j);
			}
		}
	}
	return num;
}

/*
[[1,1,0],
 [1,1,0],
 [0,0,1]]
*/
TEST_F(ExamCodeTest, findCircleNumTest0) {
	int** M = new int*[3];
	M[0] = new int[3];
	M[0][0] = 1;
	M[0][1] = 1;
	M[0][2] = 0;

	M[1] = new int[3];
	M[1][0] = 1;
	M[1][1] = 1;
	M[1][2] = 0;
	
	M[2] = new int[3];
	M[2][0] = 0;
	M[2][1] = 0;
	M[2][2] = 1;

	int MColSize[] = { 3, 3, 3 };

	int num = findCircleNum(M, 3, MColSize);

	EXPECT_EQ(num, 2);
}

/*
[[1,1,0],
 [1,1,1],
 [0,1,1]]
*/
TEST_F(ExamCodeTest, findCircleNumTest1) {
	int** M = new int*[3];
	M[0] = new int[3];
	M[0][0] = 1;
	M[0][1] = 1;
	M[0][2] = 0;

	M[1] = new int[3];
	M[1][0] = 1;
	M[1][1] = 1;
	M[1][2] = 1;

	M[2] = new int[3];
	M[2][0] = 0;
	M[2][1] = 1;
	M[2][2] = 1;

	int MColSize[] = { 3, 3, 3 };

	int num = findCircleNum(M, 3, MColSize);

	EXPECT_EQ(num, 1);
}

/*
[[1,0,0],
 [0,1,0],
 [0,0,1]]
*/
TEST_F(ExamCodeTest, findCircleNumTest2) {
	int** M = new int*[3];
	M[0] = new int[3];
	M[0][0] = 1;
	M[0][1] = 0;
	M[0][2] = 0;

	M[1] = new int[3];
	M[1][0] = 0;
	M[1][1] = 1;
	M[1][2] = 0;

	M[2] = new int[3];
	M[2][0] = 0;
	M[2][1] = 0;
	M[2][2] = 1;

	int MColSize[] = { 3, 3, 3 };

	int num = findCircleNum(M, 3, MColSize);

	EXPECT_EQ(num, 3);
}

/*
[[1,0,0,1],
 [0,1,1,0],
 [0,1,1,1],
 [1,0,1,1]]
*/
TEST_F(ExamCodeTest, findCircleNumTest3) {
	const int N = 4;
	int** M = new int*[N];
	M[0] = new int[N];
	M[0][0] = 1;
	M[0][1] = 0;
	M[0][2] = 0;
	M[0][3] = 1;

	M[1] = new int[N];
	M[1][0] = 0;
	M[1][1] = 1;
	M[1][2] = 1;
	M[1][3] = 0;

	M[2] = new int[N];
	M[2][0] = 0;
	M[2][1] = 1;
	M[2][2] = 1;
	M[2][3] = 1;

	M[3] = new int[N];
	M[3][0] = 0;
	M[3][1] = 0;
	M[3][2] = 1;
	M[3][3] = 1;

	int MColSize[] = { N, N, N, N };

	int num = findCircleNum(M, 4, MColSize);

	EXPECT_EQ(num, 1);
}

