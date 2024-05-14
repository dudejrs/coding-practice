#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define N 8

using namespace std;

const vector<pair<int, int>> d = {{-1, 1}, {1, 1}};

bool dfs(int a, vector<int>& aMatch, vector<int>& bMatch, vector<bool>& visited, vector<vector<bool>>& adj) {
	if (visited[a]) {
		return false;
	}

	visited[a] = true;

	for (int b = 0; b < bMatch.size(); b++) {
		if (!adj[a][b]) {
			continue;
		}

		if (bMatch[b] == -1 || dfs(bMatch[b], aMatch, bMatch, visited, adj)) {
			aMatch[a] = b;
			bMatch[b] = a;
			return true;
		}
	}

	return false;
}

int bipartiteMatch(int a, int b, vector<vector<bool>>& adj) {
	vector<int> aMatch(a, -1);
	vector<int> bMatch(b, -1);

	int count = 0;
	for (int i = 0; i < a; i++) {
		vector<bool> visited(a, false);
		if (dfs(i, aMatch, bMatch, visited, adj)) {
			count++;
		}
	}

	return count;
}

int solve(vector<string>& board) {
	int n = board.size();
	vector<vector<vector<int>>> id (2, vector<vector<int>>(n, vector<int>(n, -1)));

	int count[2] = {0, 0};

	for (int i = 0; i < 2; i++) {
		auto [dy, dx] = d[i];
		for (int y = 0; y < n; y++) {
			for (int x = 0; x < n; x++) {
				if (board[y][x] == '.' && id[i][y][x] == -1) {
					int cy = y, cx = x;

					while(0 <= cy && cy < n && cx >= 0 && cx < n && board[cy][cx] == '.') {
						id[i][cy][cx] = count[i];
						cy += dy;
						cx += dx;
					}
					count[i] ++;
				}
			}
		}
	}

	int a = count[0], b = count[1];
	vector<vector<bool>> adj(a, vector<bool>(b, 0));

	for (int y = 0; y < n; y++) {
		for (int x = 0; x < n; x++) {
			if (board[y][x] == '.') {
				adj[id[0][y][x]][id[1][y][x]] = 1;
			}
		}
	}

	return bipartiteMatch(a, b, adj);
}

int main(void) {
	string buf;
	fstream f("data/비숍.txt");

	getline(f, buf);
	int testCases = stoi(buf);

	for (int it = 0; it < testCases; it++) {
		getline(f, buf);
		int n = stoi(buf);

		vector<string> board;
		for (int i = 0; i < n; i++) {
			getline(f, buf);
			board.push_back(buf);
		}

		getline(f, buf);
		int answer = stoi(buf);
		cout << answer << " " << solve(board) << endl;
	}

	return 0;
}