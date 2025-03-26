#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <random>
#include <vector>
#define N 10
#define MAX 987654321

using namespace std;

double cache[N][1 << N];

double** initialize() {
  default_random_engine gen(43);
  normal_distribution<double> dis(N, 3 * N);

  double** w = new double*[N];
  for (int i = 0; i < N; i++) {
    w[i] = new double[N];
  }

  for (int i = 0; i < N; i++) {
    w[i][i] = MAX;
    for (int j = 0; j < i; j++) {
      double tmp = abs(dis(gen));
      if ((int)floor(tmp) % 37 < 1) tmp = MAX;

      w[i][j] = tmp;
      w[j][i] = tmp;
    }
  }

  memset(cache, -1, sizeof(cache));

  return w;
}

double shortest_path(int here, int visited, double** w) {
  if (visited == (1 << N) - 1) return w[here][0];

  double& ret = cache[here][visited];

  if (ret >= 0) return ret;

  ret = MAX;

  for (int i = 0; i < N; i++) {
    if (visited & (1 << i)) continue;
    ret = min(ret, shortest_path(i, visited + (1 << i), w) + w[here][i]);
  }

  return ret;
}

void print_result(double** w, double ret) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (w[i][j] == MAX) {
        cout << setw(5) << "-";
        cout << " ";
        continue;
      }
      cout << fixed << setw(5) << setprecision(2) << w[i][j];
      cout << " ";
    }
    cout << endl;
  }

  cout << "result :  " << fixed << setprecision(2) << ret << endl;
}

int main(void) {
  vector<int> path;
  double** w = initialize();
  int visited = 1;
  path.push_back(0);

  double ret = shortest_path(0, visited, w);

  print_result(w, ret);

  return 0;
}