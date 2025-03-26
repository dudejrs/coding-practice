#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <sstream>
#include <string>
#include <vector>
#define M 500
#define MAX_TIMES 200
#define START 401

using namespace std;

using Graph = array<vector<pair<int, int>>, 402>;

int vertex(int delta) { return delta + 200; }

array<int, 2> split(const string& s) {
  stringstream ss{s};
  istream_iterator<int> it{ss};

  return {*(it++), *(it)++};
}

Graph make_graph(vector<array<int, 2>>& events) {
  Graph ret;

  for (const auto [a, b] : events) {
    ret[START].push_back({vertex(a - b), a});
  }

  for (int cur = -200; cur <= 200; cur++) {
    for (const auto [a, b] : events) {
      int next = cur + a - b;

      if (abs(next) > 200) {
        continue;
      }
      ret[vertex(cur)].push_back(pair{vertex(next), a});
    }
  }

  return ret;
}

vector<int> dijkstra(int start, Graph& adj) {
  vector<int> dist(adj.size(), numeric_limits<int>::max());
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

  pq.push({0, start});
  dist[start] = 0;

  while (!pq.empty()) {
    auto [cost, cur] = pq.top();
    pq.pop();

    for (auto [next, weight] : adj[cur]) {
      int next_distance = cost + weight;

      if (next_distance < dist[next]) {
        dist[next] = next_distance;
        pq.push({next_distance, next});
      }
    }
  }

  return dist;
}

int solve(vector<array<int, 2>>& events) {
  Graph adj = make_graph(events);

  vector<int> distances = dijkstra(START, adj);

  if (distances[vertex(0)] == numeric_limits<int>::max()) {
    return -1;
  }

  return distances[vertex(0)];
}

int main(void) {
  string buf;
  fstream f("./data/철인_n종_경기.txt");

  getline(f, buf);

  int test_cases = stoi(buf);

  for (int it = 0; it < test_cases; it++) {
    getline(f, buf);
    int m = stoi(buf);

    vector<array<int, 2>> events;
    for (int i = 0; i < m; i++) {
      getline(f, buf);
      events.emplace_back(split(buf));
    }

    getline(f, buf);
    int answer = stoi(buf);

    cout << answer << " " << solve(events) << endl;
  }

  return 0;
}