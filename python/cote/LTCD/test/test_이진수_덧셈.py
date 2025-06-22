import pytest
from ..이진수_덧셈 import solve


@pytest.mark.parametrize(
    "a, b, expected",
    [
        ("11", "1", "100"),
        ("11", "0", "11"),
        ("0", "11", "11"),
        ("0", "0", "0"),
    ],
)
def test_solve(a: str, b: str, expected: str):
    assert solve(a, b) == expected
