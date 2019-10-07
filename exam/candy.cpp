#include "pch.h"

int candy(int* ratings, int ratingsSize) {
	int totalSize = ratingsSize;
	int i = 0;
	int* candyCnt = (int*)malloc(sizeof(int) * ratingsSize);
	memset(candyCnt, 0, sizeof(int) * ratingsSize);
	for (i = 0; i < (ratingsSize - 1); i++) {
		if ((ratings[i] < ratings[i + 1]) && (candyCnt[i] >= candyCnt[i + 1])) {
			candyCnt[i + 1] = candyCnt[i] + 1;
		}
	}
	for (i = (ratingsSize - 1); i > 0; i--) {
		if ((ratings[i - 1] > ratings[i]) && (candyCnt[i - 1] <= candyCnt[i])) {
			candyCnt[i - 1] = candyCnt[i] + 1;
		}
	}
	for (i = 0; i < ratingsSize; i++) {
		totalSize += candyCnt[i];
	}
	free(candyCnt);
	return totalSize;
}

TEST_F(ExamCodeTest, candyTest0) {
	int rating[] = {1, 0, 2};
	int num = candy(rating, sizeof(rating) / sizeof(rating[0]));
	EXPECT_EQ(num, 5);
}

TEST_F(ExamCodeTest, candyTest1) {
	int rating[] = { 1, 2, 2 };
	int num = candy(rating, sizeof(rating) / sizeof(rating[0]));
	EXPECT_EQ(num, 4);
}

TEST_F(ExamCodeTest, candyTest2) {
	int rating[] = { 1,2,87,87,87,2,1 };
	int num = candy(rating, sizeof(rating) / sizeof(rating[0]));
	EXPECT_EQ(num, 13);
}
