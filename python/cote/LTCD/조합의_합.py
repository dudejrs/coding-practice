from typing import List
import random

TEST_CASES = 10
N = 15
MAX_VALUE = 100


def solve(candidates: List[int], target: int) -> List[List[int]]:
    ret = []

    def dfs(path: List[int], start: int, acc: int):

        if acc > target:
            return

        if acc == target:
            ret.append(path)
            return

        for i in range(start, len(candidates)):
            dfs([*path, candidates[i]], i + 1, acc + candidates[i])

    dfs([], 0, 0)

    return ret


if __name__ == "__main__":
    random.seed(43)

    for _ in range(TEST_CASES):
        candidates = [random.randrange(MAX_VALUE) for _ in range(N)]
        target = random.randrange(MAX_VALUE * 1.5)
        print(solve(candidates, target))
