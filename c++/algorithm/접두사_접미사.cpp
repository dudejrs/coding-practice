#include <iostream>
#include <random>
#include <string>

#define TEST_CASES 10
#define MAX_MODULE 10
#define MIN_MODULE 5
#define MAX_SAMPLE 30
#define MIN_SAMPLE 10
#define MSIZE 1000

using namespace std;

void initialize(string& m, default_random_engine& gen) {
  uniform_int_distribution<int> dis('a', 'c');

  int n = gen() % (MAX_MODULE - MIN_MODULE + 1) + MIN_MODULE;

  for (int i = 0; i < n; i++) {
    int sample = gen() % (MAX_SAMPLE - MIN_SAMPLE + 1) + MIN_SAMPLE;
    while (sample > 0) {
      m += dis(gen);
      sample--;
    }
  }

  string reverse;
  for (int i = 0; i < n; i++) {
    reverse += m[n - i - 1];
  }

  m += reverse;
}

vector<int> get_partial_match(const string& m) {
  vector<int> pi(m.size(), 0);

  for (int begin = 1; begin < m.size(); begin++) {
    for (int i = 0; i < m.size(); i++) {
      if (m[begin + i] != m[i]) break;

      pi[begin + i] = max(pi[begin + i], i + 1);
    }
  }

  return pi;
}

vector<int> solve(const string& m) {
  vector<int> ret;

  vector<int> pi = get_partial_match(m);

  int k = m.size();
  while (k > 0) {
    ret.push_back(k);
    k = pi[k - 1];
  }

  return ret;
}

int main(void) {
  default_random_engine gen(43);

  for (int it = 0; it < TEST_CASES; it++) {
    string m;
    initialize(m, gen);
    vector<int> ret = solve(m);
    cout << m << endl;
    for (auto r : ret) {
      cout << r << " ";
    }
    cout << endl;
  }

  return 0;
}