﻿# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

/*
We can scramble a string s to get a string t using the following algorithm:

If the length of the string is 1, stop.

If the length of the string is > 1, do the following:

Split the string into two non-empty substrings at a random index, i.e., if the string is s, divide it to x and y where s = x + y.

Randomly decide to swap the two substrings or to keep them in the same order. i.e., after this step, s may become s = x + y or s = y + x.

Apply step 1 recursively on each of the two substrings x and y.

Given two strings s1 and s2 of the same length, return true if s2 is a scrambled string of s1, otherwise, return false.
*/

class Solution {
public:
	bool isScramble(string s1, string s2) {
		// 递归 286/288 超时
		int len = s1.size();

		if (s1.size() != s2.size()) return false;
		if (s1 == s2) return true;

		
		vector<int> letters(26);
		for (int i = 0; i < len; i++) {
			letters[s1[i] - 'a']++;
			letters[s2[i] - 'a']--;
		}
		for (int i = 0; i < 26; i++) {
			if (letters[i] != 0) return false;
		}


		for (int i = 0; i < len - 1; i++) {
			if (isScramble(s1.substr(0,i+1), s2.substr(0,i+1)) && isScramble(s1.substr(i+1,len-i-1), s2.substr(i+1,len-i-1))){
				return true;
			}
			if (isScramble(s1.substr(0, i + 1), s2.substr(len - 1 - i, i + 1)) && isScramble(s1.substr(i + 1, len - i - 1), s2.substr(0, len - i - 1))) {
				return true;
			}
		}
		return false;
	}
};