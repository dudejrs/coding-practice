#include <iostream>
#include <vector>
#include <random>
#include <limits>
#define TEST_CASES 10
#define N 10000
#define INT_MAX_ numeric_limits<int>::max()

using namespace std; 

struct RMQ {
	int n;
	vector<int*> rangeMin;
	RMQ(const vector<int>& array) {
		n = array.size();
		rangeMin.resize(4 * n);
		init(array, 0, n-1, 1);
	};

	int* query(int left, int right){
		return query(left, right, 1, 0, n-1);
	}

	private : 
		int* init(const vector<int>& array, int left, int right, int node) {
			if (left == right){
				return rangeMin[node] = new int[2] {array[left], INT_MAX_};
			}

			int mid = (left + right) / 2;
			int* leftMin = init(array, left, mid, node * 2);
			int* rightMin = init(array, mid + 1, right, node * 2 + 1);

			vector<int> cand (4);
			copy(leftMin, leftMin+2, begin(cand));
			copy(rightMin, rightMin+2, begin(cand)+2);

			sort(begin(cand), end(cand));

			return rangeMin[node] = new int[]{cand[0], cand[1]};
		}

		int* query(int left, int right, int node, int nodeLeft, int nodeRight) {
			if (right < nodeLeft || nodeRight < left) {
				return new int[2] {INT_MAX_, INT_MAX_};
			}
			if (left <= nodeLeft && nodeRight <= right) {
				return new int[2] {rangeMin[node][0], rangeMin[node][1]};
			}


			int mid = (nodeLeft + nodeRight) / 2;

			int* leftHand = query(left, right, node * 2, nodeLeft, mid);
			int* rightHand = query(left, right, node * 2 + 1, mid + 1, nodeRight);

			vector<int> cand(4);
			copy(leftHand, leftHand+2, begin(cand));
			copy(rightHand, rightHand+2, begin(cand) + 2);

			sort(begin(cand), end(cand));

			delete[] leftHand;
			delete[] rightHand;

			return new int[2]{cand[0], cand[1]};
		}

};


int* solve(int start, int end, vector<int>& v) {
	RMQ rmq(v);
	return rmq.query(start, end);
}

int main(void) {
	default_random_engine gen(43);
	uniform_int_distribution<int> dis(0, N * 5);

	for (int it = 0; it < TEST_CASES; it++) {
		vector<int> v;

		for (int i = 0; i < N; i++){
			v.push_back(dis(gen));
		}

		int end_ = dis(gen) % N + 1;
		int start = dis(gen) % end_;

		sort(begin(v), end(v));
		int* answer = solve(start, end_, v);

		sort(begin(v), end(v));
		cout <<"(" <<answer[0] << ", " << answer[1] << ")" << endl;
		delete[] answer;
	}

	return 0;
}