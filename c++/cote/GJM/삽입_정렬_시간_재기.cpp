#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#define TEST_CASES 10
#define N 50000
#define MAX_VALUE 1000000

using namespace std;

struct FenwickTree {
  vector<int> tree;

  FenwickTree(int n) : tree(n + 1) {}

  // A[0..p]의 부분합을 구한다
  int sum(int p) {
    // 인덱스가 1부터 싲가한다고 가정
    ++p;

    int ret = 0;

    while (p > 0) {
      ret += tree[p];
      p &= (p - 1);
    }

    return ret;
  }

  // A[p]에 val을 더한다
  void add(int p, int v) {
    ++p;

    while (p < tree.size()) {
      tree[p] += v;
      p += (p & -p);
    }
  }
};

// 펜윅트리를 이용한 풀이
long long solve(const vector<int>& a) {
  // a[i]가 몇번 나왔는지 저장 해 놓는 펜윅 트리
  FenwickTree tree(MAX_VALUE);
  long long ret = 0;

  for (int i = 0; i < a.size(); i++) {
    // a[i]보다 높은 값이 몇번 나왔는지 계산
    ret += tree.sum(MAX_VALUE - 1) - tree.sum(a[i]);
    tree.add(a[i], 1);
  }

  return ret;
}

long long count(vector<int>& a, int left, int right) {
  if (left == right) return 0;

  int mid = (left + right) / 2;

  long long ret = count(a, left, mid) + count(a, mid + 1, right);

  vector<int> tmp(right - left + 1);
  int i = left, j = mid + 1, k = 0;
  while (i <= mid || j <= right) {
    if (i <= mid && (j > right || a[i] <= a[j])) {
      tmp[k] = a[i];
      k++;
      i++;
    } else {
      ret += mid - i + 1;
      tmp[k] = a[j];
      k++;
      j++;
    }
  }

  copy(begin(tmp), end(tmp), begin(a) + left);

  return ret;
}

// 병합 정렬을 이용한 풀이
long long solve2(vector<int>& a) { return count(a, 0, a.size() - 1); }

int main(void) {
  default_random_engine gen(43);
  uniform_int_distribution<int> dis(1, MAX_VALUE);

  for (int it = 0; it < TEST_CASES; it++) {
    int n = gen() % (N - 1) + 1;
    vector<int> nums(n);

    for (int i = 0; i < n; i++) {
      nums[i] = dis(gen);
    }

    cout << solve(nums) << " " << solve2(nums) << endl;
  }

  return 0;
}