from typing import List
from collections import Counter
import random

TEST_CASES = 10


def task(num: int) -> int:
    return chr(ord("a") + num)


def solve(tasks: List[int], n: int) -> int:
    counter = Counter(tasks)
    result = 0

    while True:
        sub_count = 0

        for task, _ in counter.most_common(n + 1):
            sub_count += 1
            result += 1

            counter.subtract(task)
            counter += Counter()

        if not counter:
            break

        result += n - sub_count + 1

    return result


if __name__ == "__main__":
    random.seed(43)

    for _ in range(TEST_CASES):
        tasks = random.sample([chr(ord("a") + num) for num in range(26)], random.randrange(2, 26))
        n = random.randrange(1, 30)
        print(solve(tasks, n))
