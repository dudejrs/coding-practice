import random

TEST_CASES = 10
N = 10000


def solve(s: str) -> int:
    used = {}
    max_length = start = 0
    for i, c in enumerate(s):
        if c in used and start <= used[c]:
            start = used[c] + 1
        else:
            max_length = max(max_length, i - start + 1)
        used[c] = i

    return max_length


if __name__ == "__main__":
    random.seed(43)
    for _ in range(TEST_CASES):
        l = random.randrange(1, N)
        s = "".join([chr(random.randrange(ord('a'), ord('z') + 1)) for _ in range(l)])
        print(solve(s))
