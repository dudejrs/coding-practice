import random


TEST_CASES = 30
N = 4
Brakets = ["[", "]", "(", ")", "{", "}"]


def solve(s: str) -> bool:

    stack = []
    braketMap = {"(": ")", "{": "}", "[": "]"}

    for char in s:
        if char in braketMap.keys():
            stack.append(braketMap[char])
        elif not len(stack) or char != stack.pop():
            return False

    return len(stack) == 0


if __name__ == "__main__":

    random.seed(41)

    for _ in range(TEST_CASES):
        s = "".join([random.choice(Brakets) for _ in range(N)])
        print(s, solve(s))
