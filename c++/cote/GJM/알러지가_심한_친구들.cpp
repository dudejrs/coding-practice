#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#define N 20
#define M 20
#define INF 987654321

using namespace std;

int best = 0;

vector<string> split(const string& s) {
  vector<string> ret;
  stringstream ss(s);
  string tmp;

  while (getline(ss, tmp, ' ')) {
    ret.push_back(tmp);
  }

  return ret;
}

void initialize(fstream& fd, vector<int> eater[], vector<int> canEat[], int n,
                int m) {
  string buf;
  getline(fd, buf);
  vector<string> persons = split(buf);
  map<string, int> personToIdx;

  for (int i = 0; i < persons.size(); i++) {
    personToIdx.insert(make_pair(persons[i], i));
  }

  for (int i = 0; i < m; i++) {
    getline(fd, buf);
    vector<string> result = split(buf);
    for (int j = 1; j < result.size(); j++) {
      int p = personToIdx[result[j]];
      canEat[p].push_back(i);
      eater[i].push_back(p);
    }
  }

  return;
}

void search_badcase(int cur, vector<int>& edible, vector<int> eater[],
                    vector<int> canEat[], int n, int m, int chosen) {
  if (chosen >= best) return;

  if (cur == m) {
    if (find(begin(edible), end(edible), 0) == end(edible)) {
      best = min(best, chosen);
    }
    return;
  }

  search_badcase(cur + 1, edible, eater, canEat, n, m, chosen);

  for (int i = 0; i < eater[cur].size(); i++) {
    edible[eater[cur][i]] += 1;
  }
  search_badcase(cur + 1, edible, eater, canEat, n, m, chosen + 1);
  for (int i = 0; i < eater[cur].size(); i++) {
    edible[eater[cur][i]] -= 1;
  }

  return;
}

int solve_badcase(vector<int> eater[], vector<int> canEat[], const int n,
                  const int m) {
  vector<int> edible(n, 0);
  best = INF;
  search_badcase(0, edible, eater, canEat, n, m, 0);

  return best;
}

void search(vector<int>& edible, vector<int> eater[], vector<int> canEat[],
            int n, int m, int chosen) {
  if (chosen >= best) return;

  auto it = find(begin(edible), end(edible), 0);

  if (it == end(edible)) {
    best = min(best, chosen);
    return;
  }

  int p = distance(begin(edible), it);

  for (int i = 0; i < canEat[p].size(); i++) {
    int cur = canEat[p][i];

    for (int j = 0; j < eater[cur].size(); j++) {
      edible[eater[cur][j]] += 1;
    }

    search(edible, eater, canEat, n, m, chosen + 1);

    for (int j = 0; j < eater[cur].size(); j++) {
      edible[eater[cur][j]] -= 1;
    }
  }

  return;
}

int solve(vector<int> eater[], vector<int> canEat[], const int n, const int m) {
  vector<int> edible(n, 0);
  best = INF;
  search(edible, eater, canEat, n, m, 0);

  return best;
}

int main(void) {
  fstream fd("data/알러지가_심한_친구들.txt");
  string buf;

  getline(fd, buf);
  int test_cases = stoi(buf);

  while (test_cases > 0) {
    getline(fd, buf);
    vector<string> result = split(buf);
    int n = stoi(result[0]);
    int m = stoi(result[1]);

    vector<int> eater[m];
    vector<int> canEat[n];

    initialize(fd, eater, canEat, n, m);

    cout << solve_badcase(eater, canEat, n, m) << ","
         << solve(eater, canEat, n, m) << endl;

    test_cases--;
  }

  return 0;
}