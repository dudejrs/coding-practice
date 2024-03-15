#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <string>
#include <array>
#include <vector>
#include <queue>
#define MAX_PATTERN_LENGTH 10
#define ALPHABETS 26
#define N 100
#define M 100
#define MOD 10007

using namespace std;

// M * MAX_PATTERN_LENGTH + 1 : 만들수 있는 상태의 개수
int cache[N + 1][M * MAX_PATTERN_LENGTH + 1];

inline int to_number(char ch) {
	return ch - 'A';
}

array<int, 2> split(const string& s) {
	array<int, 2> ret {};
	stringstream ss(s);
	string buf;

	for(int i = 0; i < 2; i++) {
		getline(ss, buf, ' ');
		ret[i] = stoi(buf);
	}

	return ret;
}

struct Node {
	Node* children[ALPHABETS];
	int terminal {-1}; // 현 위치에서 끝나는 문자열의 번호;
	Node* fail {nullptr};
	Node* next[ALPHABETS]; // 상태 전이
	int no {-1}; // 노드(상태)에 대한 번호 
	vector<int> output {}; //이 노드(상태)가 방문되었을 떄 등장하는 문자열의 번호

	Node() {
		for (int i = 0; i < ALPHABETS; i++) {
			children[i] = nullptr;
			next[i] = nullptr;
		}
	}

	~Node() {
		for (int i = 0; i < ALPHABETS; i++) {
			if (children[i]) {
				delete children[i];
			}
			if (next[i]) {
				delete next[i];
			}
		}
	}

	void insert(const char* key, int id) {
		if (*key == 0) {
			terminal = id;
		} else {
			int next = to_number(*key);

			if (children[next] == nullptr) {
				children[next] = new Node{};
			}
			children[next]->insert(key + 1, id);
		}
	}
};

Node* make_trie(const vector<string>& words) {
	Node* trie = new Node{};

	for (int i = 0; i < words.size(); i++) {
		trie->insert(words[i].c_str(), i);
	}
	return trie;
}

// 트라이가 주어질 때 각 노드에 대해 실패함수를 계산
void compute_fail(Node* root) {
	queue<Node*> q {};
	
	root->fail = root;
	q.push(root);

	while (!q.empty()) {
		Node* cur = q.front();
		q.pop();

		for (int i = 0; i < ALPHABETS; i++) {
			Node* child = cur->children[i];

			if (!child) continue;

			// 1레벨 노드의 실패 연결은 항상 루트
			if (cur == root){ 
				child->fail = root;
			
			// 1레벨 이상의 노드는 부모의 실패 연결을 따라가면서 실패 연결을 찾는다
			} else {
				Node* t = cur->fail;
				while (t != root && t->children[i] == nullptr) {
					t = t->fail;
				}

				if (t->children[i]) {
					t = t->children[i];
				}
				child->fail = t;
			}

			child->output = child->fail->output;

			if (child->terminal != -1) {
				child->output.push_back(child->terminal);
			}
			q.push(child);
		}
	}
}

// 상태 간의 전이 테이블을 next[]에 채운다.
// 이미 compute_fail()을 통해 실패함수가 계산되어 있다고 가정한다.
void compute_transistion(Node* cur, int& counter){
	cur->no = counter++;

	// cur 뒤에 알파벳을 붙였을떄 어느 상태로 가는지 기록
	for (int i = 0; i < ALPHABETS; i++) {
		Node* next = cur;
		while(next != next->fail && next->children[i] == nullptr) {
			next = next->fail;
		}
		if (next->children[i]){
			next = next->children[i];
		}
		cur->next[i] = next;

		// 재귀적으로 모든 노드에 대해 전이 테이블을 계산한다.
		if (cur->children[i]){
			compute_transistion(cur->children[i], counter);
		}
	}
}

// 앞으로 length 글자 만들어야 하는데, 아호-코라식 알고리즘의
// 현재 상태가 state에 주어질 때 만들 수 있는 문자열의 수
int count(int length, Node* state) {
	// 기저 사례: 이 상태에 문자열이 출현하면 곧장 종료 
	if (state->output.size()) {
		return 0;
	}
	// 기저사례: 문자열을 전부 만든 경우
	if (length == 0) {
		return 1;
	}

	int& ret = cache[length][state->no];
	if (ret != -1) return ret;

	ret = 0;

	for (int i = 0; i < ALPHABETS; i++) {
		ret += count(length - 1, state->next[i]);
		ret %= MOD;
	}

	return ret;
}

// patterns에 걸리지 않고 만들수 있는 n글자의 문자열의 수를 MOD로 모듈러 연산 한 값
int solve(vector<string>& patterns, int n) {
	Node* state = make_trie(patterns);
	int counter {0};
	compute_fail(state);
	compute_transistion(state, counter);

	memset(cache, -1, sizeof(cache));

	return count(n, state);
}

int main(void) {
	string buf;

	fstream fd("data/보안종결자.txt");

	getline(fd, buf);
	int test_cases = stoi(buf);

	while (test_cases --> 0) {
		getline(fd, buf);
		array<int, 2> tokens = split(buf);
		auto [n, m] = tokens;

		vector<string> patterns {};
		for (int i = 0; i < m; i++) {
			getline(fd, buf);
			patterns.push_back(buf);
		}	

		getline(fd, buf);
		int answer = stoi(buf);
		cout << answer << " " << solve(patterns, n) << endl;
	}

	return 0;
}