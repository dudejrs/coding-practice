#include <iostream>
#include <vector>

using namespace std;

void printPicked(vector<int>& picked) {
  cout << "( ";
  for (auto item : picked) {
    cout << item << " ";
  }
  cout << ")" << endl;
}

void pick(int n, int toPick, vector<int>& picked) {
  if (toPick == 0) {
    printPicked(picked);
    return;
  }

  int smallest = picked.empty() ? 0 : picked.back() + 1;

  for (int next = smallest; next < n; ++next) {
    picked.push_back(next);
    pick(n, toPick - 1, picked);
    picked.pop_back();
  }
}

void solve(int n, int k) {
  vector<int> picked;

  pick(n, k, picked);
}

int main(void) {
  solve(4, 2);
  return 0;
}