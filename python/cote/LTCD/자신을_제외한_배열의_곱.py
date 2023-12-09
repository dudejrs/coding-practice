
from typing import *
import random 

TEST_CASES = 10
N = 100

def solve(nums : List[int]) -> List[int] :
	ret  = []

	product = 1 
	for i in range(len(nums)) :
		ret.append(product)
		product = product * nums[i]

	product = 1
	for i in range(len(nums)-1, -1, -1) :
		ret[i] = ret[i] * product
		product = product * nums[i]

	return ret

if __name__ == "__main__" :
	
	random.seed(43)

	for _ in range(TEST_CASES) :

		n = random.randrange(2,N)
		nums = [random.randrange(2,N) for _ in range(n)]

		print(solve(nums))

