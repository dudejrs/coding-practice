from typing import Protocol
from collections import Counter
import pytest

from ..무작위_인덱스_추출 import solve


class IndexPicker(Protocol):
    def pick(self, k: int) -> int: ...


@pytest.fixture
def index_picker() -> IndexPicker:
    return solve(items=[1, 2, 2, 3, 3, 3, 4, 4, 4, 4])


@pytest.mark.parametrize("k, expected", [(1, [0]), (2, [1, 2]), (3, [3, 4, 5]), (4, [6, 7, 8, 9])])
def test_accuracy(index_picker: IndexPicker, k: int, expected: list[int]):
    T = 1000

    for _ in range(T):
        assert index_picker.pick(k) in expected


@pytest.mark.parametrize("k, expected", [(1, [0]), (2, [1, 2]), (3, [3, 4, 5]), (4, [6, 7, 8, 9])])
def test_frequency(index_picker: IndexPicker, k: int, expected: list[int]):
    T = 10000
    threshold = 0.01
    counts = Counter()

    for _ in range(T):
        counts.update([index_picker.pick(k)])

    expected_freq = 1 / len(expected)
    for i in expected:
        freq = counts[i] / T
        assert abs(freq - expected_freq) < threshold
