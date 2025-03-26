#include <iostream>
#include <random>
#include <vector>
#define TEST_CASES 10
#define MAX_VAL 987654321
#define N 10

using namespace std;

vector<pair<int, int>> euclidan_to_display(vector<pair<int, int>>& points,
                                           int minX, int minY, int maxX,
                                           int maxY) {
  vector<pair<int, int>> ret;

  for (auto p : points) {
    int x = p.first - minX;
    int y = maxY - p.second;

    ret.push_back(make_pair(x, y));
  }

  return ret;
}

pair<int, int> getMinimum(vector<pair<int, int>>& points) {
  int minX = MAX_VAL;
  int minY = MAX_VAL;

  for (auto p : points) {
    if (p.first < minX) minX = p.first;
    if (p.second < minY) minY = p.second;
  }

  return make_pair(minX, minY);
};
pair<int, int> getMaximum(vector<pair<int, int>>& points) {
  int maxX = -MAX_VAL;
  int maxY = -MAX_VAL;

  for (auto p : points) {
    if (p.first > maxX) maxX = p.first;
    if (p.second > maxY) maxY = p.second;
  }

  return make_pair(maxX, maxY);
};

int main(void) {
  default_random_engine gen(43);

  for (int it = 0; it < TEST_CASES; it++) {
    normal_distribution<float> dis(0, 400);

    vector<pair<int, int>> points;

    for (int i = 0; i < N; i++) {
      int x = floor(dis(gen));
      int y = floor(dis(gen));
      points.push_back(make_pair(x, y));
    }
    pair<int, int> p1 = getMinimum(points);
    pair<int, int> p2 = getMaximum(points);

    vector<pair<int, int>> result =
        euclidan_to_display(points, p1.first, p1.second, p2.first, p2.second);

    for (int i = 0; i < N; i++) {
      cout << "(" << points[i].first << "," << points[i].second << ") ---> "
           << "(" << result[i].first << "," << result[i].second << ")" << endl;
    }
    cout << endl;
  }

  return 0;
}