# include <iostream>
# include <vector>
# include <algorithm>

using namespace std;


/*
��Ŀ������
������ intervals ��ʾ���ɸ�����ļ��ϣ����е�������Ϊ intervals[i] = [start_i, end_i] 
����ϲ������ص������䣬������һ�����ص����������飬��������ǡ�ø��������е���������
*/

class Solution {
public:
	vector<vector<int>> merge(vector<vector<int>>& intervals) {
		// �Ȱ�������ĵ�һ��Ԫ�ض�intervals����
		int len = intervals.size(); // ��ά����ĳ���

		// �������
		if (len == 1) {
			return intervals;
		}

		vector<vector<int>> res; // ���ؽ��

		// ��ߣһ����� Ҳ��ֱ����sort()����
		QuickSort(intervals, 0, len - 1); 

		int l_p = 0; // ��ָ��
		int r_p = 1; // ��ָ��

		//˫ָ������
		while (r_p <= len - 1) {
			// ����������˾�Ϊintervals[l_p][0]��Ԫ�� ����������Ҷ˵����ֵ
			int max_r = intervals[l_p][1];
			while (r_p <= len-1 && intervals[r_p][0] == intervals[l_p][0]) {
				if (intervals[r_p][1] > max_r){
					max_r = intervals[r_p][1];
				}
				r_p++;
			}
			// Ҫ�ж�r_p�Ƿ�Խ��
			if (r_p > len - 1) {
				// ���r_pԽ���� ˵����l_p��r_p������˵�ֵ�����
				// ֱ�ӻ�ȡ�����Ҷ����ֵ ���������� ����ѭ��
				intervals[l_p][1] = max_r;
				res.push_back(intervals[l_p]);
				break;
			}

			// ���û��Խ��
			// �Ƚϵ�ǰr_pλ�õ�������˺͵�ǰ�����Ҷ����ֵ
			if (intervals[r_p][0] > max_r) {
				// ��ǰr_pλ�õ�������� ���� ��ǰ�����Ҷ����ֵ
				// ���Ժϲ���������(l_pΪ�������) ����������
				intervals[l_p][1] = max_r;
				res.push_back(intervals[l_p]);
				l_p=r_p; // ����l_pָ��
				// r_p++;
			}
			else {
				// ��ǰr_pλ�õ�������� С�� ��ǰ�����Ҷ����ֵ
				max_r = max(intervals[r_p][1], max_r);
				// �ϲ�����
				// ע�⣡��ʱ���ܼ��������� ����intervals[r_p]��ֵ
				intervals[r_p][0] = intervals[l_p][0];
				intervals[r_p][1] = max_r;
				l_p = r_p; // ����l_pָ��
			}
		}

		return res;
		
	}

	// ����
	void QuickSort(vector<vector<int>>& intervals, int low, int high) {
		if (low < high) {
			// ���������λ��
			int pivot_pos = Partition(intervals, low, high);
			QuickSort(intervals, low, pivot_pos); // �������ݹ�
			QuickSort(intervals, pivot_pos + 1, high); // �����Ҳ�ݹ�
		}
	}

	int Partition(vector<vector<int>>& intervals, int low, int high) {
		vector<int> pivot = intervals[low]; // ����intervals[low:high]�ĵ�һ��Ԫ��Ϊ����

		while (low < high) {
			// ��ָ���������� �ҵ�С�������Ԫ��
			while (low < high && intervals[high][0] >= pivot[0]) {
				high--;
			}
			intervals[low] = intervals[high];
			// ��ָ���������� �ҵ����������Ԫ��
			while (low < high && intervals[low][0] <= pivot[0]) {
				low++;
			}
			intervals[high] = intervals[low];
		}
		// ���ȷ�������λ��
		intervals[low] = pivot;
		return low;

	}
};

int main() {
	Solution obj;
	vector<vector<int>> res;
	vector<vector<int>> vec(4, vector<int>(2));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 2; j++) {
			cin >> vec[i][j];
		}
	}
	res = obj.merge(vec);
	return 0;
}