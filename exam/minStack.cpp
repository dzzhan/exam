#include "pch.h"

#define BASIC_STACK_SIZE 64

typedef struct {
	int top;
	int buff_size;
	int minPos;
	int* buff;
} MinStack;

/** initialize your data structure here. */

MinStack* minStackCreate() {
	MinStack* stack = (MinStack*)malloc(sizeof(MinStack));
	if (NULL == stack) {
		return NULL;
	}
	stack->buff = (int*)malloc(BASIC_STACK_SIZE * sizeof(int));
	if (NULL == stack->buff) {
		free(stack);
		return NULL;
	}
	stack->buff_size = BASIC_STACK_SIZE;
	stack->top = 0;
	stack->minPos = 0;
	memset(stack->buff, 0, stack->buff_size * sizeof(int));
	return stack;
}

void minStackPush(MinStack* obj, int x) {
	int* tmpBuff = NULL;
	if (obj->top >= obj->buff_size) {
		tmpBuff = (int*)malloc(obj->buff_size * 2 * sizeof(int));
		if (NULL == tmpBuff) {
			return;
		}
		memcpy(tmpBuff, obj->buff, obj->buff_size * sizeof(int));
		free(obj->buff);
		obj->buff = tmpBuff;
		obj->buff_size *= 2;
	}

	obj->buff[obj->top] = x;
	if (x < obj->buff[obj->minPos]) {
		obj->minPos = obj->top;
	}
	obj->top++;
}

void minStackPop(MinStack* obj) {
	int i = 0;
	if (obj->top <= 0) {
		return;
	}
	obj->top--;

	if (obj->minPos >= obj->top) {
		obj->minPos = 0;
		for (i = 0; i < obj->top; i++) {
			if (obj->buff[i] < obj->buff[obj->minPos]) {
				obj->minPos = i;
			}
		}
	}
}

int minStackTop(MinStack* obj) {
	if (obj->top <= 0) {
		return -1;
	}
	return obj->buff[obj->top - 1];
}

int minStackGetMin(MinStack* obj) {
	if (obj->minPos >= obj->top) {
		return -1;
	}
	return obj->buff[obj->minPos];
}

void minStackFree(MinStack* obj) {
	if (NULL == obj) {
		return;
	}

	if (NULL != obj->buff) {
		free(obj->buff);
	}

	free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, x);

 * minStackPop(obj);

 * int param_3 = minStackTop(obj);

 * int param_4 = minStackGetMin(obj);

 * minStackFree(obj);
*/

TEST_F(ExamCodeTest, MiniStackTest0) {
	MinStack* stack = minStackCreate();
	EXPECT_NE((MinStack*)NULL, stack);
	minStackPush(stack, -2);
	minStackPush(stack, 0);
	minStackPush(stack, -3);
	int val = minStackGetMin(stack);
	EXPECT_EQ(val, -3);
	minStackPop(stack);
	val = minStackTop(stack);
	EXPECT_EQ(val, 0);
	val = minStackGetMin(stack);
	EXPECT_EQ(val, -2);
}