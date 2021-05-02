# include <vector>
# include <algorithm>
# include <iostream>
# include <stack>
# include <queue>
# include <unordered_set>
# include <unordered_map>

using namespace std;

/*
�������� ��ͨ ͼ��һ���ڵ�����ã����㷵�ظ�ͼ�� �������¡��
ÿ���ڵ�ֵ Node.val ����Ψһ��
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
		// �����ù�ϣ����� �ȼ�¼�˱������Ľ�� �ֽ�����ԭ���Ϳ�¡����ӳ���ϵ
		unordered_map<Node*, Node*> visited; // ��ϣ��key��¼�Ѿ��������Ľ�� val��¼��¡���
		visited[node] = new Node{ node->val };
		queue<Node*> q;
		q.push(node);

		while (!q.empty()) {
			auto ori_node = q.front();
			q.pop();

			// ����ori_node�������ھ�
			for (auto&& neighbor : ori_node->neighbors) {
				if (visited.find(neighbor) == visited.end()) {
					// ������ھ�û�б������� �����µĽ��(ӳ���ϵ)
					visited[neighbor] = new Node{ neighbor->val };
					q.push(neighbor);
				}
				// ��ori_node�Ŀ�¡�ھ� ����ori_node�Ŀ�¡���
				visited[ori_node]->neighbors.push_back(visited[neighbor]);
			}
		}

		return visited[node];
	}

	unordered_map<Node*, Node*> visited;

	Node* cloneGraph(Node* node) {
		// Method 2 DFS
		if (!node) return node;

		// ����ý�㱻������ ��ֱ�ӷ���
		if (visited.find(node) != visited.end()) {
			return visited[node];
		}

		// ����ý��û�б������� �����µĽ��
		visited[node] = new Node{ node->val }; 

		// ����neighbor���µĽ����
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