import random
from typing import List
from collections import defaultdict

TEST_CASES = 10
JEWALS = ord("z") - ord("a") + 1
STONES = 100


def solve(jewals: List[int], stones: List[int]) -> int:
    freq = defaultdict(int)

    for stone in stones:
        freq[stone] += 1

    ret = 0
    for jewal in jewals:
        ret += freq[jewal]

    return ret


if __name__ == "__main__":

    for _ in range(TEST_CASES):

        jewals = random.sample(
            [chr(ord("a") + i) for i in range(JEWALS)], random.randrange(1, JEWALS)
        )
        stones = [random.choice([chr(ord("a") + j) for j in range(JEWALS)]) for i in range(STONES)]
        print(solve(jewals, stones))
