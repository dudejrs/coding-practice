#include <initializer_list>
#include <iostream>
#include <string>

using namespace std;

namespace TreeIterator {
template <typename T>
struct BinaryTree;
template <typename T>
struct Iterator;
template <typename T>
struct PreorderIterator;

template <typename T>
struct Node {
  T value;
  Node<T>* parent = nullptr;
  Node<T>* left = nullptr;
  Node<T>* right = nullptr;

  explicit Node(const T& value) : value(value) {}
  Node(const T&& value) : value(value) {}

  Node(const T& value, Node<T>* left, Node<T>* const right)
      : value(value), left(left), right(right) {
    this->left->parent = this->right->parent = this;
  }
  Node(const T& value, const Node<T>&& left, const Node<T>&& right)
      : value(value), left(new Node<T>(left)), right(new Node<T>(right)) {
    this->left->parent = this->right->parent = this;
  }
};

template <typename T>
struct BinaryTree {
  typedef PreorderIterator<T> iterator;

  enum class IteratorType { PRE_ORDER };

  Node<T>* root = nullptr;
  IteratorType iterator_type = IteratorType::PRE_ORDER;

  explicit BinaryTree(Node<T>* root) : root(root) {}
  BinaryTree(const Node<T>& root) : BinaryTree(root) {}
  BinaryTree(const Node<T>&& root) : BinaryTree(new Node<T>(root)) {}

  iterator begin() {
    Node<T>* n = root;
    while (n->left) {
      n = n->left;
    }

    return PreorderIterator<T>(n);
  }

  iterator end() { return PreorderIterator<T>(); }
};

template <typename T>
struct Iterator {
  Node<T>* current = nullptr;

  explicit Iterator() {}
  explicit Iterator(Node<T>* current) : current(current) {}

  virtual bool operator!=(const Iterator<T>& other);

  virtual Node<T>& operator*();

  virtual Iterator<T>& operator++();
};

template <typename T>
struct PreorderIterator : public Iterator<T> {
  explicit PreorderIterator(Node<T>* current) : Iterator<T>(current) {}
  PreorderIterator() : Iterator<T>() {}

  bool operator!=(const Iterator<T>& other) override {
    return Iterator<T>::current != other.current;
  }
  Node<T>& operator*() override { return *(Iterator<T>::current); }
  Iterator<T>& operator++() override {
    Node<T>* current = Iterator<T>::current;

    if (current->right) {
      current = current->right;
      while (current->left) current = current->left;
    } else {
      Node<T>* p = current->parent;
      while (p && current == p->right) {
        current = p;
        p = p->parent;
      }
      current = p;
    }

    Iterator<T>::current = current;

    return *this;
  }
};

template <typename T>
bool Iterator<T>::operator!=(const Iterator<T>& other) {
  if (auto child = dynamic_cast<PreorderIterator<T>*>(this)) {
    return current != other.current;
  }

  return current != other.current;
}

template <typename T>
Node<T>& Iterator<T>::operator*() {
  if (auto child = dynamic_cast<PreorderIterator<T>*>(this)) {
    return *(child->current);
  }
  return *current;
}

template <typename T>
Iterator<T>& Iterator<T>::operator++() {
  if (auto child = dynamic_cast<PreorderIterator<T>*>(this)) {
    child++;
    return *this;
  }
  return *this;
}

void main() {
  BinaryTree<string> family{
      {"me", {"father"}, {"mother", {"grandmother"}, {"grandfather"}}}};

  for (auto it = family.begin(); it != family.end(); ++it) {
    cout << (*it).value << " ";
  }
  cout << endl << "--------------------------" << endl;

  for (auto it : family) {
    cout << it.value << " ";
  }
  cout << endl;
}
}  // namespace TreeIterator

int main(void) {
  TreeIterator::main();
  return 0;
}
