#include "pch.h"
#include "stdlib.h"

/*
1) 缩写格式：起始字母+被缩略的字母个数+结束字母
2）缩写是唯一的，但被省略的子串可以不唯一
3）缩写必须比原来的短，否则不缩写

1) 长度不超过3个字符的字符串不用缩写
2）长度超过三个字符的，缩写为首字符+被省略字符个数+尾字符
3）解决冲突
*/

#define MAX_WORD_SIZE 400

char* to_str(int v, char* buff, int bufSize) {
	int i = bufSize - 1;
	buff[i] = '\0';
	while ((i >= 0) && (v != 0)) {
		i--;
		buff[i] = '0' + (v % 10);
		v /= 10;
	}

	return &buff[i];
}

int FindCommPrefix(char** dict, int* conflictList, int conflictNum) {
	int i = 0;
	int j = 0;
	int len = strlen(dict[conflictList[0]]);
	while (j < len) {
		for (i = 1; i < conflictNum; i++) {
			if (dict[conflictList[0]][j] != dict[conflictList[i]][j]) {
				return j;
			}
		}
		j++;
	}
	return j;
}

void ResolveConflict(char** dict, char** result, int* conflictList, int conflictNum)
{
	int len = strlen(dict[conflictList[0]]);
	int i = 0;
	int j = 0;
	int diffSize = 0;
	char diffSizeArr[10] = { 0 };
	char* diffSizeStr = diffSizeArr;
	int commSize = FindCommPrefix(dict, conflictList, conflictNum);
	for (i = 0; i < commSize; i++) {
		result[conflictList[0]][i] = dict[conflictList[0]][i];
	}
	result[conflictList[0]][commSize] = '\0';
	for (j = 1; j < conflictNum; j++) {
		strcpy(result[conflictList[j]], result[conflictList[0]]);
	}

	diffSize = (len - 1) - commSize - 1;
	diffSizeStr = to_str(diffSize, diffSizeArr, 9);
	if (diffSize > strlen(diffSizeStr)) {
		for (j = 0; j < conflictNum; j++) {
			result[conflictList[j]][commSize] = dict[conflictList[j]][commSize];
			result[conflictList[j]][commSize + 1] = '\0';
			strcat(result[conflictList[j]], diffSizeStr);
			strcat(result[conflictList[j]], &dict[conflictList[j]][len - 1]);
		}
	}
	else {
		for (j = 0; j < conflictNum; j++) {
			result[conflictList[j]][i] = '\0';
			strcat(result[conflictList[j]], &dict[conflictList[j]][commSize]);
		}
	}
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** wordsAbbreviation(char ** dict, int dictSize, int* returnSize) {
	int i = 0;
	int j = 0;
	int len = 0;
	char** result = (char**)malloc(sizeof(char*) * dictSize);
	int* abrvSize = (int*)malloc(sizeof(int) * dictSize);
	char sizeBuff[10] = { 0 };
	char* sizeStr = sizeBuff;
	int* conflictList = (int*)malloc(sizeof(int) * dictSize);
	int conflictNum = 0;
	
	// 构建缩写
	for (i = 0; i < dictSize; i++) {
		result[i] = (char*)malloc(MAX_WORD_SIZE + 1);
		memset(result[i], 0, MAX_WORD_SIZE + 1);
		len = strlen(dict[i]);
		if (len <= 3) {
			strcpy(result[i], dict[i]);
		}
		else {
			result[i][0] = dict[i][0];
			sizeStr = to_str(len - 2, sizeBuff, 9);
			result[i][1] = '\0';
			strcat(result[i], sizeStr);
			result[i][strlen(result[i])] = dict[i][len - 1];
			abrvSize[i] = strlen(result[i]);
		}
	}

	// 去除重复:找到所有具有相同缩写的单词一并去重
	for (i = 0; i < dictSize; i++) {
		do {
			conflictNum = 0;
			conflictList[conflictNum] = i;
			for (j = i + 1; j < dictSize; j++) {
				if (abrvSize[i] != abrvSize[j]) {
					continue;
				}
				if (strcmp(result[i], result[j])) {
					continue;
				}
				conflictNum++;
				conflictList[conflictNum] = j;
			}
			if (conflictNum > 0) {
				ResolveConflict(dict, result, conflictList, conflictNum + 1);
			}
		} while (conflictNum > 0);
	}

	// 释放缩写长度内存
	free(abrvSize);
	free(conflictList);
	*returnSize = dictSize;
	return result;
}
/*
TEST_F(ExamCodeTest, FindCommPrefixTest0) {
	const char* words[] = { "internal", "interval" };
	int conflictList[] = { 0,1 };
	int dictSize = sizeof(words) / sizeof(words[0]);
	char** dict = new char*[dictSize];
	for (int i = 0; i < dictSize; i++) {
		dict[i] = new char[MAX_WORD_SIZE + 1];
		memset(dict[i], 0, MAX_WORD_SIZE + 1);
		strcpy(dict[i], words[i]);
	}
	int r = FindCommPrefix(dict, conflictList, 2);
	EXPECT_EQ(r, 5);
}

TEST_F(ExamCodeTest, FindCommPrefixTest1) {
	const char* words[] = { "internal", "internal" };
	int conflictList[] = { 0,1 };
	int dictSize = sizeof(words) / sizeof(words[0]);
	char** dict = new char*[dictSize];
	for (int i = 0; i < dictSize; i++) {
		dict[i] = new char[MAX_WORD_SIZE + 1];
		memset(dict[i], 0, MAX_WORD_SIZE + 1);
		strcpy(dict[i], words[i]);
	}
	int r = FindCommPrefix(dict, conflictList, 2);
	EXPECT_EQ(r, 8);
}

TEST_F(ExamCodeTest, FindCommPrefixTest2) {
	const char* words[] = { "abcdefg","abccefg","abcckkg" };
	int conflictList[] = { 0,1,2 };
	int dictSize = sizeof(words) / sizeof(words[0]);
	char** dict = new char*[dictSize];
	for (int i = 0; i < dictSize; i++) {
		dict[i] = new char[MAX_WORD_SIZE + 1];
		memset(dict[i], 0, MAX_WORD_SIZE + 1);
		strcpy(dict[i], words[i]);
	}
	int r = FindCommPrefix(dict, conflictList, sizeof(conflictList) / sizeof(conflictList[0]));
	EXPECT_EQ(r, 3);
}
*/

/*
输入: ["like", "god", "internal", "me", "internet", "interval", "intension", "face", "intrusion"]
输出: ["l2e","god","internal","me","i6t","interval","inte4n","f2e","intr4n"]
*/
TEST_F(ExamCodeTest, wordsAbbreviationTest1) {
	const char* words[] = { "like", "god", "internal", "me", "internet", "interval", "intension", "face", "intrusion" };
	int dictSize = sizeof(words) / sizeof(words[0]);
	char** dict = new char*[dictSize];
	for (int i = 0; i < dictSize; i++) {
		dict[i] = new char[MAX_WORD_SIZE + 1];
		memset(dict[i], 0, MAX_WORD_SIZE + 1);
		strcpy(dict[i], words[i]);
	}
	
	int returnSize = 0;
	char** result = wordsAbbreviation(dict, dictSize, &returnSize);
	EXPECT_EQ(returnSize, dictSize);
	
	const char* abbrv[] = { "l2e","god","internal","me","i6t","interval","inte4n","f2e","intr4n" };
	for (int i = 0; i < dictSize; i++) {
		EXPECT_STREQ(abbrv[i], result[i]);
	}
}

/*
输入: ["abcdefg","abccefg","abcceft"]
输出: ["abcd2g","abcc2g","a5t"]
*/
TEST_F(ExamCodeTest, wordsAbbreviationTest2) {
	const char* words[] = { "abcdefg","abccefg","abcceft" };
	int dictSize = sizeof(words) / sizeof(words[0]);
	char** dict = new char*[dictSize];
	for (int i = 0; i < dictSize; i++) {
		dict[i] = new char[MAX_WORD_SIZE + 1];
		memset(dict[i], 0, MAX_WORD_SIZE + 1);
		strcpy(dict[i], words[i]);
	}

	int returnSize = 0;
	char** result = wordsAbbreviation(dict, dictSize, &returnSize);
	EXPECT_EQ(returnSize, dictSize);

	const char* abbrv[] = { "abcd2g","abcc2g","a5t" };
	for (int i = 0; i < dictSize; i++) {
		EXPECT_STREQ(abbrv[i], result[i]);
	}
}

/*
输入: ["abcdefg","abccefg","abcckkg"] 
输出: ["abcd2g","abccefg","abcckkg"]
*/
TEST_F(ExamCodeTest, wordsAbbreviationTest3) {
	const char* words[] = { "abcdefg","abccefg","abcckkg" };
	int dictSize = sizeof(words) / sizeof(words[0]);
	char** dict = new char*[dictSize];
	for (int i = 0; i < dictSize; i++) {
		dict[i] = new char[MAX_WORD_SIZE + 1];
		memset(dict[i], 0, MAX_WORD_SIZE + 1);
		strcpy(dict[i], words[i]);
	}

	int returnSize = 0;
	char** result = wordsAbbreviation(dict, dictSize, &returnSize);
	EXPECT_EQ(returnSize, dictSize);

	const char* abbrv[] = { "abcd2g","abccefg","abcckkg" };
	for (int i = 0; i < dictSize; i++) {
		EXPECT_STREQ(abbrv[i], result[i]);
	}
}

/*
输入: ["bbbbab","bbbaab","baaaab"]
输出: ["bbbbab","bbbaab","ba3b"]
*/
TEST_F(ExamCodeTest, wordsAbbreviationTest4) {
	const char* words[] = { "bbbbab","bbbaab","baaaab" };
	int dictSize = sizeof(words) / sizeof(words[0]);
	char** dict = new char*[dictSize];
	for (int i = 0; i < dictSize; i++) {
		dict[i] = new char[MAX_WORD_SIZE + 1];
		memset(dict[i], 0, MAX_WORD_SIZE + 1);
		strcpy(dict[i], words[i]);
	}

	int returnSize = 0;
	char** result = wordsAbbreviation(dict, dictSize, &returnSize);
	EXPECT_EQ(returnSize, dictSize);

	const char* abbrv[] = { "bbbbab","bbbaab","ba3b" };
	for (int i = 0; i < dictSize; i++) {
		EXPECT_STREQ(abbrv[i], result[i]);
	}
}

/*
输入: ["bbadabadccdabdadccdd","aacbbbacccacaadabcdc","ccdcccdcbccadadbdcdd","abdbcaacbaacabccadaa",
       "cbaaabddbbddcbbcbddb","addaadcdaabcccbddada","aaaabcbbcadabdaccdda","dbcabacdacdaaccdccdc",
	   "acdabbcdcabaaccdbbac","abbadcabdabcadcdccbc","ddbddbadacacacbcbaaa","dabaaababccaddbaacad",
	   "dbbdbcdcabbaacdccbdc","dcdcbbcccadbacdaddad","dacdbcdbaddabbbabbac","bdddacdcabbcccdbcdaa",
	   "abaababcccadabadbcdd","bbbccdbadcbaacadcacb","abddadccaaccccaacccd","dbbababacaacdbdbcdcb",
	   "cdadccadbdaaacbabbbc","adaaabbcabddadcacabb","bdbbbaadaddbbbddbabd","ddaccbdccadcaccabcbd",
	   "dbdacbbbacdbbddddbbd","bbaaadcccdbacdccdddd","cbdbbcddaacabcabbabd","bbacccdbdbddbabbbaba",
	   "cacabbaaaaaaabadbddc","daddaaccbadcacaadabc","adcdbddadabbdabcabdb","aabdacbdbacdddcbbbdc",
	   "bbcdbdbdcbacbccbbdaa","daadacbcbcbcddcdcbcc","daccabbdbddcddacbdcb","cbccacacabbcdbbcabac",
	   "bbdbcbbdbacabddbcbcb","acbbbcdbbdcddbccbbba","cbdabcdaccdbcddbbbcb","dabdbbcdcccdbdacbcca",
	   "cdccbdddbbdcadbcbcbd","cacccbccdcacdcbddcbd","bbcddabcdbcadcbcdaac","adddbcbdaacbabcddbcc",
	   "ccbbbbcaabccadbcdacd","cbbbbdaadaccdadccbad","caabaddbbacccaddcdcd","bbbcdbcddadabddcccbd",
	   "ccdadbcacdadbdbbacdb","cbcaddcadadcbcdabbdc","dcadcdbaabcacdddaaba","ccaadddcabdcbbdacdad",
	   "dacdadcbbbdddaabacaa","addbaddaabbddacbdbaa","adcabccccbaccdccadaa","cbaabdabdddcaaaabdac",
	   "dbcababcaaddbdacbdcc","bdaaaadcdbcacccccdac","baccadcdaabcbcdbabba","badccccddaabacdbcdac",
	   "dabcabbdadcdcadbcddb","abcdcbbaccdddadcaaba","aaaccabacbdbcadbabcb","ddbccbbbaccdabaacacb",
	   "bdacababadbadadbccbc","aacacadccabbcadbabac","bcbcddadaddbdbddddad","bcabddacadbaadcaddaa",
	   "ccdcbdcadacddaaacbab","ddcbdbabaddcacdadcaa","bcabddcdbbdabdbccbac","cbddcbccbcadacdaccbb",
	   "ddbcaddcdabccbbdcccd","cbadbbcacdccdddabadd","cdcbdcbddddcbccbadad","dcdacdbaacddbaaccaba",
	   "cccbddbbaddbcababcdb","dcbdbaddaabcdadcaaad","ddccbadacbdbcbccadcd","dcaccbddaccdabccbccb",
	   "bdcbddcbddcbbbbdabca","dcbddbbbacaacdacdbbc","abdbabbddbdacccbdbdd","cbaddbabdcbbbaadcdbb",
	   "dbacdbdcdcacaccbbabb","acdaccdababbbcdddbbd","badcccdabacadbdaabad","cdabbadbaccbadcbaacd",
	   "bdcaddbdccdcadaaabba","bccaaddbaabcbcacdcab","abaabacbcdcdbcadaacb","abbccddcbadaaaaadcdd",
	   "badbccdddbbbdcbdbddd","bcdbddcdcccbaabccbbd","bacabcdbcbabacdddddc","cbaabcbacdbcbdabcacb",
	   "ddbdadacadcaccbdbcdd","ccabbbbbdbcacbaacbbc","bccabcacdccccbdabcad","babbadcaddadabdbdcbc",
	   "ddcaacdcccbdbdadcaac","aacccddcbaddbacbaccc","adabadbcbdbcdaacbbdd","bbacaddcbaccbcbadcdb",
	   "badddadbddbbdbcaacda","aaccddddbddddaacbcaa","aabbcbdadcdcabcccadc","dacbdaabdccccbdddacd",
	   "dccbdddccdaacadbaabc","abacddbabdacacadbadc","abcbbddddbbdccacbabb","aacaacdaadcadaaccbcc",
	   "addbacdbcdabcadccdac","cbababbdccdbdbdacadb","babdbcbacdbadbadccaa","aaabcddbcdbacbdaabbd",
	   "dabcadaaabdbcaaacbbb","dcdcdacbcccbcabccdca","abbddccccdaaaabaccad","bcabbdacbcaaccdddddd",
	   "dacddcabcaddacbbbcaa","aabcbbbddabdbaabddbc","abcbdddbccbaaaaadcdb","cbabbdacdadaddbccaca",
	   "bcddbbdcdddbadbdbabc","bbdbdadbbbaccbadbdda","cccbbdbcadbbdccbdaaa","bbcbababbcdbadbaacda",
	   "adcdcddbcccbbbaaacdc","bbbdccdccdcdaacbdacb","bcbbacbccdadabddaada","dadadadaacaaccccbdac",
	   "abbbcddaaadbbcbcbdcd","dababccbbdadbadcaaad","bbcdccbdbdbbddcbacba","ccdaaababbbbdcaaabda",
	   "daaadaabaacaabdabbbd","abbbbbbcdbcddbacddcb","adddbdbbcbdbbcdaccca","ccbddabbdcdcaabbbdbb",
	   "dcddabddbaacbbbcbaca","bccaccadcabbaabaadaa","baadcbdcabcbbbcddccd","cbddcdcbddbccbaacabc",
	   "ddacabdbacbbabccadbd","daaddcadaccdbbdcdccd","abdaabcdbabbdbbcdcba","ccdbbcaabbdadbbdccdb",
	   "cadcddbbccadcdbdabcb","dcdcddbaabbddcbdaddb","cbcdbadcdcdaddcbcddd","ddadaadcbddadbbadccd",
	   "acdacaadcddbadbcdbdd","bbaadccddabcdadddbbb","caabadcbcdacdcbacbbd","badcbddccbdcdccbbbcd",
	   "aabcbddbdbcbacdaaada","abccdcbbacbbbacddcbd","cccbbbdabcbadcabaaab","acccbcbcbbbbaaddaccb",
	   "abdddbdaadcbcdcbbccc","abcdadacdcabdacddbdd","cdddcadadbddbcbbcdba","abdbadcacbcdaaabbacd",
	   "ccdaddabbacbbbcccaba","dddaacbddcbbbddacdbc","ddbbbdcdbddaaabcdaab","dbdabddacaadccaabbac",
	   "badddacadbdbacbddbcb","cdadcddaaacdaaaabdab","bccbadaccdbbdabddbab","ddaadabbddacacbdbcdb",
	   "addcbdbdbddbdaadcdaa","bbcabccadcdcbcdadcdd","bbaccccdbdacbcddacac","dbbaadabacabbbdcaddb",
	   "bcdbbaacbccaacdbaaaa","aaabcdadbaacbabdacbc","dbccbdacdbcbacdadaba","bdadcdcdbbcdcabdbbcc",
	   "cdbbbdaabddbccabdaac","baacabdccdcdccbcbdcc","bcbbbaaaddabdcddddcd","dcddacdddacccddacbdb",
	   "dcacdcbddccbbcaacbda","cbadbbbacabcddddcacc","dabbbdddbcddbccbabda","bbcacaaddbbabddbbdaa",
	   "cbaddabdabbcddadbaab","bbadcbbdbabddbabbcca","adbdcdddbabdaacdacab","bdaccaaddbaddbaabdcc",
	   "cbdcbacacdbbcbbccbbd","cdcabcccddbbcddccbdc","bddddcabbaabcbdbbabd","cdbcbabacacbcbcdbcbc",
	   "aadbacacbaadbbbcbdba","caadbbaddcddccbbabdb","aacbddbbbadddacdbdaa","bcadabdaadcacbcccbaa"]
输出: ["bbad15d","aacb15c","ccd16d","abdb15a","cbaaa14b","adda15a","aaa16a","dbcabac12c","ac17c",
	   "abb16c","ddb16a","dabaa14d","dbb16c","dcd16d","dac16c","bdd16a","aba16d","bbbc15b","abdd15d",
	   "dbbab14b","cda16c","ada16b","bdb16d","ddacc14d","db17d","bbaa15d","cbdb15d","bbac15a","ca17c",
	   "dadd15c","adc16b","aabd15c","bbcdb14a","daa16c","dac16b","cbcc15c","bbd16b","ac17a","cbda15b",
	   "dabd15a","cdcc15d","cac16d","bbc16c","addd15c","ccb16d","cbb16d","caabadd12d","bbb16d","ccda15b",
	   "cbca15c","dcad15a","cca16d","dacda14a","addb15a","adc16a","cbaa15c","dbcabab12c","bdaa15c","bac16a",
	   "bad16c","dabcab13b","abc16a","aa17b","ddbc15b","bdaca14c","aacac14c","bcbc15d","bcab15a","ccdc15b",
	   "ddc16a","bca16c","cbdd15b","ddbc15d","cba16d","cdcb15d","dcda15a","cccbd14b","dcb16d","ddc16d",
	   "dca16b","bdcb15a","dcb16c","abdbab13d","cbaddb13b","dba16b","acdacc13d","badcc14d","cda16d","bdca15a",
	   "bcca15b","aba16b","abbc15d","badb15d","bcd16d","bac16c","cbaab14b","ddbd15d","cc17c","bcc16d","bab16c",
	   "ddc16c","aacc15c","ad17d","bbac15b","bad16a","aacc15a","aabb15c","dac16d","dcc16c","aba16c","abcbb14b",
	   "aacaa14c","addb15c","cbab15b","bab16a","aa17d","dabcad13b","dcdc15a","abbd15d","bca16d","dacdd14a",
	   "aabc15c","abcbd14b","cb17a","bcd16c","bbd16a","ccc16a","bbcb15a","adc16c","bbbd15b","bcb16a","dada15c",
	   "abbb15d","dabab14d","bbcdc14a","ccdaa14a","daaa15d","abb16b","addd15a","ccb16b","dcdd15a","bcc16a","baa16d",
	   "cbd16c","ddaca14d","daad15d","abda15a","ccdb15b","cad16b","dcdc15b","cbc16d","ddad15d","acdaca13d","bbaa15b",
	   "caabadc12d","badcb14d","aab16a","abcc15d","cccbb14b","ac17b","abd16c","abcd15d","cd17a","abdbad13d","ccdad14a",
	   "ddd16c","ddbb15b","dbd16c","ba17b","cd17b","bccb15b","dda16b","addc15a","bbc16d","bba16c","dbbaa14b","bcd16a",
	   "aaa16c","db17a","bdad15c","cdbb15c","baa16c","bcbb15d","dcdd15b","dcac15a","cbad15c","dabb15a","bbca15a",
	   "cbadda13b","bbad15a","adb16b","bdacc14c","cbdc15d","cdc16c","bdd16d","cdbc15c","aad16a","caa16b","aacb15a","bcad15a"]]
*/
TEST_F(ExamCodeTest, wordsAbbreviationTest5) {
	const char* words[] = { "bbadabadccdabdadccdd","aacbbbacccacaadabcdc","ccdcccdcbccadadbdcdd","abdbcaacbaacabccadaa",
	   "cbaaabddbbddcbbcbddb","addaadcdaabcccbddada","aaaabcbbcadabdaccdda","dbcabacdacdaaccdccdc",
	   "acdabbcdcabaaccdbbac","abbadcabdabcadcdccbc","ddbddbadacacacbcbaaa","dabaaababccaddbaacad",
	   "dbbdbcdcabbaacdccbdc","dcdcbbcccadbacdaddad","dacdbcdbaddabbbabbac","bdddacdcabbcccdbcdaa",
	   "abaababcccadabadbcdd","bbbccdbadcbaacadcacb","abddadccaaccccaacccd","dbbababacaacdbdbcdcb",
	   "cdadccadbdaaacbabbbc","adaaabbcabddadcacabb","bdbbbaadaddbbbddbabd","ddaccbdccadcaccabcbd",
	   "dbdacbbbacdbbddddbbd","bbaaadcccdbacdccdddd","cbdbbcddaacabcabbabd","bbacccdbdbddbabbbaba",
	   "cacabbaaaaaaabadbddc","daddaaccbadcacaadabc","adcdbddadabbdabcabdb","aabdacbdbacdddcbbbdc",
	   "bbcdbdbdcbacbccbbdaa","daadacbcbcbcddcdcbcc","daccabbdbddcddacbdcb","cbccacacabbcdbbcabac",
	   "bbdbcbbdbacabddbcbcb","acbbbcdbbdcddbccbbba","cbdabcdaccdbcddbbbcb","dabdbbcdcccdbdacbcca",
	   "cdccbdddbbdcadbcbcbd","cacccbccdcacdcbddcbd","bbcddabcdbcadcbcdaac","adddbcbdaacbabcddbcc",
	   "ccbbbbcaabccadbcdacd","cbbbbdaadaccdadccbad","caabaddbbacccaddcdcd","bbbcdbcddadabddcccbd",
	   "ccdadbcacdadbdbbacdb","cbcaddcadadcbcdabbdc","dcadcdbaabcacdddaaba","ccaadddcabdcbbdacdad",
	   "dacdadcbbbdddaabacaa","addbaddaabbddacbdbaa","adcabccccbaccdccadaa","cbaabdabdddcaaaabdac",
	   "dbcababcaaddbdacbdcc","bdaaaadcdbcacccccdac","baccadcdaabcbcdbabba","badccccddaabacdbcdac",
	   "dabcabbdadcdcadbcddb","abcdcbbaccdddadcaaba","aaaccabacbdbcadbabcb","ddbccbbbaccdabaacacb",
	   "bdacababadbadadbccbc","aacacadccabbcadbabac","bcbcddadaddbdbddddad","bcabddacadbaadcaddaa",
	   "ccdcbdcadacddaaacbab","ddcbdbabaddcacdadcaa","bcabddcdbbdabdbccbac","cbddcbccbcadacdaccbb",
	   "ddbcaddcdabccbbdcccd","cbadbbcacdccdddabadd","cdcbdcbddddcbccbadad","dcdacdbaacddbaaccaba",
	   "cccbddbbaddbcababcdb","dcbdbaddaabcdadcaaad","ddccbadacbdbcbccadcd","dcaccbddaccdabccbccb",
	   "bdcbddcbddcbbbbdabca","dcbddbbbacaacdacdbbc","abdbabbddbdacccbdbdd","cbaddbabdcbbbaadcdbb",
	   "dbacdbdcdcacaccbbabb","acdaccdababbbcdddbbd","badcccdabacadbdaabad","cdabbadbaccbadcbaacd",
	   "bdcaddbdccdcadaaabba","bccaaddbaabcbcacdcab","abaabacbcdcdbcadaacb","abbccddcbadaaaaadcdd",
	   "badbccdddbbbdcbdbddd","bcdbddcdcccbaabccbbd","bacabcdbcbabacdddddc","cbaabcbacdbcbdabcacb",
	   "ddbdadacadcaccbdbcdd","ccabbbbbdbcacbaacbbc","bccabcacdccccbdabcad","babbadcaddadabdbdcbc",
	   "ddcaacdcccbdbdadcaac","aacccddcbaddbacbaccc","adabadbcbdbcdaacbbdd","bbacaddcbaccbcbadcdb",
	   "badddadbddbbdbcaacda","aaccddddbddddaacbcaa","aabbcbdadcdcabcccadc","dacbdaabdccccbdddacd",
	   "dccbdddccdaacadbaabc","abacddbabdacacadbadc","abcbbddddbbdccacbabb","aacaacdaadcadaaccbcc",
	   "addbacdbcdabcadccdac","cbababbdccdbdbdacadb","babdbcbacdbadbadccaa","aaabcddbcdbacbdaabbd",
	   "dabcadaaabdbcaaacbbb","dcdcdacbcccbcabccdca","abbddccccdaaaabaccad","bcabbdacbcaaccdddddd",
	   "dacddcabcaddacbbbcaa","aabcbbbddabdbaabddbc","abcbdddbccbaaaaadcdb","cbabbdacdadaddbccaca",
	   "bcddbbdcdddbadbdbabc","bbdbdadbbbaccbadbdda","cccbbdbcadbbdccbdaaa","bbcbababbcdbadbaacda",
	   "adcdcddbcccbbbaaacdc","bbbdccdccdcdaacbdacb","bcbbacbccdadabddaada","dadadadaacaaccccbdac",
	   "abbbcddaaadbbcbcbdcd","dababccbbdadbadcaaad","bbcdccbdbdbbddcbacba","ccdaaababbbbdcaaabda",
	   "daaadaabaacaabdabbbd","abbbbbbcdbcddbacddcb","adddbdbbcbdbbcdaccca","ccbddabbdcdcaabbbdbb",
	   "dcddabddbaacbbbcbaca","bccaccadcabbaabaadaa","baadcbdcabcbbbcddccd","cbddcdcbddbccbaacabc",
	   "ddacabdbacbbabccadbd","daaddcadaccdbbdcdccd","abdaabcdbabbdbbcdcba","ccdbbcaabbdadbbdccdb",
	   "cadcddbbccadcdbdabcb","dcdcddbaabbddcbdaddb","cbcdbadcdcdaddcbcddd","ddadaadcbddadbbadccd",
	   "acdacaadcddbadbcdbdd","bbaadccddabcdadddbbb","caabadcbcdacdcbacbbd","badcbddccbdcdccbbbcd",
	   "aabcbddbdbcbacdaaada","abccdcbbacbbbacddcbd","cccbbbdabcbadcabaaab","acccbcbcbbbbaaddaccb",
	   "abdddbdaadcbcdcbbccc","abcdadacdcabdacddbdd","cdddcadadbddbcbbcdba","abdbadcacbcdaaabbacd",
	   "ccdaddabbacbbbcccaba","dddaacbddcbbbddacdbc","ddbbbdcdbddaaabcdaab","dbdabddacaadccaabbac",
	   "badddacadbdbacbddbcb","cdadcddaaacdaaaabdab","bccbadaccdbbdabddbab","ddaadabbddacacbdbcdb",
	   "addcbdbdbddbdaadcdaa","bbcabccadcdcbcdadcdd","bbaccccdbdacbcddacac","dbbaadabacabbbdcaddb",
	   "bcdbbaacbccaacdbaaaa","aaabcdadbaacbabdacbc","dbccbdacdbcbacdadaba","bdadcdcdbbcdcabdbbcc",
	   "cdbbbdaabddbccabdaac","baacabdccdcdccbcbdcc","bcbbbaaaddabdcddddcd","dcddacdddacccddacbdb",
	   "dcacdcbddccbbcaacbda","cbadbbbacabcddddcacc","dabbbdddbcddbccbabda","bbcacaaddbbabddbbdaa",
	   "cbaddabdabbcddadbaab","bbadcbbdbabddbabbcca","adbdcdddbabdaacdacab","bdaccaaddbaddbaabdcc",
	   "cbdcbacacdbbcbbccbbd","cdcabcccddbbcddccbdc","bddddcabbaabcbdbbabd","cdbcbabacacbcbcdbcbc",
	   "aadbacacbaadbbbcbdba","caadbbaddcddccbbabdb","aacbddbbbadddacdbdaa","bcadabdaadcacbcccbaa" };
	int dictSize = sizeof(words) / sizeof(words[0]);
	char** dict = new char*[dictSize];
	for (int i = 0; i < dictSize; i++) {
		dict[i] = new char[MAX_WORD_SIZE + 1];
		memset(dict[i], 0, MAX_WORD_SIZE + 1);
		strcpy(dict[i], words[i]);
	}

	int returnSize = 0;
	char** result = wordsAbbreviation(dict, dictSize, &returnSize);
	EXPECT_EQ(returnSize, dictSize);

	const char* abbrv[] = { "bbad15d","aacb15c","ccd16d","abdb15a","cbaaa14b","adda15a","aaa16a","dbcabac12c","ac17c",
	   "abb16c","ddb16a","dabaa14d","dbb16c","dcd16d","dac16c","bdd16a","aba16d","bbbc15b","abdd15d",
	   "dbbab14b","cda16c","ada16b","bdb16d","ddacc14d","db17d","bbaa15d","cbdb15d","bbac15a","ca17c",
	   "dadd15c","adc16b","aabd15c","bbcdb14a","daa16c","dac16b","cbcc15c","bbd16b","ac17a","cbda15b",
	   "dabd15a","cdcc15d","cac16d","bbc16c","addd15c","ccb16d","cbb16d","caabadd12d","bbb16d","ccda15b",
	   "cbca15c","dcad15a","cca16d","dacda14a","addb15a","adc16a","cbaa15c","dbcabab12c","bdaa15c","bac16a",
	   "bad16c","dabcab13b","abc16a","aa17b","ddbc15b","bdaca14c","aacac14c","bcbc15d","bcab15a","ccdc15b",
	   "ddc16a","bca16c","cbdd15b","ddbc15d","cba16d","cdcb15d","dcda15a","cccbd14b","dcb16d","ddc16d",
	   "dca16b","bdcb15a","dcb16c","abdbab13d","cbaddb13b","dba16b","acdacc13d","badcc14d","cda16d","bdca15a",
	   "bcca15b","aba16b","abbc15d","badb15d","bcd16d","bac16c","cbaab14b","ddbd15d","cc17c","bcc16d","bab16c",
	   "ddc16c","aacc15c","ad17d","bbac15b","bad16a","aacc15a","aabb15c","dac16d","dcc16c","aba16c","abcbb14b",
	   "aacaa14c","addb15c","cbab15b","bab16a","aa17d","dabcad13b","dcdc15a","abbd15d","bca16d","dacdd14a",
	   "aabc15c","abcbd14b","cb17a","bcd16c","bbd16a","ccc16a","bbcb15a","adc16c","bbbd15b","bcb16a","dada15c",
	   "abbb15d","dabab14d","bbcdc14a","ccdaa14a","daaa15d","abb16b","addd15a","ccb16b","dcdd15a","bcc16a","baa16d",
	   "cbd16c","ddaca14d","daad15d","abda15a","ccdb15b","cad16b","dcdc15b","cbc16d","ddad15d","acdaca13d","bbaa15b",
	   "caabadc12d","badcb14d","aab16a","abcc15d","cccbb14b","ac17b","abd16c","abcd15d","cd17a","abdbad13d","ccdad14a",
	   "ddd16c","ddbb15b","dbd16c","ba17b","cd17b","bccb15b","dda16b","addc15a","bbc16d","bba16c","dbbaa14b","bcd16a",
	   "aaa16c","db17a","bdad15c","cdbb15c","baa16c","bcbb15d","dcdd15b","dcac15a","cbad15c","dabb15a","bbca15a",
	   "cbadda13b","bbad15a","adb16b","bdacc14c","cbdc15d","cdc16c","bdd16d","cdbc15c","aad16a","caa16b","aacb15a","bcad15a" };
	for (int i = 0; i < dictSize; i++) {
		EXPECT_STREQ(abbrv[i], result[i]);
	}
}
