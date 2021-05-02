# include <string>
# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

/*
给定一个整数 n，返回所有由 1 ... n 为节点所组成的二叉搜索树的个数
*/

class Solution {
public:
	int numTrees(int n) {
		// Method 1 直接求递推式

		/*
		G(n)表示序列长度为n的BST个数 F(i,n)表示以i为根,序列长度为n的BST个数
		G(n) = \sum_{i=1}^{n} F(i,n) 
		对于F(i,n) 有 F(i,n) = G(i-1)*G(n-i) 其中G(i-1)为左子树的所有可能 G(n-i)为右子树所有可能 二者求笛卡尔积
		代入G(n)有G(n) = \sum_{i=1}^{n} G(i-1)*G(n-i) 即为递推式
		*/

		vector<int> G(n + 1, 0);
		G[0] = 1; G[1] = 1; // 边界情况
		for (int i = 2; i <= n; i++) {
			for (int j = 1; j <= i; j++) {
				G[i] += G[j - 1] * G[i - j];
			}
		}
		return G[n];
	}

	int numTrees(int n) {
		// Method 2 直接用卡塔兰数

		/*
		序列长度为n的BST个数为卡塔兰数
		递推式为 C_0=1 C_{n+1} = 2*C_n*\frac{2*n+1}{n+2}
		*/

		long long C = 1;
		for (int i = 0; i <= n - 1; i++) C = 2 * C * (2 * i + 1) / (i + 2);
		return int(C);
	}
};