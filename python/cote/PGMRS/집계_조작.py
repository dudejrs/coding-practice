import random

TEST_CASES = 10
N = 100_000_000
M = 100_000


def get_sum(survey):

    max_val = max(survey)
    min_val = min(survey)

    ret = 0

    for num in survey:
        if num not in [max_val, min_val]:
            ret += num

    return ret


def solve(n, survey):
    ret = 0

    max_val = max(survey)
    min_val = min(survey)

    for i in range(-1, 2):
        if min_val + i <= 0:
            continue

        survey.append(min_val + i)
        ret = max(ret, get_sum(survey))
        survey.pop(-1)

        if max_val + i > n:
            continue

        survey.append(max_val + i)
        ret = max(ret, get_sum(survey))
        survey.pop(-1)

    return ret


if __name__ == "__main__":
    random.seed(43)

    for _ in range(TEST_CASES):
        n = random.randint(1, N)
        m = random.randint(1, M)
        survey = [random.randint(1, n) for _ in range(m)]

        print(solve(n, survey))
