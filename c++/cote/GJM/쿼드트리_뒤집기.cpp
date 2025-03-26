#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string reverse(string::iterator& cur) {
  ostringstream oss;
  char head = *cur;
  cur++;
  if (head != 'x') {
    oss << head;
    return oss.str();
  }

  string upperLeft = reverse(cur);
  string upperRight = reverse(cur);
  string lowerLeft = reverse(cur);
  string lowerRight = reverse(cur);

  oss << string("x") << lowerLeft << lowerRight << upperLeft << upperRight;

  return oss.str();
}

string solve(string& s) {
  auto a = s.begin();
  return reverse(a);
}

int main(void) {
  fstream fd("data/쿼드트리_뒤집기.txt");
  string buf;

  getline(fd, buf);

  int test_cases = stoi(buf);

  while (test_cases > 0) {
    getline(fd, buf);

    cout << solve(buf) << endl;

    test_cases--;
  }

  return 0;
}