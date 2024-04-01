#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#define MAX_WORDS_LENGTH 100
#define MAX_WORD_LENGTH 10
#define ALPHABETS 26

using namespace std;

vector<vector<int>> adj;
vector<string> graph[ALPHABETS][ALPHABETS];
vector<int> indegree, outdegree;

vector<string> split(const string& s) {
	stringstream ss {s};
	istream_iterator<string> it {ss}, end{};

	return {it, end};
}

void cleanup(){
	for (int i = 0; i < ALPHABETS; i++){
		for (int j = 0; j < ALPHABETS; j++) {
			graph[i][j].clear();
		}
	}

	adj = vector<vector<int>>(ALPHABETS, vector<int>(ALPHABETS, 0));
	indegree = outdegree = vector<int>(ALPHABETS, 0);
}

void make_graph(const vector<string>& words) {
	cleanup();

	for (int i = 0; i < words.size(); i++) {
		int a = words[i][0] - 'a';
		int b = words[i][words[i].size() - 1] - 'a';

		graph[a][b].push_back(words[i]);
		adj[a][b]++;
		outdegree[a]++;
		indegree[b]++;
	}
}

void dfs(int cur, vector<int>& path) {
	
	for (int next = 0; next < ALPHABETS; next++) {
		while (adj[cur][next] > 0) {
			adj[cur][next]--;
			dfs(next, path);
		}
	}
	path.push_back(cur);
}

vector<int> get_path() {
	vector<int> path;
	
	//오일러 트레일이 될 수 있는 가능성이 있는 경우, 오일러 트레일을 가정한다.
	for (int i = 0; i < ALPHABETS; i++){
		if (outdegree[i] == indegree[i] + 1){
			dfs(i, path);
			return path;
		}
	}

	//오일러 서킷을 가정한다.
	for (int i = 0; i < ALPHABETS; i++){
		if (outdegree[i]){
			dfs(i, path);
			return path;
		}
	}

	return path;
}

vector<string> to_words(const vector<int>& path) {
	vector<string> ret;

	for (int i = 0; i < path.size() - 1; i++) {
		int a = path[i], b = path[i + 1];
		ret.push_back(graph[a][b].back());
		graph[a][b].pop_back();
	}

	return ret;
}

vector<string> solve(const vector<string>& words) {
	make_graph(words);

	vector<int> path = get_path();

	if (path.size() != words.size() + 1 ) {
		return {"IMPOSSIBLE"};
	}

	reverse(begin(path), end(path));

	return to_words(path);
}

int main(void) {
	fstream fd("data/단어_제한_끝말잇기.txt");

	string buf;

	getline(fd, buf);
	int test_cases = stoi(buf);

	while (test_cases > 0) {
		getline(fd, buf);
		vector<string> words = split(buf);
		vector<string> solved = solve(words);

		for (auto& word : solved) {
			cout << word << " ";
		}
		cout << endl;

		test_cases--;
	}

	return 0;
}