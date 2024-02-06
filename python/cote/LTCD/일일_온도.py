from typing import List
import random

TEST_CASES = 10
N = 10000


def solve(T: List[int]) -> List[int] : 
	ret = [0 for _ in range(len(T))]
	stack = []

	for i, cur in enumerate(T) :
		while stack and T[stack[-1]] < cur :
			j = stack.pop()
			ret[j] = i - j

		stack.append(i)

	return ret

if __name__ == "__main__" :
	random.seed(43)
	for _ in range(TEST_CASES) :
		T = [ random.randrange(-10,40) for _ in range(random.randrange(1, N)) ]
		print(solve(T))
