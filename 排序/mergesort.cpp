# include <iostream>
# include <vector>

using namespace std;

// ��·����

void MergeSort(vector<int>& nums, int low, int high);
void Merge(vector<int>& nums, int low, int mid, int high);

void MergeSort(vector<int>& nums, int low, int high) {
	if (low < high) {
		int mid = (low + high) / 2;
		MergeSort(nums, low, mid); // ��������й鲢
		MergeSort(nums,mid+1,high); // ���Ұ����й鲢
		Merge(nums, low, mid, high); // �鲢��������
	}
}

void Merge(vector<int>& nums, int low, int mid, int high) {
	vector<int> store(nums.size());
	// ����nums[low:high]
	for (int i = low; i <= high; i++) {
		store[i] = nums[i];
	}

	int i = 0;
	int j = 0;
	int p = 0;
	// ָ��p��low��ʼ���� ���¸�nums[low:high]��ֵ 
	// ˫ָ�� ��ָ��low->mid ��ָ�� mid+1->high
	for (i = low, j = mid + 1, p = i; i <= mid && j <= high; p++) {
		if (store[i] <= store[j]){
			nums[p] = store[i++];
		}
		else {
			nums[p] = store[j++];
		}
	}
	// ���ܻ���� nums[low:mid]��nums[mid+1:high]ĳһ�������� ����һ��û��
	while (i <= mid) {
		nums[p++] = store[i++]; // nums[mid+1:high]�Ѿ�������
	}
	while (j <= high) {
		nums[p++] = store[j++]; // nums[low:mid]�Ѿ�������
	}
}

// test algorithm
int main() {
	vector<int> test{ 49,38,65,97,76,13,27 };
	MergeSort(test, 0, test.size() - 1);
	for (int i = 0; i <= test.size() - 1; i++) {
		cout << test[i] << " ";
	}

	return 0;
}
	