#include <iostream>
#include <random>
#include <string>
#include <vector>

#define TEST_CASES 10

#define MIN_LENGTH 1000
#define MAX_LENGTH 10000
#define K 1000

using namespace std;

string initialize(default_random_engine& gen) {
  string script;

  int n = gen() % (MAX_LENGTH - MIN_LENGTH + 1) + MIN_LENGTH;

  uniform_int_distribution<int> dis('a', 'm');
  for (int i = 0; i < n; i++) script += dis(gen);

  return script;
}

struct Comparator {
  const vector<int>& group;
  int t;

  Comparator(const vector<int>& group, int t) : group(group), t(t) {}

  bool operator()(int i, int j) {
    if (group[i] != group[j]) return group[i] < group[j];
    return group[i + t] < group[j + t];
  }
};

vector<int> get_suffix_array(const string& s) {
  int n = s.size();
  int t = 1;

  vector<int> group(n + 1);
  for (int i = 0; i < n; i++) group[i] = s[i];
  group[n] = -1;

  vector<int> perm(n);
  for (int i = 0; i < n; i++) perm[i] = i;

  while (t < n) {
    Comparator comp(group, t);
    sort(begin(perm), end(perm), comp);

    t *= 2;
    if (t >= n) break;
    vector<int> newGroup(n + 1);
    newGroup[0] = 0;
    for (int i = 1; i < n; i++) {
      if (comp(perm[i - 1], perm[i]))
        newGroup[perm[i]] = newGroup[perm[i - 1]] + 1;
      else
        newGroup[perm[i]] = newGroup[perm[i - 1]];
    }
    newGroup[n] = -1;
    group = newGroup;
  }

  return perm;
}

int common_prefix(const string& s, int i, int j) {
  int k = 0;

  while (i < s.size() && j < s.size() && s[i] == s[j]) {
    i++;
    j++;
    k++;
  }

  return k;
}

int solve(const string& script, int k) {
  vector<int> pi = get_suffix_array(script);

  int ret = 0;
  int m = 0;

  for (int i = 0; i + k <= script.size(); i++)
    ret = max(ret, common_prefix(script, pi[i], pi[i + k - 1]));

  return ret;
}

int main(void) {
  default_random_engine gen(43);

  for (int it = 0; it < TEST_CASES; it++) {
    string script = initialize(gen);
    int k = gen() % min(K, max(int(script.size() / MIN_LENGTH), 5) - 2) + 2;

    cout << solve(script, k) << endl;
  }

  return 0;
}