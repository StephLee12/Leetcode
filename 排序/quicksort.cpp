# include <iostream>
# include <vector>

using namespace std;

// 快排 递归实习

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
	int pivot = nums[low]; // 将表中的第一个元素设为枢轴 进行划分

	/*
	注意 这里因为将表中第一个元素作为枢轴
	因此 交替搜索时要首先从右边搜索小于枢轴的替换掉
	一趟快排 实际上就是双指针交替搜索和替换的过程 要注意替换的顺序
	*/
	while (low < high) {
		// 将比枢轴小的元素移到左端
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
	nums[low] = pivot; // i==j的位置即为枢轴变量的位置
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