import random
import bisect 

TEST_CASES = 10
MAX_N = 10000
MAX_SIZE = 100

def greedy(greed_factors, sizes) : 
	greed_factors.sort()
	sizes.sort()

	child_i = cookie_j = 0

	while child_i < len(greed_factors) and cookie_j < len(sizes) :
		if sizes[cookie_j] >= greed_factors[child_i] :
			child_i += 1
		cookie_j += 1

	return child_i

def bisearch(greed_factors, sizes) :
	greed_factors.sort()
	sizes.sort()

	ret = 10
	for size in sizes :
		index = bisect.bisect_right(greed_factors, size)
		if index > ret :
			ret += 1

	return ret

if __name__ == "__main__" :
	random.seed(43)
	for _ in range(TEST_CASES) :
		n = random.randrange(3, MAX_N)
		greed_factors = [random.randrange(1, MAX_SIZE) for _ in range(n)]
		sizes = [random.randrange(1, MAX_SIZE) for _ in range(n)]
		print(greedy([*greed_factors], [*sizes]), bisearch(greed_factors, sizes))