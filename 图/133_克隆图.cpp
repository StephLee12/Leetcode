# include <vector>
# include <algorithm>
# include <iostream>
# include <stack>
# include <queue>
# include <unordered_set>
# include <unordered_map>

using namespace std;

/*
给你无向 连通 图中一个节点的引用，请你返回该图的 深拷贝（克隆）
每个节点值 Node.val 都是唯一的
*/


class Node {
public:
	int val;
	vector<Node*> neighbors;
};

class Solution {
public:
	Node* cloneGraph(Node* node) {
		if (!node) return node;

		// Method 1 BFS
		// 这里用哈希表很妙 既记录了遍历过的结点 又建立了原结点和克隆结点的映射关系
		unordered_map<Node*, Node*> visited; // 哈希表key记录已经遍历过的结点 val记录克隆结点
		visited[node] = new Node{ node->val };
		queue<Node*> q;
		q.push(node);

		while (!q.empty()) {
			auto ori_node = q.front();
			q.pop();

			// 遍历ori_node的所有邻居
			for (auto&& neighbor : ori_node->neighbors) {
				if (visited.find(neighbor) == visited.end()) {
					// 如果该邻居没有被遍历过 建立新的结点(映射关系)
					visited[neighbor] = new Node{ neighbor->val };
					q.push(neighbor);
				}
				// 将ori_node的克隆邻居 加入ori_node的克隆结点
				visited[ori_node]->neighbors.push_back(visited[neighbor]);
			}
		}

		return visited[node];
	}

	unordered_map<Node*, Node*> visited;

	Node* cloneGraph(Node* node) {
		// Method 2 DFS
		if (!node) return node;

		// 如果该结点被遍历到 则直接返回
		if (visited.find(node) != visited.end()) {
			return visited[node];
		}

		// 如果该结点没有被遍历到 建立新的结点
		visited[node] = new Node{ node->val }; 

		// 复制neighbor到新的结点中
		for (auto&& neighbor : node->neighbors) {
			visited[node]->neighbors.push_back(cloneGraph(neighbor));
		}

		return visited[node];
	}

};

int main() {
	Node* node_1 = new Node{ 1 ,vector<Node*>()};
	Node* node_2 = new Node{ 2 ,vector<Node*>() };
	Node* node_3 = new Node{ 3 ,vector<Node*>() };
	Node* node_4 = new Node{ 4 ,vector<Node*>() };

	node_1->neighbors = { node_2,node_4 };
	node_2->neighbors = { node_1,node_3 };
	node_3->neighbors = { node_2,node_4 };
	node_4->neighbors = { node_1,node_3 };

	Solution obj;
	obj.cloneGraph(node_1);
	return 0;
}