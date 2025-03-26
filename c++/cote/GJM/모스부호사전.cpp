#include <cmath>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

#define TEST_CASES 10
#define MAX_ 10
#define M 1000000100

using namespace std;

int skip;
int bino[MAX_ * 2 + 1][MAX_ * 2 + 1];

void generate(int n, int m, string s, ostringstream& oss) {
  if (skip < 0) return;

  if (n == 0 && m == 0) {
    if (skip == 0) {
      oss << s;
    }

    skip--;
    return;
  }

  if (n > 0) generate(n - 1, m, s + "-", oss);
  if (m > 0) generate(n, m - 1, s + "o", oss);
}

void calcBino() {
  memset(bino, 0, sizeof(bino));

  for (int i = 0; i < MAX_ * 2 + 1; i++) {
    bino[i][0] = bino[i][i] = 1;
    for (int j = 1; j < i; j++) {
      bino[i][j] = min(M, bino[i - 1][j] + bino[i - 1][j - 1]);
    }
  }
}

void generate2(int n, int m, string s, ostringstream& oss) {
  if (skip < 0) return;

  if (n == 0 && m == 0) {
    if (skip == 0) {
      oss << s;
    }

    skip--;
    return;
  }

  if (bino[n + m][n] <= skip) {
    skip -= bino[n + m][n];
    return;
  }

  if (n > 0) generate2(n - 1, m, s + "-", oss);
  if (m > 0) generate2(n, m - 1, s + "o", oss);
}

string generate3(int n, int m, int k) {
  if (n == 0) return string(m, 'o');
  if (k < bino[n + m - 1][n - 1]) return "-" + generate3(n - 1, m, k);
  return "o" + generate3(n, m - 1, k - bino[n + m - 1][n - 1]);
}

string solve(int n, int m, int k) {
  ostringstream oss;

  skip = k - 1;
  // generate(n,m,"",oss);

  calcBino();
  generate2(n, m, "", oss);

  return oss.str();
}

int main(void) {
  default_random_engine gen(43);
  uniform_int_distribution<int> dis(0, MAX_);

  for (int i = 0; i < TEST_CASES; i++) {
    int n = dis(gen);
    int m = dis(gen);
    int k = dis(gen) % (n + m) + 1;

    cout << n << " " << m << " " << k << endl;
    cout << solve(n, m, k) << endl;
    // cout << generate3(n,m,k) << endl;
  }

  return 0;
}