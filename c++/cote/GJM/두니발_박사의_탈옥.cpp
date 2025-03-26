#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define N 50
#define D 100

using namespace std;

double cache[N + 1][D + 1];

vector<int>& split(const string& s) {
  stringstream ss(s);
  string temp;
  vector<int>* v = new vector<int>();
  while (getline(ss, temp, ' ')) {
    v->push_back(stoi(temp));
  }
  return *v;
}

int** initialize(fstream& fd, int n) {
  string buf;
  int** map = new int*[n];

  for (int i = 0; i < n; i++) {
    map[i] = new int[n];
  }

  for (int i = 0; i < n; i++) {
    getline(fd, buf);
    vector<int> v = split(buf);
    for (int j = 0; j < n; j++) {
      map[i][j] = v[j];
    }
  }

  return map;
}

int* getDegree(int** map, int n) {
  int* deg = new int[n];
  memset(deg, 0, sizeof(*deg));

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (map[i][j] != 0) deg[i]++;
    }
  }

  return deg;
}

// 그래프 dfs
double search1(int** map, int* deg, vector<int>& path, int n, int d, int q) {
  double ret = 0.;

  if (path.size() == d + 1) {
    if (path.back() != q) return 0.;

    ret = 1.;
    for (int i = 0; i + 1 < path.size(); i++) {
      ret /= deg[path[i]];
    }
    return ret;
  }

  int cur = path.back();

  for (int i = 0; i < n; i++) {
    if (map[cur][i] != 0) {
      path.push_back(i);
      ret += search1(map, deg, path, n, d, q);
      path.pop_back();
    }
  }

  return ret;
}

void solve1(int** map, int* deg, int n, int d, int p, vector<int>& query) {
  vector<int> path;
  path.push_back(p);

  for (auto q : query) {
    cout << fixed << setprecision(7) << search1(map, deg, path, n, d, q) << " ";
  }
  cout << endl;
}

double search2(int** map, int* deg, int cur, int days, int n, int d, int q) {
  if (days == d) {
    return (cur == q) ? 1. : 0.;
  }

  double& ret = cache[cur][days];
  if (ret > -0.5) return ret;

  ret = 0.;

  for (int i = 0; i < n; i++) {
    if (map[cur][i] != 0) {
      ret += search2(map, deg, i, days + 1, n, d, q) / deg[cur];
    }
  }

  return ret;
}

void solve2(int** map, int* deg, int n, int d, int p, vector<int>& query) {
  for (auto q : query) {
    memset(cache, -1, sizeof(cache));
    cout << fixed << setprecision(7) << search2(map, deg, p, 0, n, d, q) << " ";
  }
  cout << endl;
}

int main(void) {
  fstream fd("data/두니발_박사의_탈옥.txt");
  string buf;

  getline(fd, buf);
  int test_cases = stoi(buf);
  while (test_cases > 0) {
    getline(fd, buf);
    vector<int> v = split(buf);

    int** map = initialize(fd, v[0]);
    int* deg = getDegree(map, v[0]);
    getline(fd, buf);
    getline(fd, buf);
    vector<int> query = split(buf);
    solve1(map, deg, v[0], v[1], v[2], query);
    solve2(map, deg, v[0], v[1], v[2], query);

    for (int i = 0; i < v[0]; i++) {
      delete[] map[i];
    }
    delete[] map;

    delete[] deg;

    test_cases--;
  }

  return 0;
}