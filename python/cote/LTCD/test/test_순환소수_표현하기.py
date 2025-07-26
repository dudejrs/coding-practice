import pytest
from ..순환소수_표현하기 import solve


@pytest.mark.parametrize(
    "numerator, dominator, expected",
    [
        (1, 2, "0.5"),
        (2, 1, "2"),
        (2, 3, "0.(6)"),
    ],
)
def test_accuracy(numerator: int, dominator: int, expected: str):
    assert solve(numerator, dominator) == expected
