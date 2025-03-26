#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void normalize(vector<int>& num) {
  num.push_back(0);

  for (int i = 0; i < num.size(); i++) {
    if (num[i] < 0) {
      int borrow = (abs(num[i]) + 9) / 10;
      num[i + 1] -= borrow;
      num[i] += borrow * 10;
    } else {
      num[i + 1] += num[i] / 10;
      num[i] %= 10;
    }
  }

  if (num.back() == 0) num.pop_back();
}

vector<int> multiply(const vector<int>& a, const vector<int>& b) {
  vector<int> c(a.size() + b.size() + 1, 0);

  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < b.size(); j++) {
      c[i + j] += a[i] * b[j];
    }
  }

  normalize(c);

  return c;
}

void addTo(vector<int>& a, const vector<int>& b, int k) {
  if (a.size() < b.size() + k) {
    for (int i = 0; i < b.size() + k - a.size(); i++) {
      a.push_back(0);
    }
  }

  for (int i = 0; i < b.size(); i++) {
    a[i + k] += b[i];
  }

  normalize(a);
}

void subFrom(vector<int>& a, const vector<int>& b) {
  if (a.size() < b.size()) {
    return;
  }

  if (a.size() == b.size()) {
    int n = a.size();

    while (n >= 0) {
      if (a[n] < b[n]) return;
      n--;
    }
  }

  for (int i = 0; i < b.size(); i++) {
    a[i] -= b[i];
  }

  normalize(a);
}

vector<int> karabatsuba(const vector<int>& a, const vector<int>& b) {
  vector<int> ret;

  int size_a = a.size(), size_b = b.size();
  if (size_a < size_b) return karabatsuba(b, a);
  if (size_a == 0 || size_b == 0) return vector<int>();
  if (size_a <= 50) return multiply(a, b);

  int half = size_a / 2;
  vector<int> a0(begin(a), begin(a) + half);
  vector<int> a1(begin(a) + half, end(a));
  vector<int> b0(begin(b), begin(b) + min<int>(b.size(), half));
  vector<int> b1(begin(b) + min<int>(b.size(), half), end(b));

  vector<int> z2 = karabatsuba(a1, b1);
  vector<int> z0 = karabatsuba(a0, b0);

  addTo(a0, a1, 0);
  addTo(b0, b1, 0);
  vector<int> z1 = karabatsuba(a0, b0);
  subFrom(z1, z0);
  subFrom(z1, z2);

  addTo(ret, z0, 0);
  addTo(ret, z1, half);
  addTo(ret, z2, half * 2);

  return ret;
}

int print(vector<int>& a) {
  ostringstream oss;

  for (int i = a.size() - 1; i >= 0; i--) {
    oss << a[i];
  }

  return stoi(oss.str());
}

int main(void) {
  vector<int> a = {1, 2, 3, 4};
  vector<int> b = {1, 3};
  vector<int> z = karabatsuba(a, b);

  cout << (4321 * 31) << ", " << print(z) << endl;

  return 0;
}