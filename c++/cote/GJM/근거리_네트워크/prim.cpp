#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <limits>
#include <vector>

#define N 500
#define M 2000

using namespace std;

pair<int, int> splitp(const string& s) {
	stringstream ss {s};
	istream_iterator<int> it {ss};

	return {*(it++), *(it++)};
}

vector<int> splitv(const string& s) {
	stringstream ss {s};
	istream_iterator<int> start {ss}, end;

	return vector<int>(start, end);
}

double distance (int y1, int x1, int y2, int x2) {
	return sqrt(pow(y1 - y2, 2) + pow(x1 - x2, 2));
}

vector<vector<pair<int, double>>> initialize(const vector<int>& x, const vector<int>& y) {
	int n = x.size();
	vector<vector<pair<int, double>>> adj (n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) {
				adj[i].push_back({j, numeric_limits<double>::max()});
			} else {
				adj[i].push_back({j, distance(y[i], x[i], y[j], x[j])});
			}
		}
	}

	return adj;	
}

double prim(vector<pair<int,int>>& selected, vector<vector<pair<int, double>>>& adj) {
	int n = adj.size();
	vector<bool> added(n, false);

	vector<double> dist(n, numeric_limits<double>::max());
	vector<int> parent(n, -1);

	double ret = 0;
	dist[0] = 0;
	parent[0] = 0;

	for (int it = 0; it < n; it++) {
		int cur = -1;

		for(int i = 0; i < n; i++) {
			if(!added[i] && (cur == -1 || dist[cur] > dist[i]))  {
				cur = i;
			}
		}

		if (parent[cur] != cur) {
			selected.push_back({parent[cur], cur});
		}

		ret += dist[cur];
		added[cur] = true;

		for (auto [i, weight] : adj[cur]) {
			if (!added[i] && dist[i] > weight) {
				dist[i] = weight;
				parent[i] = cur;
			}
		}
	}

	return ret;
}

double solve(const vector<int>& x, const vector<int>& y, const vector<pair<int, int>>& cables) {
	int n = x.size();
	vector<vector<pair<int, double>>> adj = initialize(x, y);

	for (auto [a, b] : cables ) {
		adj[a][b] = pair {b, 0};
		adj[b][a] = pair {a, 0};	
	}

	vector<pair<int, int>> selected; 
	return prim(selected, adj);
}


int main(void) {
	string buf;

	fstream f("../data/근거리_네트워크.txt");

	getline(f, buf);
	int testCases = stoi(buf);

	for (int it = 0; it < testCases; it++) {
		getline(f, buf);
		auto [n, m] = splitp(buf);
		getline(f, buf);
		vector<int> x = splitv(buf);
		getline(f, buf);
		vector<int> y = splitv(buf);

		vector<pair<int, int>> cables;
		for (int i = 0; i < m; i++) {
			getline(f, buf);
			cables.emplace_back(splitp(buf));
		}

		getline(f, buf);
		double answer = stod(buf);
		cout << setprecision(7) << answer <<" " << solve(x, y, cables) << endl;
	}

	return 0;
}