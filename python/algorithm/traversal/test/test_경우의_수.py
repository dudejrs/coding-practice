import pytest

from ..경우의_수 import solve


@pytest.mark.parametrize(
    "n, k, r, expected", [(2, 1, 2, 1), (2, 2, 3, 1), (3, 2, 5, 1), (4, 2, 2, 2)]
)
def test_accuracy(n: int, k: int, r: int, expected: int):
    assert solve(n, k, r) == expected
