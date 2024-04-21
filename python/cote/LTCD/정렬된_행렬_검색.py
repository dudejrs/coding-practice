from typing import List
import random

TEST_CASES = 10
MAX_VALUE = 100
N = 10
M = 10

def solve1(matrix: List[List[int]], k: int)-> bool :
	row, col = 0, len(matrix[0]) -1

	while row <= len(matrix) -1 and col >= 0 :
		if k == matrix[row][col] :
			return True
		elif k < matrix[row][col] :
			col -=1
		elif k > matrix[row][col] :
			row+=1

	return False

def solve2(matrix: List[List[int]], k: int)-> bool :
	return any(k in row for row in matrix)

if __name__ == "__main__" :
	random.seed(43)
	for _ in range(TEST_CASES) :
		n, m = random.randrange(2, N), random.randrange(2, M)
		nums = sorted(random.sample(range(MAX_VALUE), n * m))
		matrix = [nums[m*i : m*(i+1)] for i in range(n)]
		k = random.randrange(MAX_VALUE)
		print(k in nums,solve1(matrix, k), solve2(matrix, k))
