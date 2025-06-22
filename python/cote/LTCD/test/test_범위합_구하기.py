import pytest
from ..범위합_구하기 import Matrix, solve


@pytest.fixture
def matrix():
    return [
        [1, 2, 3, 4, 5],
        [6, 7, 8, 9, 10],
        [11, 12, 13, 14, 15],
        [16, 17, 18, 19, 20],
        [21, 22, 23, 24, 25],
    ]


@pytest.mark.parametrize(
    "row1, col1, row2, col2, expected_sum",
    [
        (0, 0, 4, 4, 325),
        (0, 0, 0, 0, 1),
        (1, 1, 2, 2, 40),
    ],
)
def test_범위합_구하기(
    matrix: Matrix, row1: int, col1: int, row2: int, col2: int, expected_sum: int
):
    assert solve(matrix, row1, col1, row2, col2) == expected_sum
