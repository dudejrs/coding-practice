from typing import List
import bisect
import random

TEST_CASES = 10
N = 10000
MAX_VALUE = N // 2


def solve1(nums1: List[int], nums2: List[int]) -> List[int]:
    result: Set = set()
    nums2.sort()

    for n1 in nums1:
        i2 = bisect.bisect_left(nums2, n1)
        if len(nums2) > 0 and len(nums2) > i2 and n1 == nums2[i2]:
            result.add(n1)

    return list(result)


def solve2(nums1: List[int], nums2: List[int]) -> List[int]:
    result: Set = set()

    nums1.sort()
    nums2.sort()

    i, j = 0, 0
    while i < len(nums1) and j < len(nums2):
        if nums1[i] > nums2[j]:
            j += 1
        elif nums1[i] < nums2[j]:
            i += 1
        else:
            result.add(nums1[i])
            i += 1
            j += 1

    return list(result)


if __name__ == "__main__":
    random.seed(43)

    for _ in range(TEST_CASES):
        n, m = random.randrange(1, N), random.randrange(1, N)
        nums1, nums2 = [random.randrange(1, MAX_VALUE) for _ in range(n)], [
            random.randrange(1, MAX_VALUE) for _ in range(m)
        ]
        print(nums1, nums2)
        print(solve1(nums1, nums2), solve2(nums1, nums2))
