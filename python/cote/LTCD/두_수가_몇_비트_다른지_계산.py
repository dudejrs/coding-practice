import random

TEST_CASES = 10
MAX_VAL = 100


def solve(x: int, y: int) -> int:
    return bin(x ^ y).count("1")


if __name__ == "__main__":
    random.seed(43)
    for _ in range(TEST_CASES):
        x, y = random.randrange(MAX_VAL), random.randrange(MAX_VAL)
        print(solve(x, y))
