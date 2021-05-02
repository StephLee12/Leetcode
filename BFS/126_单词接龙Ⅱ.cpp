# include <string>
# include <algorithm>
# include <vector>
# include <unordered_set>
# include <unordered_map>
# include <queue>

using namespace std;

/*
�����������ʣ�beginWord �� endWord����һ���ֵ� wordList���ҳ����д� beginWord �� endWord �����ת�����С�ת������ѭ���¹���

ÿ��ת��ֻ�ܸı�һ����ĸ��
ת����õ��ĵ��ʱ������ֵ��еĵ��ʡ�
˵��:

���������������ת�����У�����һ�����б�
���е��ʾ�����ͬ�ĳ��ȡ�
���е���ֻ��Сд��ĸ��ɡ�
�ֵ��в������ظ��ĵ��ʡ�
����Լ��� beginWord �� endWord �Ƿǿյģ��Ҷ��߲���ͬ��

*/

class Solution {
public:
	vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {

		// ��ʱ�� ������ ����40/42

		// ���ʵ�����ϣ��
		unordered_set<string> word_set(wordList.begin(), wordList.end());
		vector<vector<string>> res;
		int min_len = 0; // ��С

		if (word_set.find(endWord) == word_set.end()) return res;

		// ��¼�Ա������Ľ��Ϊkey ���Ӧ��ǰ׺����
		// ����val�Ƕ�άvec����Ϊһ��key���ܶ�Ӧ�������
		unordered_map<string, vector<vector<string>>> store_seq = {
			{beginWord,vector<vector<string>> ()}
		};
		store_seq.at(beginWord).push_back(vector<string>{beginWord});

		word_set.erase(beginWord);
		queue<string> q;
		q.push(beginWord);

		bool no_find_flag = true;
		while (!q.empty() && no_find_flag) {

			int now_cnt = q.size();
			// ���ڴ洢����BFS�������Ľ�� �������ҵ�����·�� ��˲�����ǰerase
			unordered_set<string> next_word; 
			for (int i = 1; i <= now_cnt; i++) {
				string ori_s = q.front();
				q.pop();

				for (int j = 0; j < ori_s.size(); j++) {
					char ori_word = ori_s[j];
					for (int k = 0; k < 26; k++) {
						if (char('a' + k) == ori_word) continue;

						string new_s = ori_s;
						new_s[j] = (char)('a' + k);
						if (new_s == endWord) {
							
							no_find_flag = false;// ����ҵ���endWord
							vector<vector<string>> new_seq = store_seq.at(ori_s);
							// ����ori_sΪ��β���������� ������
							for (auto&& seq : new_seq) {
								seq.push_back(new_s);
								if (min_len == 0) min_len = seq.size();
								res.push_back(seq);
							}
							if (next_word.find(endWord)==next_word.end()) next_word.insert(endWord);
						}
						else {
							if (word_set.find(new_s) != word_set.end()) {
								vector<vector<string>> new_seq = store_seq.at(ori_s);
								for (auto&& seq : new_seq) {
									seq.push_back(new_s);
									if (store_seq.find(new_s) == store_seq.end()) {
										// ���store_seq�л�û�����key Ҫ����
										store_seq.insert({ new_s, vector<vector<string>>{seq} });
									}
									else store_seq.at(new_s).push_back(seq); // ����������key ֱ��push_back
								}	
								// ������ͬ�����ظ����
								if (next_word.find(new_s) == next_word.end()) {
									q.push(new_s);
									next_word.insert(new_s);
								}
							}			
						}
					}
				}
			}
			for (auto&& s : next_word) word_set.erase(s);
		}

		return res;

	}
};

int main() {
	
	Solution obj;
	string b = "aaaaaaaaaa";
	string e = "bccccccccb";
	vector<string > words = { "aaaaaaaaaa","caaaaaaaaa","cbaaaaaaaa","daaaaaaaaa","dbaaaaaaaa","eaaaaaaaaa","ebaaaaaaaa","faaaaaaaaa","fbaaaaaaaa","gaaaaaaaaa","gbaaaaaaaa","haaaaaaaaa","hbaaaaaaaa","iaaaaaaaaa","ibaaaaaaaa","jaaaaaaaaa","jbaaaaaaaa","kaaaaaaaaa","kbaaaaaaaa","laaaaaaaaa","lbaaaaaaaa","maaaaaaaaa","mbaaaaaaaa","naaaaaaaaa","nbaaaaaaaa","oaaaaaaaaa","obaaaaaaaa","paaaaaaaaa","pbaaaaaaaa","qaaaaaaaaa","qbaaaaaaaa","raaaaaaaaa","rbaaaaaaaa","saaaaaaaaa","sbaaaaaaaa","taaaaaaaaa","tbaaaaaaaa","uaaaaaaaaa","ubaaaaaaaa","vaaaaaaaaa","vbaaaaaaaa","waaaaaaaaa","wbaaaaaaaa","xaaaaaaaaa","xbaaaaaaaa","yaaaaaaaaa","ybaaaaaaaa","zaaaaaaaaa","zbaaaaaaaa","bbaaaaaaaa","bdaaaaaaaa","bdbaaaaaaa","beaaaaaaaa","bebaaaaaaa","bfaaaaaaaa","bfbaaaaaaa","bgaaaaaaaa","bgbaaaaaaa","bhaaaaaaaa","bhbaaaaaaa","biaaaaaaaa","bibaaaaaaa","bjaaaaaaaa","bjbaaaaaaa","bkaaaaaaaa","bkbaaaaaaa","blaaaaaaaa","blbaaaaaaa","bmaaaaaaaa","bmbaaaaaaa","bnaaaaaaaa","bnbaaaaaaa","boaaaaaaaa","bobaaaaaaa","bpaaaaaaaa","bpbaaaaaaa","bqaaaaaaaa","bqbaaaaaaa","braaaaaaaa","brbaaaaaaa","bsaaaaaaaa","bsbaaaaaaa","btaaaaaaaa","btbaaaaaaa","buaaaaaaaa","bubaaaaaaa","bvaaaaaaaa","bvbaaaaaaa","bwaaaaaaaa","bwbaaaaaaa","bxaaaaaaaa","bxbaaaaaaa","byaaaaaaaa","bybaaaaaaa","bzaaaaaaaa","bzbaaaaaaa","bcbaaaaaaa","bcdaaaaaaa","bcdbaaaaaa","bceaaaaaaa","bcebaaaaaa","bcfaaaaaaa","bcfbaaaaaa","bcgaaaaaaa","bcgbaaaaaa","bchaaaaaaa","bchbaaaaaa","bciaaaaaaa","bcibaaaaaa","bcjaaaaaaa","bcjbaaaaaa","bckaaaaaaa","bckbaaaaaa","bclaaaaaaa","bclbaaaaaa","bcmaaaaaaa","bcmbaaaaaa","bcnaaaaaaa","bcnbaaaaaa","bcoaaaaaaa","bcobaaaaaa","bcpaaaaaaa","bcpbaaaaaa","bcqaaaaaaa","bcqbaaaaaa","bcraaaaaaa","bcrbaaaaaa","bcsaaaaaaa","bcsbaaaaaa","bctaaaaaaa","bctbaaaaaa","bcuaaaaaaa","bcubaaaaaa","bcvaaaaaaa","bcvbaaaaaa","bcwaaaaaaa","bcwbaaaaaa","bcxaaaaaaa","bcxbaaaaaa","bcyaaaaaaa","bcybaaaaaa","bczaaaaaaa","bczbaaaaaa","bccbaaaaaa","bccdaaaaaa","bccdbaaaaa","bcceaaaaaa","bccebaaaaa","bccfaaaaaa","bccfbaaaaa","bccgaaaaaa","bccgbaaaaa","bcchaaaaaa","bcchbaaaaa","bcciaaaaaa","bccibaaaaa","bccjaaaaaa","bccjbaaaaa","bcckaaaaaa","bcckbaaaaa","bcclaaaaaa","bcclbaaaaa","bccmaaaaaa","bccmbaaaaa","bccnaaaaaa","bccnbaaaaa","bccoaaaaaa","bccobaaaaa","bccpaaaaaa","bccpbaaaaa","bccqaaaaaa","bccqbaaaaa","bccraaaaaa","bccrbaaaaa","bccsaaaaaa","bccsbaaaaa","bcctaaaaaa","bcctbaaaaa","bccuaaaaaa","bccubaaaaa","bccvaaaaaa","bccvbaaaaa","bccwaaaaaa","bccwbaaaaa","bccxaaaaaa","bccxbaaaaa","bccyaaaaaa","bccybaaaaa","bcczaaaaaa","bcczbaaaaa","bcccbaaaaa","bcccdaaaaa","bcccdbaaaa","bccceaaaaa","bcccebaaaa","bcccfaaaaa","bcccfbaaaa","bcccgaaaaa","bcccgbaaaa","bccchaaaaa","bccchbaaaa","bccciaaaaa","bcccibaaaa","bcccjaaaaa","bcccjbaaaa","bccckaaaaa","bccckbaaaa","bccclaaaaa","bccclbaaaa","bcccmaaaaa","bcccmbaaaa","bcccnaaaaa","bcccnbaaaa","bcccoaaaaa","bcccobaaaa","bcccpaaaaa","bcccpbaaaa","bcccqaaaaa","bcccqbaaaa","bcccraaaaa","bcccrbaaaa","bcccsaaaaa","bcccsbaaaa","bccctaaaaa","bccctbaaaa","bcccuaaaaa","bcccubaaaa","bcccvaaaaa","bcccvbaaaa","bcccwaaaaa","bcccwbaaaa","bcccxaaaaa","bcccxbaaaa","bcccyaaaaa","bcccybaaaa","bccczaaaaa","bccczbaaaa","bccccbaaaa","bccccdaaaa","bccccdbaaa","bcccceaaaa","bccccebaaa","bccccfaaaa","bccccfbaaa","bccccgaaaa","bccccgbaaa","bcccchaaaa","bcccchbaaa","bcccciaaaa","bccccibaaa","bccccjaaaa","bccccjbaaa","bcccckaaaa","bcccckbaaa","bcccclaaaa","bcccclbaaa","bccccmaaaa","bccccmbaaa","bccccnaaaa","bccccnbaaa","bccccoaaaa","bccccobaaa","bccccpaaaa","bccccpbaaa","bccccqaaaa","bccccqbaaa","bccccraaaa","bccccrbaaa","bccccsaaaa","bccccsbaaa","bcccctaaaa","bcccctbaaa","bccccuaaaa","bccccubaaa","bccccvaaaa","bccccvbaaa","bccccwaaaa","bccccwbaaa","bccccxaaaa","bccccxbaaa","bccccyaaaa","bccccybaaa","bcccczaaaa","bcccczbaaa","bcccccbaaa","bcccccdaaa","bcccccdbaa","bccccceaaa","bcccccebaa","bcccccfaaa","bcccccfbaa","bcccccgaaa","bcccccgbaa","bccccchaaa","bccccchbaa","bccccciaaa","bcccccibaa","bcccccjaaa","bcccccjbaa","bccccckaaa","bccccckbaa","bccccclaaa","bccccclbaa","bcccccmaaa","bcccccmbaa","bcccccnaaa","bcccccnbaa","bcccccoaaa","bcccccobaa","bcccccpaaa","bcccccpbaa","bcccccqaaa","bcccccqbaa","bcccccraaa","bcccccrbaa","bcccccsaaa","bcccccsbaa","bccccctaaa","bccccctbaa","bcccccuaaa","bcccccubaa","bcccccvaaa","bcccccvbaa","bcccccwaaa","bcccccwbaa","bcccccxaaa","bcccccxbaa","bcccccyaaa","bcccccybaa","bccccczaaa","bccccczbaa","bccccccbaa","bccccccdaa","bccccccdba","bcccccceaa","bcccccceba","bccccccfaa","bccccccfba","bccccccgaa","bccccccgba","bcccccchaa","bcccccchba","bcccccciaa","bcccccciba","bccccccjaa","bccccccjba","bcccccckaa","bcccccckba","bcccccclaa","bcccccclba","bccccccmaa","bccccccmba","bccccccnaa","bccccccnba","bccccccoaa","bccccccoba","bccccccpaa","bccccccpba","bccccccqaa","bccccccqba","bccccccraa","bccccccrba","bccccccsaa","bccccccsba","bcccccctaa","bcccccctba","bccccccuaa","bccccccuba","bccccccvaa","bccccccvba","bccccccwaa","bccccccwba","bccccccxaa","bccccccxba","bccccccyaa","bccccccyba","bcccccczaa","bcccccczba","bcccccccba","bcccccccda","bcccccccdb","bcccccccea","bccccccceb","bcccccccfa","bcccccccfb","bcccccccga","bcccccccgb","bcccccccha","bccccccchb","bcccccccia","bcccccccib","bcccccccja","bcccccccjb","bcccccccka","bccccccckb","bcccccccla","bccccccclb","bcccccccma","bcccccccmb","bcccccccna","bcccccccnb","bcccccccoa","bcccccccob","bcccccccpa","bcccccccpb","bcccccccqa","bcccccccqb","bcccccccra","bcccccccrb","bcccccccsa","bcccccccsb","bcccccccta","bccccccctb","bcccccccua","bcccccccub","bcccccccva","bcccccccvb","bcccccccwa","bcccccccwb","bcccccccxa","bcccccccxb","bcccccccya","bcccccccyb","bcccccccza","bccccccczb","bccccccccb","aaaaaaaaaz","aaaaaaaabz","aaaaaaacbz","aaaaaaacbc","aaaaaadcbc","aaaaaedcbc","aaaaaedccc","aaaafedccc","aaaafecccc","aaaffecccc","aafffecccc","aaffcecccc","aaffcccccc","acffcccccc","acfccccccc","accccccccc","accccccccb" };
	obj.findLadders(b, e, words);
	return 0;
}


