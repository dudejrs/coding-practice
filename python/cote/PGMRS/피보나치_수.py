import random
from functools import lru_cache


TEST_CASES = 10
MAX_N = 100000
M = 1234567


@lru_cache(100000)
def fibonacci(n):
    if n == 0 or n == 1:
        return n
    return (fibonacci(n - 1) + fibonacci(n - 2)) % M


def solve(n):

    for i in range(n):
        fibonacci(i)

    return fibonacci(n)


if __name__ == "__main__":
    random.seed(43)

    for _ in range(TEST_CASES):
        n = random.randrange(1, MAX_N)
        print(solve(n))
