import pytest
from collections import Counter
from ..reservoir import solve


@pytest.mark.parametrize(
    "n, k, T, threshold",
    [
        (100, 10, 10000, 0.01),
        (50, 5, 5000, 0.015),
    ],
)
def test_solve(n: int, k: int, T: int, threshold: float):
    counts: Counter = Counter()

    for _ in range(T):
        items = list(range(n))
        sample = solve(items, k)
        counts.update(sample)

    expected = k / n

    for i in range(n):
        freq = counts[i] / T
        assert abs(freq - expected) < threshold
