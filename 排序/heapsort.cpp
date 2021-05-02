# include <vector>	
# include <iostream>
# include <algorithm>

using namespace std;

// 堆排 可以直接用优先队列实现
// 堆是一种完全二叉树 
// 大顶堆——每个结点的值都>=其孩子结点的值 小顶堆——每个结点的值都<=其孩子结点的值

vector<int> HeapSort(vector<int>& nums,int len);
void BuildMaxHeap(vector<int>& nums, int len);
void HeapAdjust(vector<int>& nums, int root_pos,int len);

void HeapAdjust(vector<int>& nums,int root_pos ,int len) {

	for (int i = 2 * root_pos; i <= len - 1; i *= 2) {
		// 若root_pos结点的左孩子小于右孩子 移动到右孩子
		if (i + 1 <= len - 1 && nums[i] < nums[i + 1]) {
			i++;
		}
		// 判断当前孩子与root_pos值的大小
		if (nums[i] <= nums[root_pos]) {
			// 孩子小于根结点 说明当前不需要调整
			break;
		}
		else {
			// 交换根结点和子结点的值
			swap(nums[i], nums[root_pos]);
			root_pos = i; //root_pos移动到以i为根结点的子树继续调整
		}
	}
}

void BuildMaxHeap(vector<int>& nums, int len) {
	// len个结点的完全二叉树 最后一个结点是第n/2(向下取整)结点的孩子
	// 从下向上 根据根结点不断调整子树
	for (int i = len / 2; i >= 0; i--) {
		HeapAdjust(nums, i, len); // 从最后一个结点的根结点 向上 不断调整堆
	}
}

vector<int> HeapSort(vector<int>& nums, int len) {
	vector<int> res(len);
	BuildMaxHeap(nums, len); // 先建堆
	for (int i = len - 1; i >= 0; i--) {
		swap(nums[i], nums[0]); // 交换堆顶结点 和 堆最后一个结点
		res[i] = nums.back(); // 获得堆顶结点
		nums.pop_back(); // 删除堆顶结点
		HeapAdjust(nums, 0, i); // 调整堆
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