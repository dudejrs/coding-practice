#include <iostream>
#include <vector>

using namespace std;

template <typename T>
struct Node {
  Node* representitive;
  T value;
  Node* next;

  Node(T value) : representitive(this), value(value), next(nullptr) {}
};

template <typename T>
struct DisjointSet {
  DisjointSet(int n) {}

  virtual int find(int a) = 0;
  virtual bool merge(int a, int b) = 0;
};

template <typename T>
struct LinkedListDisjointSet : DisjointSet<T> {
  vector<Node<T>*> groups;

  LinkedListDisjointSet(int n) : DisjointSet<T>(n), groups(0) {
    for (int i = 0; i < n; i++) {
      groups.push_back(new Node<T>(i));
    }
  }

  void _changeRoot(int rootA, int rootB) {
    if (find(rootA) != rootA || find(rootB) != rootB) return;

    Node<T>* cur = groups[rootA];
    while (cur->next != nullptr) {
      cur = cur->next;
    }
    cur->next = groups[rootB];
    cur = groups[rootB];

    while (cur != nullptr) {
      cur->representitive = groups[rootA];
      cur = cur->next;
    }
  }

  int find(int a) override {
    Node<T>* r = groups[a]->representitive;
    int i = 0;
    for (auto group : groups) {
      if (r == group) break;
      i++;
    }

    return i;
  }

  bool merge(int a, int b) override {
    int rootA = find(a);
    int rootB = find(b);

    if (rootA == rootB) return false;

    if (a < b)
      _changeRoot(rootA, rootB);
    else
      _changeRoot(rootB, rootA);

    return true;
  }
};

int main(void) {
  LinkedListDisjointSet<int> llds(10);

  for (int i = 0; i < 10; i++) {
    cout << llds.find(i) << " ";
  }
  cout << endl;

  llds.merge(0, 1);
  llds.merge(1, 2);
  llds.merge(8, 9);

  for (int i = 0; i < 10; i++) {
    cout << llds.find(i) << " ";
  }
  cout << endl;

  return 0;
}