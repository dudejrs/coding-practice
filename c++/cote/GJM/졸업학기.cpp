#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define INF 987654321
#define MAXN 12
#define MAXM 10

using namespace std;

int n, k, m, r;
int* prerequisite;
int* classes;
int cache[MAXM][1 << MAXN];

vector<int> split(const string& s) {
  vector<int> ret;
  stringstream ss(s);
  string buf;

  while (getline(ss, buf, ' ')) {
    ret.push_back(stoi(buf));
  }

  return ret;
}

int graduate(int semester, int taken) {
  // cout << semester << "," << taken << endl;
  if (__builtin_popcount(taken) >= k) return 0;
  if (semester == m) return INF;

  int& ret = cache[semester][taken];
  if (ret != -1) return ret;
  ret = INF;

  int canTake = (classes[semester] & ~taken);

  for (int i = 0; i < n; i++)
    if ((canTake & (1 << i) && (prerequisite[i] & taken) != prerequisite[i]))
      canTake &= ~(1 << i);

  for (int set = canTake; set > 0; set = (canTake & (set - 1))) {
    if (__builtin_popcount(taken) > r) continue;
    ret = min(ret, graduate(semester + 1, taken | set) + 1);
  }
  ret = min(ret, graduate(semester + 1, taken));
  return ret;
}

string solve() {
  memset(cache, -1, sizeof(cache));
  int ret = graduate(0, 0);
  if (ret > 0 && ret <= m) return to_string(ret);

  return "IMPOSSIBLE";
}

int main(void) {
  fstream fd("data/졸업학기.txt");
  string buf;

  getline(fd, buf);
  int test_cases = stoi(buf);

  while (test_cases > 0) {
    getline(fd, buf);
    vector<int> result = split(buf);

    n = result[0];
    k = result[1];
    m = result[2];
    r = result[3];
    prerequisite = new int[n];
    classes = new int[m];

    for (int i = 0; i < n; i++) {
      getline(fd, buf);
      vector<int> tmp = split(buf);

      int cur = 0;
      for (int j = 1; j <= tmp[0]; j++) {
        cur |= (1 << tmp[j]);
      }

      prerequisite[i] = cur;
    }

    for (int i = 0; i < m; i++) {
      getline(fd, buf);
      vector<int> tmp = split(buf);
      int cur = 0;
      for (int j = 1; j <= tmp[0]; j++) {
        cur |= (1 << tmp[j]);
      }
      classes[i] = cur;
    }

    cout << solve() << endl;

    delete[] prerequisite;
    delete[] classes;

    test_cases--;
  }

  return 0;
}