#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#define N 50
#define MIN_NUM -1000
#define MAX_NUM -1000
#define EMPTY -987654321

using namespace std;

array<array<int, N>, N> cache;

vector<int> split(const string& s) {
  stringstream ss{s};
  istream_iterator<int> it{ss}, end;

  return {it, end};
}

int play(int left, int right, const vector<int>& nums) {
  if (left > right) return 0;
  int& ret = cache[left][right];

  if (ret != EMPTY) return ret;

  ret = max(nums[left] - play(left + 1, right, nums),
            nums[right] - play(left, right - 1, nums));

  if (right - left + 1 >= 2) {
    ret = max(ret, -play(left + 2, right, nums));
    ret = max(ret, -play(left, right - 2, nums));
  }

  return ret;
}

int solve(const vector<int>& nums) {
  for (auto& a : cache) {
    fill(begin(a), end(a), EMPTY);
  }

  return play(0, nums.size() - 1, nums);
}

int main(void) {
  string buf;
  fstream f("./data/숫자_게임.txt");

  getline(f, buf);
  int test_cases = stoi(buf);

  for (int it = 0; it < test_cases; it++) {
    getline(f, buf);
    int n = stoi(buf);
    getline(f, buf);
    vector<int> nums{split(buf)};
    getline(f, buf);
    int answer = stoi(buf);
    int solved = solve(nums);

    cout << answer << "," << solved << endl;
  }

  return 0;
}