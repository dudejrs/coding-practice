#include <iostream>
#include <random>
#include <set>

#define N 100

using namespace std;

int* initialize(default_random_engine& gen) {
  int* ret = new int[N];

  normal_distribution<float> dis(1500, 1000);

  for (int i = 0; i < N; i++) {
    ret[i] = abs(floor(dis(gen)));
  }

  return ret;
}

int solve2(int* russians, int* koreans) {
  int wins = 0;

  multiset<int> ratings(koreans, koreans + N);
  for (int i = 0; i < N; i++) {
    if (*ratings.rbegin() < russians[i]) {
      ratings.erase(ratings.begin());
    } else {
      ratings.erase(ratings.lower_bound(russians[i]));
      wins++;
    }
  }
  return wins;
}

int solve(int* russians, int* koreans) {
  sort(russians, russians + N);
  sort(koreans, koreans + N);

  int j = 0;
  for (int i = 0; i < N; i++) {
    if (russians[j] < koreans[i]) {
      j++;
    }
  }

  return j;
}

int main(void) {
  default_random_engine gen(43);

  int* russians = initialize(gen);
  int* koreans = initialize(gen);

  for (int i = 0; i < N; i++) {
    cout << russians[i] << " ";
  }
  cout << endl;
  for (int i = 0; i < N; i++) {
    cout << koreans[i] << " ";
  }
  cout << endl;

  cout << solve(russians, koreans) << endl;
  cout << solve2(russians, koreans) << endl;

  return 0;
}