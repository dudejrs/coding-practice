#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

vector<int>& geth(const string& s) {
  vector<int>* result = new vector<int>();
  stringstream ss(s);
  string temp;

  while (getline(ss, temp, ' ')) {
    result->push_back(stoi(temp));
  }

  return *result;
}

int solve(vector<int>& h, int left, int right) {
  if (left == right) return h[left];

  // divide
  int mid = (left + right) / 2;
  int ret = max(solve(h, left, mid), solve(h, mid + 1, right));

  // merge
  int low = mid;
  int high = mid + 1;
  int height = min(h[low], h[high]);
  ret = max(ret, height * 2);

  while (left < low || high < right) {
    if (left < low && (high == right || h[high + 1] < h[low - 1])) {
      low--;
      height = min(height, h[low]);
    } else {
      high++;
      height = min(height, h[high]);
    }

    ret = max(ret, height * (high - low + 1));
  }

  return ret;
}

int main(void) {
  fstream fd("data/울타리_잘라내기.txt");
  string buf;

  getline(fd, buf);
  int test_cases = stoi(buf);

  while (test_cases > 0) {
    getline(fd, buf);
    int n = stoi(buf);

    getline(fd, buf);
    vector<int> h = geth(buf);

    cout << solve(h, 0, n - 1) << endl;

    test_cases--;
  }

  return 0;
}