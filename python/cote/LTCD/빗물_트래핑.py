from typing import *
import random

TEST_CASES = 10
N = 10
MAX_HEIGHT = 100


# 2 Pointer


def solve1(heights: List[int]) -> int:

    left, right = 0, len(heights) - 1
    left_max, right_max = 0, 0
    volume = 0

    while left < right:
        left_max, right_max = max(left_max, heights[left]), max(right_max, heights[right])

        if left_max <= right_max:
            volume += left_max - heights[left]
            left += 1
        else:
            volume += right_max - heights[right]
            right -= 1

    return volume


# Stack
def solve2(heights: List[int]) -> int:

    stack = []
    volume = 0

    for i in range(len(heights)):
        while stack and heights[i] > heights[stack[-1]]:
            top = stack.pop()

            if not len(stack):
                break

            distance = i - stack[-1] - 1
            waters = min(heights[i], heights[stack[-1]]) - heights[top]

            volume += distance * waters

        stack.append(i)

    return volume


if __name__ == "__main__":
    random.seed(17)

    for _ in range(TEST_CASES):

        n = random.randrange(2, N) + 2
        h = random.randrange(1, MAX_HEIGHT) + 1
        heights = [random.randrange(h) for _ in range(n)]
        print(solve1(heights), solve2(heights))
