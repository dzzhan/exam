#include "pch.h"

int romanChar2Int(char c) {
	if (c == 'I') {
		return 1;
	}
	else if (c == 'V') {
		return 5;
	}
	else if (c == 'X') {
		return 10;
	}
	else if (c == 'L') {
		return 50;
	}
	else if (c == 'C') {
		return 100;
	}
	else if (c == 'D') {
		return 500;
	}
	else if (c == 'M') {
		return 1000;
	}
	return 0;
}

int romanToInt(char * s) {
	int val = 0;
	int len = strlen(s);
	int i = 0;
	for (i = 0; i < len - 1; i++) {
		if ((s[i] == 'I') && (s[i + 1] == 'V')) {
			val += 4;
			i++;
		}
		else if ((s[i] == 'I') && (s[i + 1] == 'X')) {
			val += 9;
			i++;
		}
		else if ((s[i] == 'X') && (s[i + 1] == 'L')) {
			val += 40;
			i++;
		}
		else if ((s[i] == 'X') && (s[i + 1] == 'C')) {
			val += 90;
			i++;
		}
		else if ((s[i] == 'C') && (s[i + 1] == 'D')) {
			val += 400;
			i++;
		}
		else if ((s[i] == 'C') && (s[i + 1] == 'M')) {
			val += 900;
			i++;
		}
		else {
			val += romanChar2Int(s[i]);
		}
	}
	if (i < len) {
		val += romanChar2Int(s[i]);
	}
	return val;
}

TEST_F(ExamCodeTest, romaToInt_test0) {
	char s[] = { "III" };
	int val = romanToInt(s);
	EXPECT_EQ(3, val);
}

TEST_F(ExamCodeTest, romaToInt_test1) {
	char s[] = { "IV" };
	int val = romanToInt(s);
	EXPECT_EQ(4, val);
}

TEST_F(ExamCodeTest, romaToInt_test2) {
	char s[] = { "IX" };
	int val = romanToInt(s);
	EXPECT_EQ(9, val);
}

TEST_F(ExamCodeTest, romaToInt_test3) {
	char s[] = { "LVIII" };
	int val = romanToInt(s);
	EXPECT_EQ(58, val);
}

TEST_F(ExamCodeTest, romaToInt_test4) {
	char s[] = { "MCMXCIV" };
	int val = romanToInt(s);
	EXPECT_EQ(1994, val);
}
