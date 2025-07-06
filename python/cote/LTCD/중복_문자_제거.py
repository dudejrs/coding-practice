import random
from collections import Counter

TEST_CASES = 10
LENGTH = 100


def randomChar():
    return chr(random.choice(range(ord("a"), ord("z"))))


# 재귀
def solve1(s):

    for c in sorted(set(s)):
        suffix = s[s.index(c) :]
        if set(s) == set(suffix):
            return c + solve1(suffix.replace(c, ""))

    return ""


# stack
def solve2(s):

    counts, selected, stack = Counter(s), set(), []

    for c in s:
        counts[c] -= 1

        if c in selected:
            continue

        while stack and stack[-1] > c and counts[stack[-1]] > 0:
            selected.remove(stack.pop())

        stack.append(c)
        selected.add(c)

    return "".join(stack)


if __name__ == "__main__":
    random.seed(43)
    for _ in range(TEST_CASES):
        s = "".join([randomChar() for _ in range(random.randrange(10, LENGTH))])
        print(solve1(s), solve2(s))
