#include "pch.h"

int compareStrLen(const void* a, const void* b) {
	const char* s0 = *((const char**)(a));
	const char* s1 = *((const char**)(b));
	return (strlen(s1) - strlen(s0));
}

int strstr_r(char* s, char* subs) {
	int diff = strlen(s) - strlen(subs);
	return (0 == strcmp(s + diff, subs));
	/*
	int i = 0;
	int slen = strlen(s);
	int len = strlen(subs);
	int diff = slen - len;
	if (len > slen) {
		return 0;
	}
	for (i = len - 1; i >= 0; i--) {
		if (subs[i] != s[i + diff]) {
			return 0;
		}
	}
	return 1;
	*/
}

int minimumLengthEncoding(char ** words, int wordsSize) {
	int len = 0;
	int i = 0;
	int* minLen = (int*)malloc(sizeof(int) * wordsSize);
	memset(minLen, -1, sizeof(int) * wordsSize);
	qsort(words, wordsSize, sizeof(char*), compareStrLen);
	for (i = 0; i < wordsSize; i++) {
		if (minLen[i] == -1) {
			minLen[i] = strlen(words[i]) + 1;
		}
		for (int j = i + 1; j < wordsSize; j++) {
			if (minLen[j] != -1) {
				continue;
			}
			if (strstr_r(words[i], words[j])) {
				minLen[j] = 0;
			}
		}
	}

	for (i = 0; i < wordsSize; i++) {
		len += minLen[i];
	}

	return len;
}

TEST_F(ExamCodeTest, minLenEncodingTest0) {
	const char* wordList[] = { "time", "me", "bell" };
	int wordsSize = sizeof(wordList) / sizeof(wordList[0]);
	char** words = (char**)malloc(sizeof(char*) * wordsSize);
	for (int i = 0; i < wordsSize; i++) {
		words[i] = (char*)malloc(strlen(wordList[i]) + 1);
		strcpy(words[i], wordList[i]);
	}

	int len = minimumLengthEncoding(const_cast<char**>(words), wordsSize);
	EXPECT_EQ(len, 10);

	for (int i = 0; i < wordsSize; i++) {
		free(words[i]);
	}
	free(words);
}

TEST_F(ExamCodeTest, minLenEncodingTest1) {
	const char* wordList[] = { "time", "tim", "bell" };
	int wordsSize = sizeof(wordList) / sizeof(wordList[0]);
	char** words = (char**)malloc(sizeof(char*) * wordsSize);
	for (int i = 0; i < wordsSize; i++) {
		words[i] = (char*)malloc(strlen(wordList[i]) + 1);
		strcpy(words[i], wordList[i]);
	}

	int len = minimumLengthEncoding(const_cast<char**>(words), wordsSize);
	EXPECT_EQ(len, 14);

	for (int i = 0; i < wordsSize; i++) {
		free(words[i]);
	}
	free(words);
}


