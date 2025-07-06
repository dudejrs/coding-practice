import random
from pprint import pprint

TEST_CASES = 10
H_SIZE = 1000000
M_SIZE = 10


def initialize():

    s = ["a", "b", "c"]

    h = "".join([random.choice(s) for _ in range(H_SIZE)])
    m = "".join([random.choice(s) for _ in range(M_SIZE)])

    return (h, m)


def get_partial_match(m):
    pi = [0 for _ in range(len(m))]

    for begin in range(1, len(m)):
        for i in range(len(m) - begin):
            if m[begin + i] != m[i]:
                break
            pi[begin + i] = max(pi[begin + i], i + 1)

    return pi


def solve(h, m):
    ret = []
    pi = get_partial_match(m)

    begin, matched = 0, 0

    while begin <= len(h) - len(m):
        if matched < len(m) and h[begin + matched] == m[matched]:
            matched += 1
            if matched == len(m):
                ret.append(begin)
        else:
            if matched == 0:
                begin += 1
            else:
                begin += matched - pi[matched - 1]
                matched = pi[matched - 1]

    return ret


if __name__ == "__main__":
    random.seed(43)

    for _ in range(TEST_CASES):
        h, m = initialize()
        ret = solve(h, m)
        print(ret)
