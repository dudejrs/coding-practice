import sys
from typing import *
import random


TEST_CASES = 10
N = 100000
MAX_PRICE = 10000000000


def solve(prices: List[int]) -> int:

    min_price = sys.maxsize
    max_profit = 0

    for price in prices:
        min_price = min(min_price, price)
        max_profit = max(max_profit, price - min_price)

    return max_profit


if __name__ == "__main__":
    random.seed(43)

    for _ in range(TEST_CASES):
        n = random.randrange(1, N)
        prices = [random.randrange(1, MAX_PRICE) for _ in range(n)]

        print(solve(prices))
