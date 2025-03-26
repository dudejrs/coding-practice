#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#define N 200
#define MAX_LENGTH 20
#define TEST_CASES 10

using namespace std;

vector<string> initialize(default_random_engine& gen) {
  vector<string> ret;
  set<string> set;

  int n = gen() % (10 - 1) + 1;

  while (set.size() < n) {
    int m = gen() % (MAX_LENGTH - 1) + 1;
    char word[m + 1];

    for (int i = 0; i < m; i++) {
      word[i] = gen() % ('z' - 'a' - 1) + 'a';
    }
    word[m] = '\0';

    set.insert(word);
  }

  ret.assign(begin(set), end(set));

  shuffle(begin(ret), end(ret), gen);

  return ret;
}

vector<vector<int>> make_graph(const vector<string>& words) {
  vector<vector<int>> graph(26, vector<int>(26, 0));

  for (int i = 0; i < words.size() - 1; i++) {
    int j = i + 1, m = min(words[i].size(), words[j].size());
    for (int k = 0; k < m; k++) {
      if (words[i][k] != words[j][k]) {
        int a = words[i][k] - 'a';
        int b = words[j][k] - 'a';
        graph[a][b] = 1;
        break;
      }
    }
  }

  return graph;
}

void dfs(int cur, vector<bool>& visited, const vector<vector<int>>& graph,
         vector<int>& order) {
  visited[cur] = true;

  for (int i = 0; i < graph.size(); i++) {
    if (!visited[i] && graph[cur][i]) {
      dfs(i, visited, graph, order);
    }
  }

  order.push_back(cur);
}

string solve(const vector<string>& words) {
  vector<vector<int>> graph = make_graph(words);
  vector<bool> visited(graph.size(), false);
  vector<int> order;

  for (int i = graph.size() - 1; i >= 0; i--) {
    if (!visited[i]) {
      dfs(i, visited, graph, order);
    }
  }

  reverse(begin(order), end(order));

  for (int i = 0; i < order.size(); i++) {
    for (int j = i + 1; j < order.size(); j++) {
      if (graph[order[j]][order[i]]) {
        return "INVALID HYPOTHESIS";
      }
    }
  }

  string s;

  for (const auto& c : order) {
    s.push_back('a' + c);
  }

  return s;
}

int main(void) {
  default_random_engine gen{43};

  for (int it = 0; it < TEST_CASES; it++) {
    vector<string> words = initialize(gen);
    string solved = solve(words);
    cout << solved << endl;
  }

  return 0;
}