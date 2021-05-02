# include <iostream>
# include <vector>
# include <algorithm>
# include <unordered_map>
# include <unordered_set>
# include <queue>

using namespace std;

/*
你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。

在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] 
表示如果要学习课程 ai 则 必须 先学习课程  bi 。

例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false

*/

class Solution {
public:
	bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
		
		// 不能有环
		// 拓扑排序 DAG（有向无环图）
		// 思想就是从入度为0的结点(即源点开始搜索)
		
		// BFS
		if (prerequisites.size() == 0 || numCourses == 1) return true;


		unordered_map<int, vector<int>> adj_table; // 构建图的邻接表 key是要修的课程 val是先修课程
		vector<int> in_deg(numCourses, 0); // 获得每个顶点的入度
		for (auto&& x : prerequisites) {
			adj_table[x[1]].push_back(x[0]); // 注意是x[1]为先修课程 x[0]为后续课程 由于是有向图 所以x[1]的邻居是x[0] 而x[0]的邻居没有x[1]
			in_deg[x[0]]++; // x[0]的入度+1
		}

		queue<int> q;
		// 将所有入度为0的结点入队
		for (int i = 0; i < numCourses; i++) {
			if (in_deg[i] == 0) q.push(i);
		}

		while (!q.empty()) {
			// 弹出队首结点
			auto prev_course = q.front();
			q.pop();
			numCourses -= 1;

			for (auto&& next_course : adj_table[prev_course]) {
				// 对于先修课程是prev_course的next_course 其入度要-1
				in_deg[next_course]--;
				// 如果入度-1后 入度为0 则入队
				if (in_deg[next_course] == 0) q.push(next_course);
			}
		}
		// 如果存在环 则一定有结点的入度一定不为0 则numCourses就一定不为0
		// 因为队列中只存储入度为0的结点
		return (numCourses == 0);
	}

	bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
		// DFS
		if (prerequisites.size() == 0 || numCourses == 1) return true;

		// 建立先修课程与所修课程的映射
		unordered_map<int, vector<int>> prev_to_next;
		for (auto&& x : prerequisites) prev_to_next[x[1]].push_back(x[0]);

		// 建立每个结点的状态
		vector<int> flag(numCourses);

		// 对每个结点进行dfs
		for (int i = 0; i < numCourses; i++) {
			if (!dfs(prev_to_next, flag, i)) return false; // 如果对结点i进行dfs 发现环 return false
		}
		return true;
	}

	bool dfs(unordered_map<int, vector<int>>& prev_to_next, vector<int>& flag, int course_id) {
		if (flag[course_id] == 2) return true; // 该结点已经被搜索过
		if (flag[course_id] == 1) return false; // 该结点的状态为“搜索中” 但是又碰到了此结点 说明有环

		flag[course_id] = 1; // 对该结点进行dfs 该结点状态置为“搜索中”
		for (auto&& x : prev_to_next[course_id]) {
			if (!dfs(prev_to_next, flag, x)) return false;
		}
		// 该结点遍历完后若没有环
		flag[course_id] = 2; // 状态置为“搜索完成”
		return true;
	}

};

int main() {
	vector<vector<int>> pres;
	pres.push_back(vector<int>{0, 10});
	pres.push_back(vector<int>{3, 18});
	pres.push_back(vector<int>{5, 5});
	pres.push_back(vector<int>{6, 11});
	pres.push_back(vector<int>{11, 14});
	pres.push_back(vector<int>{13, 1});
	pres.push_back(vector<int>{15, 1});
	pres.push_back(vector<int>{17, 4});
	Solution obj;
	int nums = 20;
	obj.canFinish(nums, pres);
	return 0;
}