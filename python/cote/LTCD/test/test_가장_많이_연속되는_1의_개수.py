import pytest
from ..가장_많이_연속되는_1의_개수_구하기 import solve


@pytest.mark.parametrize(
    "nums, expected",
    [
        ([1, 1, 0, 1, 1, 1], 3),
        ([1, 0, 1, 0, 1, 0], 1),
        ([0, 0, 0, 0, 0, 0], 0),
    ],
)
def test_solve(nums: list[int], expected: int):
    assert solve(nums) == expected
