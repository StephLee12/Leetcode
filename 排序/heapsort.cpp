# include <vector>	
# include <iostream>
# include <algorithm>

using namespace std;

// ���� ����ֱ�������ȶ���ʵ��
// ����һ����ȫ������ 
// �󶥶ѡ���ÿ������ֵ��>=�亢�ӽ���ֵ С���ѡ���ÿ������ֵ��<=�亢�ӽ���ֵ

vector<int> HeapSort(vector<int>& nums,int len);
void BuildMaxHeap(vector<int>& nums, int len);
void HeapAdjust(vector<int>& nums, int root_pos,int len);

void HeapAdjust(vector<int>& nums,int root_pos ,int len) {

	for (int i = 2 * root_pos; i <= len - 1; i *= 2) {
		// ��root_pos��������С���Һ��� �ƶ����Һ���
		if (i + 1 <= len - 1 && nums[i] < nums[i + 1]) {
			i++;
		}
		// �жϵ�ǰ������root_posֵ�Ĵ�С
		if (nums[i] <= nums[root_pos]) {
			// ����С�ڸ���� ˵����ǰ����Ҫ����
			break;
		}
		else {
			// �����������ӽ���ֵ
			swap(nums[i], nums[root_pos]);
			root_pos = i; //root_pos�ƶ�����iΪ������������������
		}
	}
}

void BuildMaxHeap(vector<int>& nums, int len) {
	// len��������ȫ������ ���һ������ǵ�n/2(����ȡ��)���ĺ���
	// �������� ���ݸ���㲻�ϵ�������
	for (int i = len / 2; i >= 0; i--) {
		HeapAdjust(nums, i, len); // �����һ�����ĸ���� ���� ���ϵ�����
	}
}

vector<int> HeapSort(vector<int>& nums, int len) {
	vector<int> res(len);
	BuildMaxHeap(nums, len); // �Ƚ���
	for (int i = len - 1; i >= 0; i--) {
		swap(nums[i], nums[0]); // �����Ѷ���� �� �����һ�����
		res[i] = nums.back(); // ��öѶ����
		nums.pop_back(); // ɾ���Ѷ����
		HeapAdjust(nums, 0, i); // ������
	}
	return res;
}

// test algorithm

int main() {
	vector<int> test{ 49,38,65,97,76,13,27 };
	vector<int> res = HeapSort(test, test.size());
	for (int i = 0; i <= res.size() - 1; i++) {
		cout << res[i] << " ";
	}

	return 0;
}