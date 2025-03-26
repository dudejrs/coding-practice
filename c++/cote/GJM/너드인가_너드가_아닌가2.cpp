#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

#define MAX_N 50000
#define MAX_VALUE 100000

using namespace std;

int** persons;
map<int, int> coords;

int* get_score(string s) {
  int* ret = new int[2];

  stringstream ss(s);
  string buf;

  for (int i = 0; i < 2; i++) {
    getline(ss, buf, ' ');
    ret[i] = stoi(buf);
  }

  return ret;
}

bool isDominated(int x, int y) {
  map<int, int>::iterator it = coords.lower_bound(x);

  if (it == end(coords)) return false;

  return y < it->second;
}

void removeDominated(int x, int y) {
  map<int, int>::iterator it = coords.lower_bound(x);

  if (it == begin(coords)) return;
  it--;

  while (true) {
    if (it->second > y) break;

    if (it == begin(coords)) {
      coords.erase(it);
      break;
    }

    map<int, int>::iterator tmp = it;
    --it;
    coords.erase(tmp);
  }
}

void registerCoord(int x, int y) {
  if (isDominated(x, y)) return;

  removeDominated(x, y);
  coords[x] = y;
}

int solve(int n) {
  int count = 0;

  for (int i = 0; i < n; i++) {
    int* score = persons[i];
    registerCoord(score[0], score[1]);

    count += coords.size();
  }
  return count;
}

int main(void) {
  fstream fd("data/너드인가_너드가_아닌가2.txt");
  string buf;

  getline(fd, buf);
  int test_cases = stoi(buf);

  while (test_cases > 0) {
    getline(fd, buf);
    int n = stoi(buf);

    persons = new int*[n];

    for (int i = 0; i < n; i++) {
      getline(fd, buf);
      persons[i] = get_score(buf);
    }

    cout << solve(n) << endl;

    for (int i = 0; i < n; i++) {
      delete[] persons[i];
    }

    coords.clear();

    test_cases--;
  }

  return 0;
}