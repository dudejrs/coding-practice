from typing import List
import random

TEST_CASES = 10
N = 10000
MAX_NUMBER = 10000
MAX_INTERVAL = 100

def initialize() -> List[List[int]] :
	ret = []
	n = random.randrange(2, N)

	for _ in range(n) :
		hi = random.randrange(MAX_INTERVAL, MAX_NUMBER)
		lo = hi - random.randrange(1, MAX_INTERVAL)
		ret.append([lo, hi])

	ret.sort()
	return ret

def solve(intervals: List[List[int]]) -> List[List[int]] :
	merged = []

	for cur in sorted(intervals, key = lambda x : x[0]) :
		if merged and cur[0] <= merged[-1][1] :
			merged[-1][1] = max(merged[-1][1], cur[1])
		else :
			merged.append(cur)

	return merged

if __name__ == "__main__" :
	random.seed(43)

	for _ in range(TEST_CASES) :
		intervals = initialize()
		print(solve(intervals))