from typing import List
import random

TEST_CASES = 10
N = 10000
MAX_PRICES = 100


def solve(prices: List[int]) -> int:
    return sum(max(prices[i + 1] - prices[i], 0) for i in range(len(prices) - 1))


if __name__ == "__main__":
    random.seed(43)

    for _ in range(TEST_CASES):
        n = random.randrange(1, N)
        prices = [random.randrange(1, MAX_PRICES) for _ in range(n)]
        print(solve(prices))
