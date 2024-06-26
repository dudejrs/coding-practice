import random

TEST = 10
N = 1000

def initialize(n) :
	ret = []
	k = random.randrange(3, n)
	ret.extend([k for _ in range(n + 1)])
	ret.extend([random.randrange(1, k) for _ in range(n)])
	random.shuffle(ret)

	return k, ret

def solve(nums) :
	if not nums :
		return None

	if len(nums) == 1 :
		return nums[0]

	half = len(nums) // 2
	a = solve(nums[:half])
	b = solve(nums[half:])

	return [b, a][nums.count(a) > half]

if __name__ == "__main__" :
	random.seed(43)

	for _ in range(TEST) :
		n = random.randrange(4, N // 2) 
		k, nums =initialize(n)
		print(k, solve(nums))