# include <iostream>
# include <vector>
# include <algorithm>
# include <queue>

using namespace std;

/*
���� n ���Ǹ�������ʾÿ�����Ϊ 1 �����ӵĸ߶�ͼ�����㰴�����е����ӣ�����֮���ܽӶ�����ˮ
*/

class Solution {
public:
	int trap(vector<int>& height) {
		
		// Method 1 ��̬�滮  trap_v2()�Ż�����
		if (height.empty()) return 0;

		int len = height.size();
		// dp����ĺ��� dp[i] ������iΪ�ұ߽�Ľ�ˮ����
		vector<int> dp(len, 0);
		int max_height = height[0]; // ��¼height[i]�����ߵ����ӵĸ߶�
		int max_pos = 0; // ��¼height[i]�����ߵ����ӵ�λ��

		for (int i = 1; i < len; i++) {
			if (height[i - 1] >= height[i]) {
				// �����ǰ���Ӹ߶�<=ǰһ�����Ӹ߶�
				dp[i] = dp[i - 1];
			}
			else {
				// �����ǰ���Ӹ߶�>ǰһ�����Ӹ߶�

				int rain = 0;
				if (height[i] >= max_height) {
					// �����ǰ���Ӹ߶ȱ�������������ӻ���
					// ��max_height��Ϊʢˮ�����Ŀ� ����max_pos:i�Ĵ�ˮ��
					rain = max_height * (i - max_pos - 1);
					for (int j = max_pos + 1; j < i; j++) {
						rain -= height[j];
					}
					dp[i] = dp[max_pos] + rain; // ״̬ת��

					// ����max_height��max_pos
					max_height = height[i];
					max_pos = i;
				}
				else {
					// ��ǰ���Ӹ߶�û��max_height��
					// ��height[i]��Ϊʢˮ�����Ŀ� �������� ֻҪ��������height[i]�ߵ����Ӿ�ֹͣ �����㴢ˮ��
					for (int j = i - 1; j >= 0; j--) {
						if (height[j] >= height[i]) {
							rain += (height[i] * (i - j - 1));
							dp[i] = dp[j] + rain;
							break;
						}
						else {
							rain -= height[j];
						}
					}
				}

			}

		}

		return dp[len - 1];
	}

	int trap_v2(vector<int>& height) {
		// ��̬�滮 δ�Ż�
		if (height.empty()) return 0;

		int len = height.size();
		// dp����ĺ��� dp[i] ������iΪ�ұ߽�Ľ�ˮ����
		vector<int> dp(len, 0);

		for (int i = 1; i < len; i++) {
			if (height[i - 1] >= height[i]) {
				// �����ǰ���Ӹ߶�<=ǰһ�����Ӹ߶�
				dp[i] = dp[i - 1];
			}
			else {
				// ����������û�бȵ�ǰ���Ӹ߶ȸ��ߵ�(�����)
				queue<int> que; // ���� �洢�������������Ӹ߶�
				que.push(height[i - 1]);

				int max_height = height[i - 1]; // ��¼height[i]�����ߵ����ӵĸ߶�
				int max_pos = i - 1; // ��¼height[i]�����ߵ����ӵ�λ�� ����ǰ�ڶ���
				int rain = 0; // �����ڴ�ˮ��
				bool find_flag = false;
				for (int p = i - 2; p >= 0; p--) {
					if (height[p] >= height[i]) {
						// height[i]�����ڸ���(�����)������

						// ���㵱ǰջ�ڵĴ�ˮ��
						rain = height[i] * que.size();
						while (!que.empty()) {
							rain -= que.front();
							que.pop();
						}

						dp[i] = rain + dp[p]; // ״̬ת��
						find_flag = true; // �ҵ�Ŀ������
						break;
					}
					else {
						que.push(height[p]);
						if (height[p] > max_height) {
							max_height = height[p];
							max_pos = p;
						}
					}
				}

				// ���û�ҵ���height[i]��(�����)������ ����ڶ��ߵ�height[i]�Ĵ�ˮ��
				if (!find_flag) {
					rain = max_height * (i - max_pos - 1);
					for (int p = 0; p < i - max_pos - 1; p++) {
						rain -= que.front();
						que.pop();
					}
					dp[i] = dp[max_pos] + rain;
				}

			}

		}

		return dp[len - 1];
	}

	// Method 2 ����ջ
	int trap_v2(vector<int>& height) {

	}
};

int main() {
	Solution obj;
	vector<int> test(12, 0);
	for (int i = 0; i < 12; i++) {
		cin >> test[i];
	}
	
	return obj.trap(test);
}