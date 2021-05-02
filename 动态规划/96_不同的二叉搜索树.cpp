# include <string>
# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;

/*
����һ������ n������������ 1 ... n Ϊ�ڵ�����ɵĶ����������ĸ���
*/

class Solution {
public:
	int numTrees(int n) {
		// Method 1 ֱ�������ʽ

		/*
		G(n)��ʾ���г���Ϊn��BST���� F(i,n)��ʾ��iΪ��,���г���Ϊn��BST����
		G(n) = \sum_{i=1}^{n} F(i,n) 
		����F(i,n) �� F(i,n) = G(i-1)*G(n-i) ����G(i-1)Ϊ�����������п��� G(n-i)Ϊ���������п��� ������ѿ�����
		����G(n)��G(n) = \sum_{i=1}^{n} G(i-1)*G(n-i) ��Ϊ����ʽ
		*/

		vector<int> G(n + 1, 0);
		G[0] = 1; G[1] = 1; // �߽����
		for (int i = 2; i <= n; i++) {
			for (int j = 1; j <= i; j++) {
				G[i] += G[j - 1] * G[i - j];
			}
		}
		return G[n];
	}

	int numTrees(int n) {
		// Method 2 ֱ���ÿ�������

		/*
		���г���Ϊn��BST����Ϊ��������
		����ʽΪ C_0=1 C_{n+1} = 2*C_n*\frac{2*n+1}{n+2}
		*/

		long long C = 1;
		for (int i = 0; i <= n - 1; i++) C = 2 * C * (2 * i + 1) / (i + 2);
		return int(C);
	}
};