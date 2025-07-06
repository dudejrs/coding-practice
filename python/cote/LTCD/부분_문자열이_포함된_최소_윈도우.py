import random
from collections import Counter

TEST_CASES = 10
N = 100000
K = 100000


def randchar() -> str:
    return chr(ord("a") + random.randrange(ord("z") - ord("a")))


def solve(s: str, t: str) -> str:
    need = Counter(t)
    missing = len(t)

    left = start = end = 0

    for right, char in enumerate(s, 1):
        missing -= need[char] > 0
        need[char] -= 1

        if missing == 0:
            while left < right and need[s[left]] < 0:
                need[s[left]] += 1
                left += 1

            if not end or right - left <= end - start:
                start, end = left, right

            need[s[left]] += 1
            missing += 1
            left += 1

    return s[start:end]


if __name__ == "__main__":
    random.seed(43)
    for _ in range(TEST_CASES):
        n = random.randrange(1, N)
        k = random.randrange(1, min(K, n))
        s = "".join([randchar() for _ in range(n)])
        t = "".join([randchar() for _ in range(k)])
        print(t, solve(s, t))
