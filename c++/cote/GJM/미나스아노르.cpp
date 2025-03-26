#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define C 50
#define N 100
#define INF 987654321

using namespace std;

const double pi = 2.0 * acos(0);

double x[N], y[N];
double r[N];

vector<double>& split(const string& s) {
  stringstream ss(s);
  string buf;

  vector<double>* ret = new vector<double>();

  while (getline(ss, buf, ' ')) {
    ret->push_back(stod(buf));
  }

  return *ret;
}

vector<pair<double, double>>& convetToRange(int n) {
  vector<pair<double, double>>* ret = new vector<pair<double, double>>();

  for (int i = 0; i < n; i++) {
    double loc = fmod(2 * pi + atan2(y[i], x[i]), 2 * pi);
    double range = 2 * asin(r[i] / 2.0 / 8.0);
    ret->push_back(make_pair(loc - range, loc + range));
  }

  return *ret;
}

int solveLinear(double begin, double end, vector<pair<double, double>>& ranges,
                int n) {
  int used = 0;
  int i = 0;

  while (begin < end) {
    double maxCover = -1;

    while (i < n & ranges[i].first <= begin) {
      maxCover = max(maxCover, ranges[i].second);
      i++;
    }
    if (maxCover <= begin) return INF;
    begin = maxCover;
    ++used;
  }

  return used;
}

int solveCircular(vector<pair<double, double>>& ranges, int n) {
  int ret = INF;
  sort(begin(ranges), end(ranges));

  for (int i = 0; i < n; i++) {
    if (ranges[i].first <= 0 || ranges[i].second >= 2 * pi) {
      double begin = fmod(ranges[i].second, 2 * pi);
      double end = fmod(ranges[i].first + 2 * pi, 2 * pi);
      ret = min(ret, 1 + solveLinear(begin, end, ranges, n));
    }
  }

  return ret;
}

string solve(int n) {
  vector<pair<double, double>> ranges = convetToRange(n);

  int ret = solveCircular(ranges, n);

  return (ret >= INF) ? "IMPOSSIBLE" : to_string(ret);
}

int main(void) {
  fstream fd("data/미나스아노르.txt");
  string buf;

  getline(fd, buf);
  int test_cases = stoi(buf);

  while (test_cases > 0) {
    getline(fd, buf);
    int n = stoi(buf);
    int cur = 0;

    while (cur < n) {
      getline(fd, buf);
      vector<double> v = split(buf);

      x[cur] = v[0];
      y[cur] = v[1];
      r[cur] = v[2];
      cur++;
    }

    cout << solve(n) << endl;

    test_cases--;
  }

  return 0;
}