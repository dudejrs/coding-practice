#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#define H 20
#define W 20

using namespace std;

const vector<pair<int,int>> d = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

pair<int, int> split(const string& s) {
	stringstream ss {s};
	istream_iterator<int> it {ss};

	return {*(it++), *(it++)};
}

vector<vector<bool>> initialize(vector<string>& board) {
	int n = board.size(), m = board[0].size();
	vector<vector<int>> id(n, vector<int>(m, -1));
	int a = 0, b = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] == '#') {
				continue;
			}
			if ((i + j) % 2 == 0) {
				id[i][j] = a++;
			} else {
				id[i][j] = b++;
			}
		}
	}


	vector<vector<bool>> adj(a, vector<bool>(b, false));

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if ((y + x) % 2 != 0 || board[y][x] == '#') {
				continue;
			}

			for (auto [dy, dx] : d) {
				int ny = y + dy, nx = x + dx;

				if (ny < 0 || ny >= n || nx < 0 || nx >= m || board[ny][nx] == '#') {
					continue;
				}
				adj[id[y][x]][id[ny][nx]] = true;
			}
		}
	}

	return adj;
}

bool dfs(int a, vector<vector<bool>>& adj, vector<int>& aMatch, vector<int>& bMatch, vector<bool>& visited) {
	if (visited[a]) {
		return false;
	}

	visited[a] = true;

	for (int b = 0; b < adj[a].size(); b++){
		if (! adj[a][b]) {
			continue;
		}

		if (bMatch[b] == -1 || dfs(bMatch[b], adj, aMatch, bMatch, visited)) {
			aMatch[a] = b;
			bMatch[b] = a;

			return true;
		}
	}

	return false;
}

int bipartite_match(vector<vector<bool>>& adj, vector<int>&  aMatch, vector<int>& bMatch ) {
	int a = aMatch.size();
	int count = 0;
	for (int i = 0; i < a; i++) {
		vector<bool> visited(a, false);
		if (dfs(i, adj, aMatch, bMatch, visited)) {
			count++;
		}
	}

	return count;
}

void set_trap(vector<bool>& aChosen, vector<bool>& bChosen, vector<string>& board) {
	int n = board.size(), m = board[0].size();
	vector<vector<int>> id(n, vector<int>(m, -1));
	int a = 0, b = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (board[i][j] == '#') {
				continue;
			}
			if ((i + j) % 2 == 0) {
				if (aChosen[a]) {
					board[i][j] = '^';
				}

				id[i][j] = a++;
			} else {
				if (bChosen[b]) {
					board[i][j] = '^';
				}

				id[i][j] = b++;
			}
		}
	}
}

void choose(vector<vector<bool>>& adj, vector<int>& aMatch, vector<int>& bMatch, vector<string>& board) {
	int a = adj.size(), b = adj[0].size();
	vector<bool> aChosen(a), bChosen(b);

	// a집합 노드들을 모두 선택
	fill(begin(aChosen), end(aChosen), true);

	// b집합 노드들은 매칭되지 않은 노드들만 선택
	fill(begin(bChosen), end(bChosen), false);
	for (int i = 0; i < b; i++) {
		if(bMatch[i] == -1) {
			bChosen[i] = true;
		}
	}

	// 선택된 a와 b의 정점이 인점 한 경우, A의 정점을 선택해제하고, B의 대응된 정점을 선택
	while (true) {
		bool changed = false;

		for (int i = 0; i < a; i++) {
			for (int j =0; j < b; j++) {
				if (aChosen[i] && bChosen[j] && adj[i][j]) {
					assert(aMatch[i] != -1);
					aChosen[i] = false;
					bChosen[aMatch[i]] = true;
					changed = true;
				}
			}
		}

		if (!changed) {
			break;
		}
	}

	set_trap(aChosen, bChosen, board);

	return;
}

int solve(vector<string>& board) {
	int n = board.size(), m = board[0].size();
	
	vector<vector<bool>> adj = {initialize(board)};

	int a = adj.size(), b = adj[0].size();
	vector<int> aMatch(a, -1), bMatch(b, -1);

	int match = bipartite_match(adj, aMatch, bMatch);

	choose(adj, aMatch, bMatch, board);

	return a + b - match;
}

int main(void) {
	string buf;

	fstream f("data/함정_설치.txt");
	getline(f, buf);

	int testCases = stoi(buf);

	for (int it = 0; it < testCases; it++) {
		getline(f, buf);
		auto [n, m] = split(buf);

		vector<string> board;
		for (int i = 0; i < n; i++) {
			getline(f, buf);
			board.push_back(buf);
		}

		getline(f, buf);
		int answer = stoi(buf);

		cout << answer << " " << solve(board) << endl;
		for (auto row : board) {
			cout << row << endl;
		}
		cout << endl;
	}

	return 0;
}