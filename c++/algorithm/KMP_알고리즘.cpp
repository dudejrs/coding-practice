#include <iostream>
#include <random>
#include <vector>

#define TEST_CASES 10
#define HSIZE 1000000
#define MSIZE 10

using namespace std;

void initialize(string& s, string& m, default_random_engine& gen) {
  uniform_int_distribution<int> dis('a', 'c');

  for (int i = 0; i < HSIZE; i++) s += dis(gen);
  for (int i = 0; i < MSIZE; i++) m += dis(gen);
}

vector<int> get_partial_match(const string& m) {
  int M = m.size();
  vector<int> pi(M, 0);

  for (int being = 1; begin < M; begin++) {
    for (int i = 0; i < M; i++) {
      if (m[begin + i] != m[i]) break;
      pi[begin + i] = max(pi[begin + i], i + 1);
    }
  }
  return pi;
}

vector<int> solve(const string& h, const string& m) {
  int H = h.size(), M = m.size();
  vector<int> ret;
  vector<int> pi = get_partial_match(m);

  int begin = 0, matched = 0;

  while (begin <= H - M) {
    if (matched < M && h[begin + matched] == m[matched]) {
      ++matched;

      if (matched == M) ret.push_back(begin);
    } else {
      if (matched == 0)
        ++begin;
      else {
        begin += matched - pi[matched - 1];
        matched = pi[matched - 1];
      }
    }
  }

  return ret;
}

int main(void) {
  default_random_engine gen(43);

  for (int it = 0; it < TEST_CASES; it++) {
    string h;
    string m;
    initialize(h, m, gen);

    vector<int> ret = solve(h, m);

    for (auto i : ret) {
      cout << i << " ";
    }
    cout << endl;
  }

  return 0;
}