from typing import List

Matrix = List[List[int]]


def calculate_range_sum(original: Matrix) -> Matrix:
    n, m = len(original), len(original[0])
    result = [[0 for _ in range(m + 1)] for _ in range(n + 1)]

    for i in range(n):
        for j in range(m):
            result[i + 1][j + 1] = (
                result[i][j + 1] + result[i + 1][j] - result[i][j] + original[i][j]
            )

    return result


def solve(matrix: Matrix, row1: int, col1: int, row2: int, col2: int) -> int:
    range_sum = calculate_range_sum(matrix)
    return (
        range_sum[row2 + 1][col2 + 1]
        - range_sum[row1][col2 + 1]
        - range_sum[row2 + 1][col1]
        + range_sum[row1][col1]
    )
