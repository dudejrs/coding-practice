import random

N = 20
MAX_VALUE = 100
TEST_CASES = 10

cache = [-1] * (N + 1)
answer = [-1] * (N + 1)

random.seed(43)


def solve(cur, l):

    ret = cache[cur + 1]

    if ret != -1:
        return ret

    ret = 1
    j = -1

    for i in range(0, N):
        if cur == -1 or l[cur] < l[i]:
            tmp = 1 + solve(i, l)
            if ret < tmp:
                ret = tmp
                j = i

    cache[cur + 1] = ret
    answer[cur + 1] = j

    return ret


def print_answer(cur, l, v):

    if cur != -1:
        v.append(l[cur])

    next_idx = answer[cur + 1]

    if next_idx != -1:
        print_answer(next_idx, l, v)


if __name__ == "__main__":

    for _ in range(0, TEST_CASES):

        cache = [-1] * (N + 1)
        answer = [-1] * (N + 1)
        l = [random.randint(0, MAX_VALUE) for _ in range(0, N)]
        v = []
        print(solve(-1, l) - 1)
        print_answer(-1, l, v)
        print(v)
