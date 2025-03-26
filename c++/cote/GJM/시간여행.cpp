#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#define GALAXIES 100
#define WORMHOLES 1000
#define MIN_D -1000
#define MAX_D 1000
#define M 10000

using namespace std;

using Graph = vector<vector<pair<int, int>>>;

array<int, 2> split(const string& s) {
  stringstream ss{s};
  istream_iterator<int> it{ss};

  return {*(it++), *(it++)};
}

array<int, 3> get_edge(const string& s) {
  stringstream ss{s};
  istream_iterator<int> it{ss};

  return {*(it++), *(it++), *(it++)};
}

vector<vector<bool>> floyd(Graph& adj) {
  int n = adj.size();
  vector<vector<bool>> ret(n, vector<bool>(n, false));

  for (int cur = 0; cur < n; cur++) {
    for (auto [next, cost] : adj[cur]) {
      ret[cur][next] = true;
    }
  }

  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        ret[i][j] = ret[i][j] || (ret[i][k] && ret[k][j]);
      }
    }
  }

  return ret;
}

int bellman(int src, int target, const Graph& adj,
            const vector<vector<bool>>& reachable) {
  int n = adj.size();
  vector<int> upper(n, numeric_limits<int>::max());
  upper[src] = 0;

  for (int it = 0; it < n - 1; it++) {
    for (int cur = 0; cur < n; cur++) {
      for (auto [next, cost] : adj[cur]) {
        upper[next] = min(upper[next], upper[cur] + cost);
      }
    }
  }

  // 음수 사이클의 존재 여부를 확인
  for (int cur = 0; cur < n; cur++) {
    for (auto [next, cost] : adj[cur]) {
      // 완화가 성공한다면 cur과 next는 모두 음수 사이클 안에 들어있다.
      if (upper[cur] + cost < upper[next]) {
        if (reachable[src][cur] && reachable[cur][target]) {
          return numeric_limits<int>::min();
        }
      }
    }
  }

  return upper[target];
}

void reverse(Graph& graph) {
  for (auto& a : graph) {
    for (auto& [b, d] : a) {
      d = -d;
    }
  }
}

string answer(int result) {
  if (result == numeric_limits<int>::min()) {
    return "INFINITY";
  } else if (result > numeric_limits<int>::max() - M) {
    throw exception{};
  }
  return to_string(result);
}

string answer(int shortest, int largest) {
  try {
    return answer(shortest) + " " + answer(-largest);
  } catch (exception e) {
    return "UNREACHABLE";
  }
}

string solve(Graph& adj) {
  vector<vector<bool>> reachable = floyd(adj);

  int shortest = bellman(0, 1, adj, reachable);

  reverse(adj);
  int largest = bellman(0, 1, adj, reachable);

  return answer(shortest, largest);
}

int main(void) {
  string buf;

  fstream f("./data/시간여행.txt");
  getline(f, buf);
  int test_cases = stoi(buf);

  for (int i = 0; i < test_cases; i++) {
    getline(f, buf);
    auto [galaxies, wormholes] = split(buf);

    Graph graph(galaxies);
    for (int i = 0; i < wormholes; i++) {
      getline(f, buf);
      auto [a, b, d] = get_edge(buf);
      graph[a].push_back({b, d});
    }

    getline(f, buf);
    string answer = buf;

    cout << "answer : " << answer << endl;
    cout << "solved : " << solve(graph) << endl;
  }

  return 0;
}