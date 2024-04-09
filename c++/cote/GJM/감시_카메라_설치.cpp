#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

enum class State {
	UNWATCHED, WATCHED, INSTALLED
};

vector<int> split(const string& s) {
	stringstream ss {s};
	istream_iterator<int> begin{ss}, end ;

	return {begin, end};
}

State dfs(int cur, vector<vector<int>>& adj, vector<bool>& visited, int& installed) {
	visited[cur] = true;
	map<State, int> counts;

	for (auto& next : adj[cur]) {
		if (!visited[next]) {
			State childState = dfs(next, adj, visited, installed);
			counts[childState] += 1;
		}	
	}

	if (counts[State::UNWATCHED]) {
		installed++;
		return State::INSTALLED;
	} 

	if (counts[State::INSTALLED]) {
		return State::WATCHED;
	}

	return State::UNWATCHED;
}

int solve(int n, vector<vector<int>>& edges) {
	vector<vector<int>> adj(n, vector<int>());
	vector<bool> visited(n, false);

	for (auto& edge : edges) {
		int a = edge[0], b = edge[1];
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	int installed = 0;

	for (int i = 0; i < n; i++) {
		if (!visited[i] && dfs(i, adj, visited, installed) == State::UNWATCHED) {
			installed++;
		}
	}

	return installed;
}

int main(void) {
	string buf;
	fstream fd("data/감시_카메라_설치.txt");
	
	getline(fd, buf);
	int test_cases = stoi(buf);
	
	for (int it = 0; it < test_cases; it++) {
		getline(fd, buf);
		vector<int> nums = split(buf);
		vector<vector<int>> edges;

		for (int i = 0; i < nums[1]; i++) {
			getline(fd, buf);
			edges.push_back(split(buf));
		}

		getline(fd, buf);
		int answer = stoi(buf);

		cout << answer << " " << solve(nums[0], edges) << endl;
	}

	return 0;
}