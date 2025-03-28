from typing import *
from pprint import pprint


def solve(logs: List[str]) -> List[str]:

    digits, others = [], []

    for log in logs:
        if log.split(" ")[1].isdigit():
            digits.append(log)
        else:
            others.append(log)

    others.sort(key=lambda l: (l.split(" ")[1:], l.split(" ")[0]))

    return [*others, *digits]


if __name__ == "__main__":

    with open("data/로그파일_재정렬.txt") as fout:

        TEST_CASES = int(fout.readline())

        for _ in range(0, TEST_CASES):

            NUM_LOGS = int(fout.readline())
            logs = []

            for _ in range(NUM_LOGS):
                logs.append(fout.readline().strip())

            pprint(solve(logs))
