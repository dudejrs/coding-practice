#include <iostream>
#include <random>
#include <vector>
#define N 100
#define Y 100
#define X 100
#define TEST_CASES 10

using namespace std;
using Location = pair<int, int>;
using Area = pair<Location, Location>;

Location get_location(int y0, int x0, int y1, int x1,
                      default_random_engine& gen) {
  int y = gen() % (y1 - y0) + y0;
  int x = gen() % (x1 - x0) + x0;

  return {y, x};
}

vector<Area> get_area(int n, default_random_engine& gen) {
  vector<Area> ret;

  for (int i = 0; i < n; i++) {
    Location l1{get_location(1, 1, Y, X, gen)};
    Location l2{get_location(0, 0, l1.first, l1.second, gen)};
    ret.emplace_back(l2, l1);
  }

  return ret;
}

vector<Location> derived_from(vector<Area>& area, default_random_engine& gen) {
  vector<Location> ret;

  for (auto [l1, l2] : area) {
    ret.push_back(
        {get_location(l1.first, l1.second, l2.first, l2.second, gen)});
  }

  return ret;
}

bool is_in(Location& picture, Area& area) {
  auto [l1, l2] = area;
  auto [y, x] = picture;

  if (y < l1.first || y > l2.first) {
    return false;
  }

  if (x < l1.second || x > l2.second) {
    return false;
  }

  return true;
}

vector<vector<int>> get_adjacent(vector<Area>& area,
                                 vector<Location>& pictures) {
  int n = area.size();
  vector<vector<int>> ret(n);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (is_in(pictures[i], area[j])) {
        ret[i].push_back(j);
      }
    }
  }

  return ret;
}

bool dfs(int a, vector<int>& area_match, vector<int>& picture_match,
         vector<bool>& visited, vector<vector<int>>& adj) {
  if (visited[a]) {
    return false;
  }
  visited[a] = true;

  for (auto p : adj[a]) {
    if (picture_match[p] == -1 ||
        dfs(picture_match[p], area_match, picture_match, visited, adj)) {
      area_match[a] = p;
      picture_match[p] = a;

      return true;
    }
  }

  return false;
}

vector<int> solve(vector<Area>& area, vector<Location>& pictures) {
  int n = area.size();
  vector<vector<int>> adj{get_adjacent(area, pictures)};

  vector<int> area_match(n, -1);
  vector<int> picture_match(n, -1);

  for (int i = 0; i < n; i++) {
    vector<bool> visited(n, false);
    dfs(i, area_match, picture_match, visited, adj);
  }

  return picture_match;
}

int main(void) {
  default_random_engine gen{43};

  for (int it = 0; it < TEST_CASES; it++) {
    int n = gen() % (N - 3) + 3;
    vector<Area> area{get_area(n, gen)};
    vector<Location> pictures{derived_from(area, gen)};
    shuffle(begin(pictures), end(pictures), gen);
    vector<int> solved{solve(area, pictures)};

    for (auto matched : solved) {
      cout << matched << " ";
    }
    cout << endl;
  }

  return 0;
}