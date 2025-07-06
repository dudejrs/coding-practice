import random
from collections import Counter

TEST_CASES = 10
N = 100000
K = 100


def randchr() -> str:
    return chr(ord("A") + random.randrange(ord("Z") - ord("A")))


def solve(s: str, k: int) -> int:

    left = right = 0
    counts = Counter()

    for right in range(1, len(s) + 1):
        counts[s[right - 1]] += 1

        max_char_n = counts.most_common(1)[0][1]

        if right - left - max_char_n > k:
            counts[s[left]] -= 1
            left += 1

    return right - left


if __name__ == "__main__":
    random.seed(43)
    for _ in range(TEST_CASES):
        n = random.randrange(1, N)
        k = random.randrange(1, min(n, K))
        s = "".join([randchr() for _ in range(n)])
        print(solve(s, k))
