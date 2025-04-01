import pytest

from ..순열 import solve


@pytest.mark.parametrize(
    "n, k, expected",
    [
        (2, 1, {(2,), (1,)}),
        (2, 2, {(1, 2), (2, 1)}),
        (3, 2, {(1, 2), (1, 3), (2, 1), (2, 3), (3, 1), (3, 2)}),
    ],
)
def test_accuracy(n: int, k: int, expected: set[tuple[int, ...]]):
    assert set(tuple(i) for i in solve(n, k)) == expected
