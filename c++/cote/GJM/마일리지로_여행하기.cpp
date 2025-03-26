#include <functional>
#include <iostream>
#include <limits>
#include <numeric>
#include <queue>
#include <random>
#include <vector>
#define M 100
#define P 100
#define MAX_AMOUNT 100
#define TEST_CASES 10

using namespace std;

struct Edge {
  int target, capacity, flow;
  Edge* reverse;

  int get_residual_capacity() { return capacity - flow; }

  void push(int amount) {
    flow += amount;
    reverse->flow -= amount;
  }
};

struct AmountGenerator {
  AmountGenerator(default_random_engine& gen) : gen(gen) {}

  int operator()() { return abs(floor(dis(gen))) * 1000; }

 private:
  default_random_engine& gen;
  normal_distribution<float> dis{MAX_AMOUNT / 2, MAX_AMOUNT / 4};
};

int source() { return 0; }

int milege(int i) { return i + 1; }

int price(int m, int i) { return m + i + 1; }

int sink(int m, int p) { return m + p + 1; }

void addEdge(int u, int v, int capacity, vector<vector<Edge*>>& adj) {
  Edge* uv = new Edge();
  Edge* vu = new Edge();

  uv->target = v;
  uv->capacity = capacity;
  uv->flow = 0;
  uv->reverse = vu;

  vu->target = u;
  vu->capacity = 0;
  vu->flow = 0;
  vu->reverse = uv;

  adj[u].push_back(uv);
  adj[v].push_back(vu);
}

vector<vector<Edge*>> initiailze(vector<int>& mileges, vector<int>& prices,
                                 vector<pair<int, int>>& availables) {
  int m = mileges.size(), p = prices.size();
  vector<vector<Edge*>> ret(m + p + 2);

  for (int i = 0; i < m; i++) {
    addEdge(source(), milege(i), mileges[i], ret);
  }

  for (auto [i, j] : availables) {
    addEdge(milege(i), price(m, j), numeric_limits<int>::max(), ret);
  }

  for (int i = 0; i < p; i++) {
    addEdge(price(m, i), sink(m, p), prices[i], ret);
  }

  return ret;
}

vector<int> getAmounts(int n, function<int()> amount) {
  vector<int> ret(n, 0);

  for (int i = 0; i < n; i++) {
    ret[i] = amount();
  }

  return ret;
}

vector<pair<int, int>> getAvailables(int m, int p,
                                     function<bool()> is_available) {
  vector<pair<int, int>> ret;

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < p; j++) {
      if (!is_available()) {
        continue;
      }
      ret.push_back({i, j});
    }
  }

  return ret;
}

int solve(vector<int>& mileges, vector<int>& prices,
          vector<pair<int, int>>& availables) {
  int m = mileges.size(), p = prices.size();
  vector<vector<Edge*>> adj{initiailze(mileges, prices, availables)};

  int total_amount = 0;

  while (true) {
    vector<int> parent(m + p + 2, -1);
    vector<Edge*> selected(m + p + 2, nullptr);
    queue<int> q;
    q.push(source());
    parent[source()] = source();

    while (!q.empty()) {
      int cur = q.front();
      q.pop();

      if (cur == sink(m, p)) {
        break;
      }

      for (auto* e : adj[cur]) {
        int next = e->target;
        if (e->get_residual_capacity() > 0 && parent[next] == -1) {
          q.push(next);
          parent[next] = cur;
          selected[cur] = e;
        }
      }
    }

    if (parent[sink(m, p)] == -1) {
      break;
    }
    int amount = numeric_limits<int>::max();

    for (int c = sink(m, p); c != source(); c = parent[c]) {
      amount = min(amount, selected[parent[c]]->get_residual_capacity());
    }

    for (int c = sink(m, p); c != source(); c = parent[c]) {
      selected[parent[c]]->push(amount);
    }

    total_amount += amount;
  }

  return accumulate(begin(prices), end(prices), 0) - total_amount;
}

int main(void) {
  default_random_engine gen(23);

  auto is_available{bind(bernoulli_distribution{0.5}, gen)};
  AmountGenerator amount{gen};

  for (int it = 0; it < TEST_CASES; it++) {
    int m = gen() % (M - 2) + 2;
    int p = gen() % (P - 2) + 2;
    vector<int> mileges{getAmounts(m, amount)};
    vector<int> prices{getAmounts(p, amount)};
    vector<pair<int, int>> availables{getAvailables(m, p, is_available)};

    cout << solve(mileges, prices, availables) << endl;
  }

  return 0;
}