index = int


def find_pivot(nums: list[int]) -> index:
    n = len(nums)

    for i in range(n - 2, -1, -1):
        if nums[i] < nums[i + 1]:
            return i

    return -1


def find_successor(nums: list[int], pivot: int) -> index:
    n = len(nums)

    for i in range(n - 1, pivot, -1):
        if nums[i] > nums[pivot]:
            return i

    return pivot


def solve(nums: list[int]) -> list[int]:
    i = find_pivot(nums)

    if i < 0:
        return sorted(nums)

    j = find_successor(nums, i)
    print(nums, i, j)
    nums = nums[:]
    nums[i], nums[j] = nums[j], nums[i]

    return nums[: i + 1] + sorted(nums[i + 1 :])
