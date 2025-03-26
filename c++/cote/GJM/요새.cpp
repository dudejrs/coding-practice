#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Node {
  vector<Node*> children;
  int i;

  Node(int i) : i(i) {}

  ~Node() {
    for (Node* child : children) {
      delete child;
    }
  }
};

int longest = 0;

int* x;
int* y;
int* radius;

int* getFort(string& s) {
  int* ret = new int[3];
  stringstream ss(s);
  string buf;

  for (int i = 0; i < 3; i++) {
    getline(ss, buf, ' ');
    ret[i] = stoi(buf);
  }

  return ret;
}

int square_distance(int parent, int child) {
  return pow(x[parent] - x[child], 2) + pow(y[parent] - y[child], 2);
}

bool encolses(int parent, int child) {
  return radius[parent] > radius[child] &&
         square_distance(parent, child) <
             pow(radius[parent] - radius[child], 2);
}

bool isChild(int parent, int child, int n) {
  if (!encolses(parent, child)) return false;
  for (int i = 0; i < n; i++) {
    if (i == parent || i == child) continue;
    if (encolses(parent, i) && encolses(i, child)) return false;
  }

  return true;
}

Node* getTree(int i, int n) {
  Node* ret = new Node(i);

  for (int j = 0; j < n; j++) {
    if (isChild(i, j, n)) {
      ret->children.push_back(getTree(j, n));
    }
  }

  return ret;
}

int height(Node* root) {
  vector<int> heights;

  for (int i = 0; i < root->children.size(); i++) {
    heights.push_back(height(root->children[i]));
  }

  if (heights.empty()) return 0;

  sort(begin(heights), end(heights));

  int l = heights.size();
  if (l >= 2) longest = max(longest, 2 + heights[l - 2] + heights[l - 1]);

  return heights.back() + 1;
}

int solve(int n) {
  longest = 0;
  Node* root = getTree(0, n);
  int h = height(root);

  delete root;
  return max(h, longest);
}

int main(void) {
  fstream fd("data/요새.txt");

  string buf;

  getline(fd, buf);
  int test_cases = stoi(buf);

  while (test_cases > 0) {
    getline(fd, buf);
    int n = stoi(buf);

    x = new int[n];
    y = new int[n];
    radius = new int[n];

    for (int i = 0; i < n; i++) {
      getline(fd, buf);
      int* fort = getFort(buf);
      x[i] = fort[0];
      y[i] = fort[1];
      radius[i] = fort[2];
      delete[] fort;
    }

    cout << solve(n) << endl;

    delete[] x;
    delete[] y;
    delete[] radius;

    test_cases--;
  }

  return 0;
}