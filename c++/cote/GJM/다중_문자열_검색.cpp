#include <algorithm>
#include <iostream>
#include <queue>
#include <random>
#include <sstream>
#include <vector>
#define TEST_CASES 10
#define ALPHABETS 26
#define N 10000
#define M 1000
#define P 100

using namespace std;

inline int to_number(char ch) { return ch - 'A'; }

inline char to_char(int n) { return static_cast<char>('A' + n); }

struct Node {
  Node* children[ALPHABETS];
  int terminal = -1;  // 현 위치에서 끝나는 문자열의 번호
  Node* fail = nullptr;
  vector<int> output;  // 이 노드가 방문되었을 때 등장하는 바늘 문자열들의 번호

  Node() {
    for (int i = 0; i < ALPHABETS; i++) {
      children[i] = nullptr;
    }
  }

  ~Node() {
    for (int i = 0; i < ALPHABETS; i++) {
      if (children[i]) {
        delete children[i];
      }
    }
  }

  void insert(const char* key, int id) {
    if (*key == 0) {
      terminal = id;
    } else {
      int next = to_number(*key);
      if (children[next] == nullptr) {
        children[next] = new Node();
      }
      children[next]->insert(key + 1, id);
    }
  }
};

string generate_corpus(default_random_engine& gen) {
  uniform_int_distribution<int> dis(0, ALPHABETS - 1);
  stringstream ss;

  int n = gen() % (N - 1) + 1;

  for (int i = 0; i < n; i++) {
    ss << to_char(dis(gen));
  }

  return ss.str();
}

vector<string> generate_words(default_random_engine& gen,
                              const string& corpus) {
  vector<string> ret;

  int m = gen() % N - 500 + 500;
  int p = gen() % (min(static_cast<int>(corpus.length()), M) - 2) + 2;

  normal_distribution<float> dis(m / p, 3);

  while (ret.size() < p) {
    int i = gen() % static_cast<int>(corpus.length());
    int n = gen() % (static_cast<int>(abs(dis(gen))) - 2) + 2;

    if (i < static_cast<int>(corpus.length()) - n) {
      ret.push_back(corpus.substr(i, n));
    }
  }

  return ret;
}

Node* make_trie(const vector<string>& words) {
  Node* trie = new Node();

  for (int i = 0; i < words.size(); i++) {
    trie->insert(words[i].c_str(), i);
  }

  return trie;
}

// 트라이가 주어질 때 각 노드에 대해 실패 연결과 출력 문자열 목록을 계산
void compute_fail(Node* root) {
  queue<Node*> q;

  root->fail = root;
  q.push(root);

  while (!q.empty()) {
    Node* cur = q.front();
    q.pop();

    for (int i = 0; i < ALPHABETS; i++) {
      Node* child = cur->children[i];

      if (!child) continue;

      // 1레벨 노드의 실패 연결은 항상 루트
      if (cur == root) {
        child->fail = root;

        // 1레벨 이상의 노드는 부모의 실패 연결을 따라가면서 실패 연결을 찾는다
      } else {
        Node* t = cur->fail;
        while (t != root && t->children[i] == nullptr) {
          t = t->fail;
        }

        if (t->children[i]) {
          t = t->children[i];
        }
        child->fail = t;
      }

      child->output = child->fail->output;

      if (child->terminal != -1) {
        child->output.push_back(child->terminal);
      }
      q.push(child);
    }
  }
}

vector<pair<int, int>> solve(const string& corpus,
                             const vector<string>& words) {
  vector<pair<int, int>> ret;

  Node* root = make_trie(words);
  compute_fail(root);

  Node* state = root;

  for (int i = 0; i < corpus.size(); i++) {
    int chr = to_number(corpus[i]);
    while (state != root && state->children[chr] == nullptr) {
      state = state->fail;
    }

    if (state->children[chr]) {
      state = state->children[chr];
    }
    for (auto j : state->output) {
      ret.push_back(make_pair(i, j));
    }
  }

  return ret;
}

int main(void) {
  default_random_engine gen(43);

  for (int i = 0; i < TEST_CASES; i++) {
    const string corpus = generate_corpus(gen);
    vector<string> words = generate_words(gen, corpus);

    vector<pair<int, int>> occurances = solve(corpus, words);

    for (auto o : occurances) {
      cout << "(" << o.first << "," << o.second << ") ";
    }
    cout << endl;
  }

  return 0;
}