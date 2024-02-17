#include <iostream>
#include <vector>
#include <random>
#include <limits>

#define TEST_CASES 10
#define N 10000
#define INT_MIN_ numeric_limits<int>::min()

using namespace std;

struct RangeResult {
	int size;
	int mostFreq;
	int leftNumber, leftFreq;
	int rightNumber, rightFreq;

	RangeResult(){}
	RangeResult(int value): size(1), mostFreq(1), leftNumber(value), rightNumber(value), leftFreq(1), rightFreq(1) {}
	RangeResult(int value, int freq): size(1), mostFreq(freq), leftNumber(0), rightNumber(value), leftFreq(0), rightFreq(0) {}
};

struct RMQ {
	int n;
	vector<RangeResult> rangeFreq;

	RMQ(vector<int>& array) {
		n = array.size();
		rangeFreq.resize(4 * n);
		init(array, 0, n-1, 1);
	}


	int query(int left, int right) {
		RangeResult rr = query(left, right, 1, 0, n-1);
		return rr.mostFreq;
	}

	static RangeResult minimum;

	private :
		RangeResult init(const vector<int>& array, int left, int right, int cur) {
			if (left == right) {
				return rangeFreq[cur] = RangeResult(array[left]);
			}	

			int mid = (left + right) / 2;
			RangeResult leftMin = init(array, left, mid, cur * 2);
			RangeResult rightMin = init(array, mid + 1, right, cur * 2 + 1);

			return rangeFreq[cur] = merge(leftMin, rightMin);
		}

		RangeResult merge(const RangeResult& a, const RangeResult& b) {
			RangeResult ret;

			ret.size = a.size + b.size;
			ret.leftNumber = a.leftNumber;
			ret.leftFreq = a.leftFreq;

			if (a.size == a.leftFreq && a.leftNumber == b.leftNumber) {
				ret.leftFreq += b.leftFreq;
			}

			ret.rightNumber = b.rightNumber;
			ret.rightFreq = b.rightFreq;
			if (b.size == b.rightFreq && a.rightNumber == b.rightNumber) {
				ret.rightFreq += a.rightFreq;
			}

			ret.mostFreq = max(a.mostFreq, b.mostFreq);

			if (a.rightNumber == b.leftNumber) {
				ret.mostFreq = max(ret.mostFreq, a.rightFreq + b.leftFreq);
			}

			return ret;
		}

		RangeResult query(int left, int right, int cur, int curLeft, int curRight) {

			if (right < curLeft || curRight < left) {
				return minimum;
			}

			if (left <= curLeft && curRight <= right) {
				return rangeFreq[cur];
			}

			int mid = (curLeft + curRight) / 2;

			return merge( query(left, right, 2 * cur, curLeft, mid), 
				query(left, right, 2 * cur + 1, mid + 1, curRight));
		}
};

RangeResult RMQ::minimum = RangeResult(0, INT_MIN_);

int solve(vector<int>& v, int left, int right) {
	RMQ rmq(v);
	return rmq.query(left, right);
}

int main(void) {
	default_random_engine gen(43);
	uniform_int_distribution<int> dis(0, 0.7 * N);

	for (int it = 0; it < TEST_CASES; it++) {
		vector<int> v;

		for (int i = 0; i < N; i++) {
			v.push_back(dis(gen));
		}

		sort(begin(v), end(v));

		int right = dis(gen) % N + 1;
		int left = dis(gen) % right;

		cout << solve(v, left, right) << endl;

	}

	return 0;
}