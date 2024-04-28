#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

#define N 500
#define M 2000

using namespace std;

struct DisjointSet {

	DisjointSet(int n) : parent(n), rank(n, 0), _size(n) {
		for (int i = 0; i < n ; i++) {
			parent[i] = i;
		}
	}

	int find(int x) {
		if (parent[x] == x) {
			return x;
		}
		return parent[x] = find(parent[x]);
	}

	void merge(int x, int y) {
		x = find(x);
		y = find(y);

		if (x == y) {
			return;
		}

		if (rank[x] < rank[y]) {
			swap(x, y);
		}
		parent[y] = x;
		
		if (rank[x] == rank[y]) {
			rank[x]++;
		}
		_size--;

		return;
	}

	int size() {
		return _size;
	}

	private :
		vector<int> parent;
		vector<int> rank;
		int _size;
};


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

inline double distance(int y1, int x1, int y2, int x2) {
	return sqrt(pow(y1 - y2, 2) + pow(x1 - x2, 2));
}

vector<pair<double, pair<int, int>>> initialize(const vector<int>& x, const vector<int>& y) {
	int n = x.size();

	vector<pair<double, pair<int, int>>> ret;

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			ret.push_back({distance(y[i], x[i], y[j], x[j]), {i, j}});
		}
	}

	return ret;
}

double kruskal(int n, vector<pair<double, pair<int, int>>>& edges, vector<pair<int, int>>& selected) {
	DisjointSet set(n);
	sort(begin(edges), end(edges));

	double ret = 0;
	for (auto [cost, e] : edges) {
		auto [a, b] = e;

		if (set.find(a) == set.find(b)) {
			continue;
		}
		set.merge(a, b);

		selected.push_back({a, b});
		ret += cost;

		if (set.size() == 1) {
			break;
		}
	}

	return ret;
}

double solve(const vector<int>& x, const vector<int>& y, const vector<pair<int, int>>& cables) {
	vector<pair<double, pair<int, int>>> edges = initialize(x, y);

	for (auto [a, b] : cables) {
		edges.push_back({0, {a, b}});
	}

	vector<pair<int, int>> selected;

	return kruskal(x.size(), edges, selected);
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