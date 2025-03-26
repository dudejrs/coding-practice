#include <iostream>
#include <random>
#include <string>

#define TEST_CASES 10
#define N 100

using namespace std;

vector<int> initialize(default_random_engine& gen) {
  vector<int> ret;
  uniform_int_distribution<int> dis(0, 100);
  int n = abs(dis(gen)) % 5 + 5;

  for (int i = 0; i < n; i++) ret.push_back(abs(dis(gen)));
  return ret;
}

string solve(vector<int>& n) {
  vector<string> s;

  for (int i = 0; i < n.size(); i++) s.push_back(to_string(n[i]));

  sort(begin(s), end(s), [](string a, string b) { return a + b > b + a; });

  string ret;
  for (int i = 0; i < s.size(); i++) ret += s[i];
  return ret;
}

int main(void) {
  default_random_engine gen(43);

  for (int it = 0; it < TEST_CASES; it++) {
    vector<int> n = initialize(gen);

    for (int i = 0; i < n.size(); i++) cout << n[i] << " ";
    cout << endl;

    cout << solve(n) << endl;
  }
  return 0;
}