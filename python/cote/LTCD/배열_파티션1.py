from typing import *
import random

TEST_CASES = 10
N = 100000

def solve(nums : List[int]) -> int :
	return sum(sorted(nums)[::2])


if __name__ == "__main__" :	

	for _ in range(10) :
		n = 2*random.randrange(1,N);
		nums= random.sample(range(0,n), 2*random.randrange(2,n//2))
		print(solve(nums))
