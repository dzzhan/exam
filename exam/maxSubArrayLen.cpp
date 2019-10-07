#include "pch.h"

int maxSubArrayLen(int* nums, int numsSize, int k) {
	int total = 0;
	int i = 0;
	int len = numsSize;
	int start = 0;
	int sum = 0;
	total = 0;
	for (i = 0; i < len; i++) {
		total += nums[i];
	}
	if (total == k) {
		return len;
	}

	while (len > 1) {
		total -= nums[len - 1];
		len--;
		sum = total;
		if (sum == k) {
			return len;
		}
		start = 1;
		while ((start + len) <= numsSize) {
			sum -= nums[start - 1];
			sum += nums[start + len - 1];
			if (sum == k) {
				return len;
			}
			start++;
		}
	}

	return 0;
}

TEST_F(ExamCodeTest, maxSubArrayTest0) {
	int nums[] = { 1, -1, 5, -2, 3 };
	int k = 3;
	int len = maxSubArrayLen(nums, sizeof(nums) / sizeof(nums[0]), k);
	EXPECT_EQ(len, 4);
}

TEST_F(ExamCodeTest, maxSubArrayTest1) {
	int nums[] = { -2, -1, 2, 1 };
	int k = 1;
	int len = maxSubArrayLen(nums, sizeof(nums) / sizeof(nums[0]), k);
	EXPECT_EQ(len, 2);
}
