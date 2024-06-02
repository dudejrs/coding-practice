#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#define N 20
#define PREFERENCE 20 
#define PRICE 20000
#define PRICE_UNIT 100 // 각 접시의 가격은 항상 100의 배수
#define BUDGETS pow(10, 9)

using namespace std;

// 각 초밥의 가격은 최대 2만원이기 떄문에 c[budget - 2만원] 전의 원소들은 필요가 없음. 슬라이딩 윈도우 이용
vector<int> cache(201);

pair<int, int> split(const string& s) {
	stringstream ss {s};
	istream_iterator<int> it{ss};

	return {*(it++), *(it++)};
}

int solve(int budget, vector<int>& prices, vector<int>& preferences) {
	int ret = 0;

	fill(begin(cache), end(cache), -1);

	cache[0] = 0;

	for (int cost = 0; cost <= budget / 100; cost++) {
		int cand = 0;
		for (int i = 0; i < prices.size(); i++) {
			if (prices[i] / 100 <= cost) {
				cand = max(cand, cache[(cost - prices[i] / 100) % 201] + preferences[i]);
			}
		}
		cache[cost % 201] = cand;
		ret = max(ret, cand);
	}

	return ret;
}

int main(void) {
	string buf;
	fstream f("./data/회전초밥.txt");

	getline(f, buf);
	int test_cases = stoi(buf);

	for (int it = 0; it < test_cases; it++) {
		getline(f, buf);
		auto [n, budget] = split(buf);

		vector<int> prices(n), preferences(n);

		for (int i = 0; i < n; i++) {
			getline(f, buf);
			auto [price, preference] = split(buf);
			prices[i] = price;
			preferences[i] = preference;
		}

		getline(f, buf);
		int answer = stoi(buf);

		cout << answer << " " << solve(budget, prices, preferences) << endl;
	}

	return 0;
}