#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <sstream>
#include <vector>
#define N 8

using namespace std;

vector<int> split(const string& s) {
  stringstream ss{s};
  istream_iterator<int> start{ss}, end{};

  return vector<int>(start, end);
}

int solve1(const vector<int>& nums) {
  vector<int> target = nums;

  sort(begin(target), end(target));
  queue<vector<int>> q;
  map<vector<int>, int> distance;

  distance[nums] = 0;
  q.push(nums);

  while (!q.empty()) {
    vector<int> cur = q.front();
    q.pop();

    if (cur == target) {
      return distance[cur];
    }
    int cost = distance[cur];

    for (int i = 0; i < nums.size(); i++) {
      for (int j = i + 2; j <= nums.size(); j++) {
        vector<int> next = cur;
        reverse(begin(next) + i, begin(next) + j);
        if (distance.count(next) == 0) {
          distance[next] = cost + 1;
          q.push(next);
        }
      }
    }
  }

  return -1;
}

map<vector<int>, int> precalc() {
  map<vector<int>, int> ret;
  for (int n = 1; n <= N; n++) {
    vector<int> perm(n);

    for (int i = 0; i < n; i++) {
      perm[i] = i;
    }

    queue<vector<int>> q;
    q.push(perm);
    ret[perm] = 0;

    while (!q.empty()) {
      vector<int> cur = q.front();
      q.pop();

      int cost = ret[cur];

      for (int i = 0; i < n; i++) {
        for (int j = i + 2; j <= n; j++) {
          vector<int> next = cur;
          reverse(begin(next) + i, begin(next) + j);
          if (next == cur) {
            cout << "." << endl;
          }
          if (ret.count(next) == 0) {
            ret[next] = cost + 1;
            q.push(next);
          }
        }
      }
    }
  }

  return ret;
}

int solve2(const vector<int>& nums, map<vector<int>, int> toSort) {
  int n = nums.size();
  vector<int> fixed(n);

  for (int i = 0; i < n; i++) {
    fixed[i] = count_if(begin(nums), end(nums),
                        [&nums, i](int cur) { return cur < nums[i]; });
  }

  return toSort[fixed];
}

int main(void) {
  string buf;
  fstream fd("data/sorting_game.txt");

  getline(fd, buf);
  int test_cases = stoi(buf);

  map<vector<int>, int> toSort = precalc();

  while (test_cases-- > 0) {
    getline(fd, buf);
    vector<int> nums = split(buf);
    getline(fd, buf);
    int answer = stoi(buf);
    cout << answer << " " << solve1(nums) << " " << solve2(nums, toSort)
         << endl;
  }

  return 0;
}