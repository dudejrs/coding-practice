#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<pair<int, int>> split(const string& s) {
  vector<pair<int, int>> ret;
  stringstream ss(s);
  string buf;

  while (getline(ss, buf, ' ')) {
    int first = stoi(buf);
    getline(ss, buf, ' ');
    int second = stoi(buf);

    ret.push_back(make_pair(first, second));
  }

  return ret;
}

int solve(vector<pair<int, int>>& cost, vector<pair<int, int>>& order) {
  int ret = 0;
  int last_month = 0;

  for (int i = 0; i < order.size(); i++)
    if (last_month < order[i].first) last_month = order[i].first;

  int month_order[last_month];
  memset(month_order, 0, sizeof(month_order));

  int total_order = 0;
  for (int i = 0; i < order.size(); i++) {
    month_order[order[i].first] = order[i].second;
    total_order += order[i].second;
  }

  int left_order = total_order;

  for (int k = 0; k < cost.size() - 1; k++) {
    int month_limit = cost[k + 1].first - cost[k].first;
    int price = cost[k].second;
    int products = 0;

    for (int m = 0; m < last_month; m++) {
      if (left_order <= 0) break;

      int cur_produce = min(month_limit, left_order);

      ret += cur_produce * price;
      products += cur_produce;
      left_order -= cur_produce;

      if (month_order[m] > 0) {
        int product_delivered = min(month_order[m], products);
        products -= product_delivered;
        month_order[m] -= product_delivered;
      }
    }
  }

  ret += (cost[cost.size() - 1].second) * left_order;
  return ret;
}

int main(void) {
  fstream fd("data/자전거_공장.txt");
  string buf;

  getline(fd, buf);
  int test_cases = stoi(buf);

  while (test_cases > 0) {
    getline(fd, buf);
    vector<pair<int, int>> cost = split(buf);

    getline(fd, buf);
    vector<pair<int, int>> order = split(buf);

    cout << solve(cost, order) << endl;

    test_cases--;
  }

  return 0;
}