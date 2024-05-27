#include <iostream>
#include <random>
#include <vector>
#define TEST_CASES 10

using namespace std;

vector<int> cache(pow(3,9), -2);

pair<vector<string>, char> initialize(default_random_engine& gen) {
	vector<string> ret(3, string(3,'.'));

	char turn = gen() % 2 == 0 ? 'o' : 'x';

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (gen () % 2 == 0) {
				ret[i][j] = turn;
				turn = 'o' + 'x' - turn;
			}
		}
	}
 
	return {ret, turn} ;
}

bool is_finished(vector<string>& board, char turn) {
	for (int i = 0; i < 3; i++) {
		int j = 0;
		while (j < 3 && board[i][j] == turn) {
			j++;
		}

		if (j == 3) {
			return true;
		}
	}

	for (int j = 0; j < 3; j++) {
		int i = 0;
		while ( i < 3 && board[i][j] == turn) {
			i++;
		}
		if (i == 3) {
			return true;
		}
	}

	return false;
}

int bijection(vector<string>& board) {
	int ret = 0;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ret = ret * 3;
			if (board[i][j] == 'o' ) {
				ret += 1;
			} else if (board[i][j] == 'x') {
				ret += 2;
			}
		}
	}

	return ret;
}

int solve(vector<string>& board, char turn) {

	if (is_finished(board, turn)) {
		return -1;
	}

	int& ret = cache[bijection(board)];
	if (ret != -2) {
		return ret;
	}

	int other = 2;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == '.') {
				board[i][j] = turn;
				other = min(other, solve(board, 'o' +' x' - turn));
				board[i][j] = '.';
			}
		}
	}

	// 플레이 할 수 없거나, 어떻게 해도 비기는 것이 최선인 경우 비김
	if (other == 2 || other == 0) {
		return ret = 0;
	}

	// 최선이 상대가 이기는 거라면 난 지고, 내가 이기는 거라면 상대는 짐
	return ret = - other;
}

int main(void) {
	default_random_engine gen{21};

	for (int i = 0; i < TEST_CASES; i++) {
		auto [board, turn] = initialize(gen);
		cout << solve(board, turn)  << endl;
	}
	return 0;
}