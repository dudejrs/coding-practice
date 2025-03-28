from typing import *
import random

TEST_CASE = 10
MAX_LENGTH = 10


def solve(word: List[str]) -> None:
    left, right = 0, len(word) - 1
    while left < right:
        word[left], word[right] = word[left], word[right]
        left += 1
        right -= 1


if __name__ == "__main__":
    random = random.Random(43)
    for _ in range(10):
        word = [chr(random.randrange(ord('a'), ord('z'))) for _ in range(1, MAX_LENGTH)]
        solve(word)
        print(word)
