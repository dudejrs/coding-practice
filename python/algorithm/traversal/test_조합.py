import pytest

from .조합 import solve


@pytest.mark.parametrize(
    "n, k, expected",
    [
        (2, 1, {frozenset([2]), frozenset([1])}),
        (3, 1, {frozenset([3]), frozenset([2]), frozenset([1])}),
        (3, 2, {frozenset([3, 2]), frozenset([3, 1]), frozenset([2, 1])}),
    ],
)
def test_accuracy(n, k, expected):
    assert solve(n, k) == expected
