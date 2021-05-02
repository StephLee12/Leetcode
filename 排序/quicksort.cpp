# include <iostream>
# include <vector>

using namespace std;

// ���� �ݹ�ʵϰ

void QuickSort(vector<int>& nums, int low, int high);
int Partition(vector<int>& nums, int low, int high);
void QuickSort(vector<int>& nums, int low, int high) {
	if (low < high) {
		int pivot_pos = Partition(nums, low, high);
		QuickSort(nums, low, pivot_pos);
		QuickSort(nums, pivot_pos + 1, high);
	}
}

int Partition(vector<int>& nums, int low, int high) {
	int pivot = nums[low]; // �����еĵ�һ��Ԫ����Ϊ���� ���л���

	/*
	ע�� ������Ϊ�����е�һ��Ԫ����Ϊ����
	��� ��������ʱҪ���ȴ��ұ�����С��������滻��
	һ�˿��� ʵ���Ͼ���˫ָ�뽻���������滻�Ĺ��� Ҫע���滻��˳��
	*/
	while (low < high) {
		// ��������С��Ԫ���Ƶ����
		while (low<high && nums[high]>=pivot)
		{
			high--;
		}
		nums[low] = nums[high];
		while (low < high && nums[low] <= pivot)
		{
			low++;
		}
		nums[high] = nums[low];
	}
	nums[low] = pivot; // i==j��λ�ü�Ϊ���������λ��
	return low;
}

// test algorithm
int main() {
	vector<int> test{ 49,38,65,97,76,13,27 };
	QuickSort(test, 0, test.size() - 1);
	for (int i = 0; i <= test.size() - 1; i++) {
		cout << test[i] << " ";
	}

	return 0;
}