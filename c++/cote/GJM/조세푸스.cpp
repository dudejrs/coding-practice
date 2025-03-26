#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>

using namespace std;

vector<int> split(const string& s) {
  vector<int> ret;
  stringstream ss(s);
  string buf;

  while (getline(ss, buf, ' ')) {
    ret.push_back(stoi(buf));
  }

  return ret;
}

pair<int, int> solve(int n, int k) {
  list<int> l;

  for (int i = 1; i <= n; i++) l.push_back(i);

  list<int>::iterator it = begin(l);

  while (l.size() > 2) {
    it = l.erase(it);

    if (it == end(l)) it = begin(l);

    for (int i = 0; i < k - 1; i++) {
      it++;
      if (it == end(l)) it = begin(l);
    }
  }

  return make_pair(l.front(), l.back());
}

int main(void) {
  fstream fd("data/조세푸스.txt");
  string buf;
  getline(fd, buf);

  int test_cases = stoi(buf);

  while (test_cases > 0) {
    getline(fd, buf);
    vector<int> n = split(buf);
    pair<int, int> result = solve(n[0], n[1]);
    cout << result.first << " " << result.second << endl;
    test_cases--;
  }

  return 0;
}