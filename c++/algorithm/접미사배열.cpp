#include <iostream>
#include <random>
#include <string>

#define TEST_CASES 10
#define MAX_LENGTH 20

using namespace std;

string initialize(default_random_engine& gen) {
  uniform_int_distribution<int> dis('a', 'z');

  int n = gen() % (20 - 10 + 1) + 10;
  string s = "";

  for (int i = 0; i < n; i++) s += dis(gen);

  return s;
}

// O(n^2*lgn)
namespace NaiveSuffixArray {
struct SuffixComparator {
  const string& s;
  SuffixComparator(const string& s) : s(s) {}
  bool operator()(int i, int j) {
    return strcmp(s.c_str() + i, s.c_str() + j) < 0;
  }
};

vector<int> getSuffixArrayNaive(const string& s) {
  vector<int> perm;
  for (int i = 0; i < s.size(); i++) perm.push_back(i);

  sort(begin(perm), end(perm), SuffixComparator(s));
  return perm;
}

void main(void) {}
};  // namespace NaiveSuffixArray

// O(n*lgn^2)
namespace MMSuffixArray {

struct Comparator {
  const vector<int>& group;
  int t;
  Comparator(const vector<int>& group, int t) : group(group), t(t) {}

  bool operator()(int a, int b) {
    if (group[a] != group[b]) return group[a] < group[b];
    return group[a + t] < group[b + t];
  }
};

vector<int> getSuffixArray(const string& s) {
  int n = s.size();

  int t = 1;
  vector<int> group(n + 1);
  for (int i = 0; i < n; i++) group[i] = s[i];
  group[n] = -1;

  vector<int> perm(n);
  for (int i = 0; i < n; i++) perm[i] = i;

  while (t < n) {
    Comparator comp(group, t);
    sort(perm.begin(), perm.end(), comp);

    t *= 2;
    if (t >= n) break;
    vector<int> newGroup(n + 1);
    newGroup[n] = -1;
    newGroup[0] = 0;
    for (int i = 1; i < n; i++) {
      if (comp(perm[i - 1], perm[i]))
        newGroup[perm[i]] = newGroup[perm[i - 1]] + 1;
      else
        newGroup[perm[i]] = newGroup[perm[i - 1]];
    }
    group = newGroup;
  }

  return perm;
}

void main(void) {}
};  // namespace MMSuffixArray

int main(void) {
  default_random_engine gen(43);

  for (int it = 0; it < TEST_CASES; it++) {
    string target = initialize(gen);

    cout << target << endl;

    vector<int> naive = NaiveSuffixArray::getSuffixArrayNaive(target);
    for (int i = 0; i < target.length(); i++) {
      cout << naive[i] << " ";
    }
    cout << endl;

    vector<int> mm = MMSuffixArray::getSuffixArray(target);
    for (int i = 0; i < target.length(); i++) {
      cout << mm[i] << " ";
    }
    cout << endl << endl;
  }

  return 0;
}