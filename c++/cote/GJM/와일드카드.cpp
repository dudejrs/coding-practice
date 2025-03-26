#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int cache[101][101];

bool match(const string& w, const string& s) {
  int pos = 0;
  while (pos < s.size() && pos < w.size() &&
         (w[pos] == '?' || w[pos] == s[pos])) {
    pos++;
  }

  if (pos == w.size() && pos == s.size()) return true;

  if (w[pos] == '*') {
    for (int i = 0; pos + i <= s.size(); i++) {
      if (match(w.substr(pos + 1), s.substr(pos + i))) return true;
    }
  }

  return false;
}

bool match2(int a, int b, const string& w, const string& s) {
  int& ret = cache[a][b];
  if (ret != -1) return ret;

  while (a < w.size() && b < s.size() && (w[a] == '?' || w[a] == s[b])) {
    a++;
    b++;
  }

  if (a == w.size() && b == s.size()) return true;

  if (w[a] == '*') {
    for (int i = 0; b + i <= s.size(); i++) {
      if (match2(a + 1, b + i, w, s)) return (ret = 1);
    }
  }

  return (ret = 0);
}

bool match3(int a, int b, const string& w, const string& s) {
  int& ret = cache[a][b];
  if (ret != -1) return ret;

  if (a < w.size() && b < s.size() && (w[a] == '?' || w[a] == s[b])) {
    return (ret = match3(a + 1, b + 1, w, s));
  }

  if (a == w.size() && b == s.size()) return true;

  if (w[a] == '*') {
    if (match3(a + 1, b, w, s) || (a < w.size() && match3(a, b + 1, w, s)))
      return (ret = 1);
  }

  return (ret = 0);
}

int main(void) {
  fstream fd("data/와일드카드.txt");
  string buf;

  getline(fd, buf);
  int test_cases = stoi(buf);

  while (test_cases > 0) {
    getline(fd, buf);
    string w = buf;

    vector<string> s;

    getline(fd, buf);
    int n = stoi(buf);

    while (n > 0) {
      memset(cache, -1, sizeof(cache));

      getline(fd, buf);

      if (match3(0, 0, w, buf)) {
        cout << buf << endl;
      }
      n--;
    }

    test_cases--;
  }

  return 0;
}