#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#define MAX_N 100000
#define MAX_QUERiES_LENGTH 10000

using namespace std;

struct RMQ {

	RMQ (vector<int>& array) : n(array.size()) {
		range_min.resize(4 * n);
		init(0, n - 1, 1, array);
	}

	int query(int left, int right) {
		return query(left, right, 0, n - 1, 1);
	}

	private : 

		int n;
		vector<int> range_min;

		int init(int left, int right, int cur, vector<int>& array) {
			if (left == right) {
				return range_min[cur] = array[left];
			}

			int mid = (left + right) / 2;
			int left_min = init(left, mid, 2 * cur, array);
			int right_min = init(mid + 1, right, 2 * cur + 1, array);

			return range_min[cur] = min(left_min, right_min);
		}

		int query(int left, int right, int cur_left, int cur_right, int cur) {

			if (right < cur_left || cur_right < left) {
				return numeric_limits<int>::max();
			}

			if (left <= cur_left && cur_right <= right) {
				return range_min[cur];
			}

			int mid = (cur_left + cur_right) / 2;

			int left_min = query(left, right, cur_left, mid, 2 * cur);
			int right_min = query(left, right, mid + 1, cur_right, 2 * cur + 1);

			return min(left_min, right_min);
		}
};

int next_serial = 0;
int node_to_serial[MAX_N];
int serial_to_node[MAX_N];
int first_appearance[MAX_N];
int depth[MAX_N];
vector<int> children[MAX_N];

int* split(const string& s, int n) {
	int* ret = new int[n];
	
	stringstream ss(s);
	string buf;

	for (int i =0; i < n; i++) {
		getline(ss, buf, ' ');
		ret[i] = stoi(buf);
	}

	return ret;
}

void clear() {
	next_serial = 0;
	memset(node_to_serial, -1, sizeof(node_to_serial));
	memset(serial_to_node, -1, sizeof(serial_to_node));
	memset(first_appearance, -1, sizeof(first_appearance));
	memset(depth, -1, sizeof(depth));

	for (int i =0; i < MAX_N; i++){
		children[i].clear();
	}

	return;
}

// 깊이가 d인 노드(cur)를 전위탐색하면서 
// 	1. 부모 노드일 수록 작은 번호를 갖도록 노드들의 번호를 다시 매김
//  2. 트리를 일렬로 핀 결과를 trip으로 표현 (여러번 방문하여도 방문할때마다 표시)
void traverse(int cur, int d, vector<int>& trip) {
	node_to_serial[cur] = next_serial;
	serial_to_node[next_serial] = cur;
	++next_serial;

	depth[cur] = d;

	first_appearance[cur] = trip.size();
	trip.push_back(node_to_serial[cur]);

	for (int i = 0; i < children[cur].size(); ++i) {
		traverse(children[cur][i], d + 1, trip);
		trip.push_back(node_to_serial[cur]);
	}
}

// 트리를 일렬로 피고, 가장 작은 번호(최소 공통 조상노드)를 가지고 있는 RMQ를 반환
RMQ* prepareRMQ() {

	vector<int> trip;
	traverse(0, 0, trip);

	return new RMQ(trip);
}

int distance(RMQ* rmq, int u, int v) {

	int location_u = first_appearance[u];
	int location_v = first_appearance[v];

	if (location_u > location_v) {
		swap(location_u, location_v);
	}

	int lca = serial_to_node[rmq->query(location_u, location_v)];

	return depth[u] + depth[v] - 2 * depth[lca];
}

// 두 노드간의 촌수를 계산하여 반환
int* solve(int* father, int** queries, int n, int q) {
	clear();
	
	// children 초기화
	for (int i = 0; i < n - 1; i++) {
		children[father[i]].push_back(i + 1);
	}	

	// rmq 생성
	RMQ* rmq = prepareRMQ();


	int* ret = new int[q];

	// query 처리
	for (int i = 0; i < q; i++) {
		ret[i] = distance(rmq, queries[i][0], queries[i][1]);
	}

	delete rmq;

	return ret;
}

int main(void) {
	string buf;
	fstream fd("data/족보_탐험.txt");

	getline(fd, buf);
	int test_cases = stoi(buf);

	while(test_cases > 0) {

		getline(fd, buf);
		int* nums = split(buf, 2);

		getline(fd, buf);
		int* father = split(buf, nums[0] - 1);

		int** queries = new int*[nums[1]];
		for (int i = 0; i < nums[1]; i++) {
			getline(fd, buf);
			queries[i] = split(buf, 2);
		}

		int* ret = solve(father, queries, nums[0], nums[1]);

		getline(fd, buf);
		int* answer = split(buf, nums[1]);

		cout << "answer : ";
		for (int i =0; i <nums[1]; i++) {
			cout << answer[i] << " ";
		}
		cout << endl;

		cout << "solved : ";
		for (int i =0; i <nums[1]; i++) {
			cout << ret[i] << " ";
		}
		cout << endl;

		delete[] ret;
		delete[] answer;

		for (int i =0; i< nums[1]; i++) {
			delete[] queries[i];
		}
		delete[] queries;

		delete[] father;
		delete[] nums;

		test_cases--;
	}

	return 0;
}