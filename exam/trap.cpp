#include "pch.h"

int calcSize(int* height, int leftPos, int rightPos) {
	int size = 0;
	int i = 0;
	int edge = 0;
	if (height[leftPos] < height[rightPos]) {
		for (i = leftPos + 1; i < rightPos; i++) {
			size += height[leftPos] - height[i];
		}
	}
	else {
		edge = leftPos;
		while ((height[edge + 1] <= height[edge]) && (height[edge + 1] > height[rightPos])) {
			edge++;
		}
		for (i = edge + 1; i < rightPos; i++) {
			size += height[rightPos] - height[i];
		}
	}
	return size;
}

int maxThanLeft(int* height, int heightSize, int pos) {
	int i = 0;
	for (i = pos + 1; i < heightSize; i++) {
		if (height[i] > height[pos]) {
			return 0;
		}
	}

	return 1;
}

int trap(int* height, int heightSize) {
	int total = 0;
	int i = 0;
	int leftPos = 0;
	int leftHeight = 0;
	int bottomPos = 0;
	int bottomHeight = 0;
	int rightHeight = 0;
	int rightPos = 0;
	int size = 0;
	if (heightSize == 0) {
		return 0;
	}
	leftHeight = height[0];
	bottomHeight = height[0];
	for (i = 1; i < heightSize; i++) {
		if ((height[i] < bottomHeight) || ((bottomPos < leftPos) && (height[i] < leftHeight))) {
			bottomHeight = height[i];
			bottomPos = i;
		}
		if ((height[i] > bottomHeight) && (leftHeight > bottomHeight) && (leftPos < bottomPos)) {
			if ((height[i] >= rightHeight) && (i > rightPos)) {
				size = calcSize(height, leftPos, i);
				rightHeight = height[i];
				rightPos = i;
			}
		}
		if ((height[i] >= leftHeight) || maxThanLeft(height, heightSize, i)) {
			leftHeight = height[i];
			leftPos = i;
			rightHeight = 0;
			rightPos = 0;
			total += size;
			size = 0;
		}
	}
	total += size;
	return total;
}


TEST_F(ExamCodeTest, trap_test0) {
	int height[] = { 0,1,0,2,1,0,1,3,2,1,2,1 };
	int total = trap(height, sizeof(height) / sizeof(height[0]));
	EXPECT_EQ(total, 6);
}

TEST_F(ExamCodeTest, trap_test1) {
	int height[] = { 5, 4, 1, 2 };
	int total = trap(height, sizeof(height) / sizeof(height[0]));
	EXPECT_EQ(total, 1);
}

TEST_F(ExamCodeTest, trap_test2) {
	int height[] = { 4,2,0,3,2,5 };
	int total = trap(height, sizeof(height) / sizeof(height[0]));
	EXPECT_EQ(total, 9);
}

TEST_F(ExamCodeTest, trap_test3) {
	int height[] = { 5,5,1,7,1,1,5,2,7,6 };
	int total = trap(height, sizeof(height) / sizeof(height[0]));
	EXPECT_EQ(total, 23);
}

TEST_F(ExamCodeTest, trap_test4) {
	int height[] = { 4,3,3,9,3,0,9,2,8,3 };
	int total = trap(height, sizeof(height) / sizeof(height[0]));
	EXPECT_EQ(total, 23);
}

TEST_F(ExamCodeTest, trap_test5) {
	int height[] = { 9,6,8,8,5,6,3 };
	int total = trap(height, sizeof(height) / sizeof(height[0]));
	EXPECT_EQ(total, 3);
}

TEST_F(ExamCodeTest, trap_test6) {
	int height[] = { 3,6,5,8,8,6,9 };
	int total = trap(height, sizeof(height) / sizeof(height[0]));
	EXPECT_EQ(total, 3);
}
