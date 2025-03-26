#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

template <typename T>
struct Node {
  T value;
  int priority;
  Node<T>*left, *right;
  int size;

  Node(T value, Node<T>* left, Node<T>* right)
      : value(value), left(left), right(right), priority(random()), size(0) {}
  Node(T value) : Node(value, nullptr, nullptr) {}

  void set_left(Node<T>* left_) {
    left = left_;
    calcSize();
  }

  void set_right(Node<T>* right_) {
    right = right_;
    calcSize();
  }

  void calcSize() {
    size = 1;
    if (left) size += left->size;
    if (right) size += right->size;
  }

  T min() {
    if (!left) return value;
    return left->min();
  }

  T max() {
    if (!right) return value;
    return right->max();
  }
};

template <typename T>
using NodePair = pair<Node<T>*, Node<T>*>;

template <typename T>
NodePair<T> split(Node<T>* root, T key) {
  if (root == nullptr) {
    return {nullptr, nullptr};
  }

  if (root->value < key) {
    NodePair<T> right_side = split(root->right, key);
    root->set_right(right_side.first);
    return {root, right_side.second};
  }

  NodePair<T> left_side = split(root->left, key);
  root->set_left(left_side.second);

  return {left_side.first, root};
}

template <typename T>
Node<T>* insert(Node<T>* root, Node<T>* node) {
  if (root == nullptr) return node;
  if (node->priority > root->priority) {
    NodePair<T> splitted = split(root, node->value);
    node->set_left(splitted.first);
    node->set_right(splitted.second);
    return node;
  }

  if (node->value < root->value) {
    root->set_left(insert(root->left, node));
    return root;
  }

  root->set_right(insert(root->right, node));
  return root;
}

template <typename T>
Node<T>* merge(Node<T>* a, Node<T>* b) {
  // assert(a->max() < b->min());

  if (a == nullptr) return b;
  if (b == nullptr) return a;

  if (a->priority < b->priority) {
    b->set_left(merge(a, b->left));
    return b;
  }

  a->set_right(merge(a->right, b));
  return a;
}

template <typename T>
Node<T>* erase(Node<T>* root, T key) {
  if (root == nullptr) return root;
  if (root->value == key) {
    Node<T>* ret = merge(root->left, root->right);
    delete root;
    return ret;
  }
  if (key < root->value) {
    root->set_left(erase(root->left, key));
    return root;
  }
  root->set_right(erase(root->right, key));

  return root;
}

template <typename T>
Node<T>* kth(Node<T>* root, int k) {
  int left_side = 0;
  if (root->left) left_side = root->left->size;
  if (k <= left_side) return kth(root->left, k);
  if (k == left_side + 1) return root;
  return kth(root->right, k - left_side - 1);
}

template <typename T>
int countLessThan(Node<T>* root, T key) {
  if (root) return 0;
  if (root->value >= key) return countLessThan(root->left, key);
  int left_side = (root->left ? root->left->size : 0);
  return left_side + 1 + countLessThan(root->right, key);
}

int* split_string(string s, int n) {
  stringstream ss(s);
  string buf;
  int* ret = new int[n];

  for (int i = 0; i < n; i++) {
    getline(ss, buf, ' ');
    ret[i] = stoi(buf);
  }

  return ret;
}

int* solve(int* shifted, int n) {
  Node<int>* candidates = nullptr;
  int* answer = new int[n];

  for (int i = 0; i < n; i++)
    candidates = insert(candidates, new Node<int>(i + 1));

  for (int i = n - 1; i >= 0; i--) {
    int larger = shifted[i];
    Node<int>* k = kth(candidates, i + 1 - larger);
    answer[i] = k->value;
    candidates = erase(candidates, k->value);
  }

  return answer;
}

int main(void) {
  fstream fd("data/삽입_정렬_뒤집기.txt");
  string buf;

  getline(fd, buf);
  int test_cases = stoi(buf);

  while (test_cases > 0) {
    getline(fd, buf);
    int n = stoi(buf);
    getline(fd, buf);
    int* shifted = split_string(buf, n);
    getline(fd, buf);
    int* answer = split_string(buf, n);

    cout << "answer : [ ";
    for (int i = 0; i < n; i++) {
      cout << answer[i] << " ";
    }
    cout << "]" << endl;

    int* solved = solve(shifted, n);

    cout << "solved : [ ";
    for (int i = 0; i < n; i++) {
      cout << solved[i] << " ";
    }
    cout << "]" << endl;

    delete[] shifted;
    delete[] answer;
    delete[] solved;

    test_cases--;
  }

  return 0;
}