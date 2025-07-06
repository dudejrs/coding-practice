import random
from collections import defaultdict


class IndexPicker:
    def __init__(self, items):
        self.nums = defaultdict(list)
        for i, elem in enumerate(items):
            self.nums[elem].append(i)

    def pick(self, k: int):
        return random.choice(self.nums[k])


def solve(items: list[int]) -> list[int]:
    return IndexPicker(items)
