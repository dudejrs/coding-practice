#include <fstream>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#define V 1000
#define E(v) ((v) * (v - 1) / 2)

using namespace std;

using Graph = vector<vector<pair<int, int>>>;

vector<int> split(const string& s) {
  stringstream ss{s};
  istream_iterator<int> it{ss}, end{};

  return vector<int>(it, end);
}

Graph edgesToGraph(int v, vector<vector<int>>& edges) {
  Graph adj = Graph(v);

  for (auto& edge : edges) {
    int a = edge[0] - 1, b = edge[1] - 1, t = edge[2];

    adj[a].push_back(pair{b, t});
    adj[b].push_back(pair{a, t});
  }

  return adj;
}

int solve(int v, vector<vector<int>>& edges, vector<int>& spots,
          vector<int>& fire_stations) {
  Graph adj = edgesToGraph(v, edges);
  vector<int> dist(v, numeric_limits<int>::max());
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

  for (auto& fire_station : fire_stations) {
    dist[fire_station - 1] = 0;
    pq.push({0, fire_station - 1});
  }

  while (!pq.empty()) {
    const auto [cost, cur] = pq.top();
    pq.pop();

    if (dist[cur] < cost) {
      continue;
    }

    for (const auto [next, weight] : adj[cur]) {
      int next_distance = cost + weight;

      if (next_distance < dist[next]) {
        dist[next] = next_distance;
        pq.push({next_distance, next});
      }
    }
  }

  return accumulate(begin(spots), end(spots), 0, [&dist](int acc, int spot) {
    return acc + dist[spot - 1];
  });
}

int main() {
  string buf;
  fstream f("data/소방차.txt");

  getline(f, buf);
  int test_cases = stoi(buf);

  for (int it = 0; it < test_cases; it++) {
    getline(f, buf);
    vector<int> nums = split(buf);
    int v = nums[0], e = nums[1], n = nums[2], m = nums[3];

    vector<vector<int>> edges;

    for (int i = 0; i < e; i++) {
      getline(f, buf);
      edges.emplace_back(split(buf));
    }

    getline(f, buf);
    vector<int> spots = split(buf);

    getline(f, buf);
    vector<int> fire_stations = split(buf);

    getline(f, buf);
    int answer = stoi(buf);

    cout << answer << " " << solve(v, edges, spots, fire_stations) << endl;
  }

  return 0;
}