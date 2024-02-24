#include <iostream>
#include <vector>
#include <random>
#include <limits>

#define TEST_CASES 1
#define N 100000
#define Q 10000
#define H 20000


using namespace std;

struct RMQ {
	RMQ(int array[], int length) :  n(length){
		range_min.resize(4 * n);
		init(array, 0, n-1, 1);
	}

	int query(int left, int right) {
		return query(left, right, 1, 0, n-1);
	}

	private : 
		int n;
		vector<int> range_min;

		int init(int array[], int left, int right, int cur) {
			if (left == right) {
				return range_min[cur] = array[left];
			}

			int mid = (left + right) / 2;

			int left_min = init(array, left, mid, 2 * cur);
			int right_min = init(array, mid + 1, right, 2 * cur + 1);

			return range_min[cur] = min(left_min, right_min);
		}

		int query(int left, int right, int cur, int cur_left, int cur_right) {
			
			if (right < cur_left || cur_right < left) {
				return numeric_limits<int>::max();
			}

			if (left <= cur_left && cur_right <= right) {
				return range_min[cur];
			}
			int mid = (cur_left + cur_right) / 2;
			int left_min = query(left, right, 2 * cur, cur_left, mid);
			int right_min = query(left, right, 2 * cur + 1, mid + 1, cur_right);

			return min(left_min, right_min);
		}
};

int* solve(int* sign_boards, int** querys, int n, int q) {
	int* ret = new int[q];
	int* reversed = new int[n];
	
	transform(sign_boards, sign_boards+n, reversed,[](int a){
		return -a;
	});

	RMQ min_rmq(sign_boards, n);
	RMQ max_rmq (reversed, n);

	for (int i = 0; i < q; i++) {

		int min = min_rmq.query(querys[i][0], querys[i][1]);
		int max = max_rmq.query(querys[i][0], querys[i][1]);

		ret[i] = -max - min; 
	}

	delete[] reversed;

	return ret;
}

int main(void) {
	default_random_engine gen(43);
	uniform_int_distribution<int> n_dist(2, N);


	for (int it = 0; it < TEST_CASES; it++) {

		int n = n_dist(gen);
		int max_height = gen() % (H - 1) + 1;
		int q = gen() % (Q - 1) + 1;
		
		normal_distribution<float> h_dist( max_height / 2, max_height / 4);
		int* sign_boards = new int[n];

		for (int i = 0; i < n; i++) {
			sign_boards[i] = floor(h_dist(gen));
		}

		int** querys = new int*[q];
		for (int i = 0; i < q; i++) {
			int a = gen() % (n - 1) + 1;
			int b = gen() % a;
			querys[i] = new int[2] {b, a};
		}

		int* ret = solve(sign_boards, querys, n, q);

		for (int i =0; i < q; i++) {
			cout << ret[i] << endl;
		}

		delete[] sign_boards;
		for (int i = 0; i < q; i++) {
			delete[] querys[i];
		}
		delete[] querys;
		delete[] ret;
	}

	return 0;
}