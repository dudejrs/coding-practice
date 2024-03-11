#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#define ALPHABETS 26
#define N 10000
#define M 20000

using namespace std;

vector<string> split(const string& s) {
	vector<string> ret;
	string buf;
	stringstream ss(s);

	while(getline(ss, buf, ' ')) {
		ret.push_back(buf);
	}

	return ret;
}

int toNumber(char ch){
	return ch - 'A';
}

struct Node {
	Node* children[ALPHABETS];

	int terminal = -1; // 이 노드에서 종료하는 문자열의 번호.
	int first = -1; // 이 노드를 루트로 하는 트라이에 가장 먼저 추가된 단어의 번호.

	~Node();

	// 이 노드를 루트로 하는 트라이에 번호 id인 문자열 key를 추가
	void insert(const char* key, int id) {
		if (first == -1) first = id;

		if (*key == 0){
			terminal = id;
		} else {
			int next = toNumber(*key);

			if (children[next] == NULL){
				children[next] = new Node();
			}
			children[next]->insert(key + 1, id);
		}
	}

	// 이 노드를 루트로 하는 트라이에 key와 일치하는 노드를 찾음.
	Node* find(const char* key) {
		if (*key ==0) return this;
		int next = toNumber(*key);

		if (children[next] == NULL)  return NULL;

		return children[next]->find(key + 1);
	}

	int type(const char* key, int id) {
		if (*key == 0) return 0;

		if (first == id) return 1;
		int next = toNumber(*key);
		return 1 + children[next] -> type(key + 1, id);
	}
};

Node* make_trie(vector<pair<string, int>>& words){
	sort(begin(words), end(words), [](pair<string, int> a, pair<string, int> b){
		return b.second <= a.second;
	});

	Node* trie = new Node();

	for (int i = 0; i < words.size(); i++) {
		trie->insert(words[i].first.c_str(), i);
	}

	trie->first = -1;
	
	return trie;	
}

int solve(vector<pair<string, int>>& words, const string& target) {
	Node* trie = make_trie(words);

	vector<string> tokens = split(target);
	int ret = 0;

	for (auto token : tokens) {
		Node* node = trie->find(token.data());

		if (node == NULL || node->terminal == -1) {
			ret += token.length();
			continue;
		}

		ret += trie->type(token.data(), node->terminal);
	}

	return ret + tokens.size() - 1;
}

int main(void){
	string buf;
	fstream fd("data/안녕히_그리고_물고기는_고마웠어요.txt");

	getline(fd, buf);
	int test_cases = stoi(buf);

	while (test_cases --> 0) {
		getline(fd, buf);
		vector<string> tokens = split(buf);
		
		int n = stoi(tokens[0]); 
		int m = stoi(tokens[1]); 

		vector<pair<string, int>> words;

		for (int i = 0; i < n; i++){
			getline(fd, buf);
			vector<string> tokens = split(buf);
			words.push_back(make_pair<>(tokens[0], stoi(tokens[1])));
		}

		getline(fd, buf);
		string target = buf;

		getline(fd, buf);
		int answer = stoi(buf);

		cout << answer<< " " << solve(words, target) << endl;
	}

	return 0;
}