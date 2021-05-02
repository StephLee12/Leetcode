# include <iostream>
# include <vector>

using namespace std;

// 二路归排

void MergeSort(vector<int>& nums, int low, int high);
void Merge(vector<int>& nums, int low, int mid, int high);

void MergeSort(vector<int>& nums, int low, int high) {
	if (low < high) {
		int mid = (low + high) / 2;
		MergeSort(nums, low, mid); // 对左半序列归并
		MergeSort(nums,mid+1,high); // 对右半序列归并
		Merge(nums, low, mid, high); // 归并左右序列
	}
}

void Merge(vector<int>& nums, int low, int mid, int high) {
	vector<int> store(nums.size());
	// 复制nums[low:high]
	for (int i = low; i <= high; i++) {
		store[i] = nums[i];
	}

	int i = 0;
	int j = 0;
	int p = 0;
	// 指针p从low开始遍历 重新给nums[low:high]赋值 
	// 双指针 左指针low->mid 右指针 mid+1->high
	for (i = low, j = mid + 1, p = i; i <= mid && j <= high; p++) {
		if (store[i] <= store[j]){
			nums[p] = store[i++];
		}
		else {
			nums[p] = store[j++];
		}
	}
	// 可能会出现 nums[low:mid]或nums[mid+1:high]某一个遍历完 但另一个没有
	while (i <= mid) {
		nums[p++] = store[i++]; // nums[mid+1:high]已经遍历完
	}
	while (j <= high) {
		nums[p++] = store[j++]; // nums[low:mid]已经遍历完
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
	