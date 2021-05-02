# include <string>
# include <vector>
# include <iostream>
# include <algorithm>
# include <unordered_map>
# include <set>

using namespace std;

/*
����һ������������ equations ��һ��ʵ��ֵ���� values ��Ϊ��֪������

���� equations[i] = [Ai, Bi] �� values[i] ��ͬ��ʾ��ʽ Ai / Bi = values[i] ��

ÿ�� Ai �� Bi ��һ����ʾ�����������ַ�����

����һЩ������ queries ��ʾ�����⣬���� queries[j] = [Cj, Dj] ��ʾ�� j �����⣬

���������֪�����ҳ� Cj / Dj = ? �Ľ����Ϊ�𰸡�

���� ��������Ĵ� ���������ĳ���޷�ȷ���Ĵ𰸣����� -1.0 �������𰸡�

��������г����˸�������֪������û�г��ֵ��ַ�����Ҳ��Ҫ�� -1.0 �������𰸡�

ע�⣺����������Ч�ġ�����Լ�����������в�����ֳ���Ϊ 0 ��������Ҳ������κ�ì�ܵĽ����

*/

class Solution {
public:
	vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
		// ��������ͼ���ڽӱ� ��ÿ�����ж�Ӧ��Ȩֵ keyΪhead valΪtail��edge value��pair
		unordered_map<string, vector<pair<string,double>>> adj_table;
		for (int i = 0; i < equations.size(); i++) {
			string head = equations[i][0]; string tail = equations[i][1];
			adj_table[head].push_back(pair<string, double>{tail,values[i]});
			adj_table[tail].push_back(pair<string, double>{head, 1.0/values[i]});
		}

		int q_num = queries.size(); // quries������
		set<pair<string, string>> records; // dfs��¼�������Ľ��
		vector<double> res(q_num); // �������
		for (int i = 0; i < q_num;i++) {
			auto q = queries[i];
			string head = q[0]; string tail = q[1];

			// �ж�head��tail�Ƿ��ǺϷ���
			bool flag = false;
			if (adj_table.find(head) != adj_table.end() && adj_table.find(tail) != adj_table.end()) flag = true;

			if (flag) {
				// ������ǺϷ���
				double tmp = dfs(double(1), head, tail, adj_table, records);
				if (tmp == 0) res[i] = double(-1); // ���û���ҵ�arc��tail��·�� ��Ϊͼ��һ����ͨ
				else res[i] = tmp;
			}
			else res[i]=double(-1); // ���head��tail���ǺϷ��� ��query��ֵΪ-1
			records.clear(); // ���records ������һ��dfs
		}
		return res;
	}

	double dfs(double val,string head, const string& tail, unordered_map<string, vector<pair<string, double>>>& adj_table, set<pair<string, string>>& records) {
		if (head == tail) return val; // �ҵ��˴�arc��tail��·��

		vector<pair<string, double>> neighbors = adj_table[head]; // ��ȡhead���ھӽ��
		bool dead = true; // deadΪ�Ƿ���ڴ�head��tail��· dead=trueΪ������
		for (auto&& edge :neighbors) {
			string next_node = edge.first; double next_val = edge.second; // head���ھ� �Լ��ߵ�ֵ
			if (records.find(pair<string, string>{head, next_node}) == records.end()) {
				// ������û�б�������
				records.insert(pair<string, string>{head, next_node}); // ��¼�ñ�
				double tmp = dfs(next_val, next_node, tail, adj_table, records);  // ��next_node����dfs
				// ���tmp=0 ˵����next_node�����޷���tail
				if (tmp == 0) dead=true;
				else {
					// ���tmp!=0 ˵�����ڴ�next_node��tail��·�� ֱ��break
					dead = false;
					val *= tmp;
					break;
				}
			}
		}

		return (dead ? 0 : val); // ��������ڴ�arc��tail��·�� ����0 ���򷵻رߵ�ֵ
	}

};

int main() {
	vector<vector<string>> eqs;
	eqs.push_back(vector<string>{"a", "b"});
	eqs.push_back(vector<string>{"b", "c"});
	vector<double> vals{ double(2),double(3) };
	vector<vector<string>> quries;
	quries.push_back(vector<string>{"a", "c"});
	quries.push_back(vector<string>{"b", "a"});
	quries.push_back(vector<string>{"a", "e"});
	quries.push_back(vector<string>{"a", "a"});
	quries.push_back(vector<string>{"x", "x"});
	Solution obj;
	obj.calcEquation(eqs, vals, quries);
	return 0;

}