import pytest

from ..다음_순열 import solve


@pytest.mark.parametrize(
    "nums, expected",
    [
        ([1, 2, 3], [1, 3, 2]),
        ([1, 3, 2], [2, 1, 3]),
        ([2, 1, 3], [2, 3, 1]),
        ([2, 3, 1], [3, 1, 2]),
        ([3, 1, 2], [3, 2, 1]),
        ([3, 2, 1], [1, 2, 3]),
        ([1, 1, 5], [1, 5, 1]),
    ],
)
def test_accuracy(nums: list[int], expected: list[int]):
    assert solve(nums) == expected
