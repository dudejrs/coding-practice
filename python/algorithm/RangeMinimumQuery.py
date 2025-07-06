from typing import List
import random
import sys

TEST_CASES = 10
N = 10000
MAX_VALUE = sys.maxsize % 100000


class RangeMinimumQuery:
    def __init__(self, data: List[int]):
        self.n = len(data)
        self._range_min = [MAX_VALUE for _ in range(4 * self.n)]
        self._init(data, 0, self.n - 1, 1)

    def _init(self, data, left, right, cur) -> int:
        if left == right:
            self._range_min[cur] = data[left]
        else:
            mid = (left + right) // 2
            left_min, right_min = self._init(data, left, mid, 2 * cur), self._init(
                data, mid + 1, right, 2 * cur + 1
            )
            self._range_min[cur] = min(left_min, right_min)

        return self._range_min[cur]

    def update(self, idx: int, value: int):

        def update(cur_left: int, cur_right: int, cur: int) -> int:
            if idx < cur_left or idx > cur_right:
                return self._range_min[cur]
            if cur_left == idx:
                self._range_min[cur] = value
            else:
                mid = (cur_left + cur_right) // 2
                left_min, right_min = update(cur_left, mid, 2 * cur), update(
                    mid + 1, cur_right, 2 * cur + 1
                )
                self._range_min[cur] = min(left_min, right_min)

            return self._range_min[cur]
            update(0, self.n - 1, 1)

    def query(self, left: int, right: int) -> int:

        def search(cur_left: int, cur_right: int, cur: int) -> int:
            if right < cur_left or cur_right < left:
                return MAX_VALUE
            if left <= cur_left and cur_right <= right:
                return self._range_min[cur]

            mid = (cur_left + cur_right) // 2
            left_min, right_min = search(cur_left, mid, 2 * cur), search(
                mid + 1, cur_right, 2 * cur + 1
            )
            return min(left_min, right_min)

        return search(0, self.n - 1, 1)


if __name__ == "__main__":
    random.seed(43)

    for _ in range(TEST_CASES):
        nums = [random.randrange(MAX_VALUE) for _ in range(N)]
        k = random.randrange(N - 1) + 1

        rmq = RangeMinimumQuery(nums[:k])

        for n in nums[k:]:
            rmq.update(random.randrange(k), n)
            print(rmq.query(0, k), end=" ")

        print()
