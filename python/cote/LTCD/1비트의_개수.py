import random

TEST_CASES = 10
MAX_VAL = 1000


def solve(n: int) -> int:

    count = 0

    while n:
        n &= n - 1
        count += 1

    return count


if __name__ == "__main__":
    random.seed(43)
    for _ in range(TEST_CASES):
        n = random.randrange(MAX_VAL)
        print(solve(n))
