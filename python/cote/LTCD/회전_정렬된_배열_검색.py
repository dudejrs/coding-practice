from typing import List
import random

TEST_CASE = 10
N = 10000

def solve(target: int, nums: List[int])-> int :

	if not nums :
		return -1

	left, right = 0, len(nums) - 1
	while left + 1 < right :
		mid = left + (right - left) // 2

		# (mid, right]에  최솟값이 존재 
		if nums[mid] > nums[right] :
			left = mid
		else :
			right = mid -1 

	pivot = right

	left, right = 0, len(nums) - 1

	while left <= right :
		mid = left + (right - left) // 2
		mid_pivot = (mid + pivot) % len(nums)

		if nums[mid_pivot] < target :
			left = mid + 1
		elif nums[mid_pivot] > target: 
			right = mid -1
		else :
			return mid_pivot

	return -1 

if __name__ == "__main__" :
	random.seed(43)

	for _ in range(TEST_CASE) :
		k = random.randrange(N)
		nums = sorted(random.sample(range(k,N), random.randrange(0, N-k))) + sorted(random.sample(range(k), random.randrange(k)))
		target = nums[random.randrange(len(nums))]
		k = solve(target, nums)
		print(target, nums[k])