import pytest
from ..숫자_변환_가능_여부_검증 import solve


@pytest.mark.parametrize(
    "input, expected",
    [
        ("0", True),
        ("0.1", True),
        ("1a", False),
        ("2e10", True),
        ("-90e3", True),
        ("1e", False),
        ("e3", False),
        ("99e2.5", False),
        ("53.5e93", True),
        ("--6", False),
        ("-+3", False),
        ("95a54e53", False),
    ],
)
def test_accuracy(input: str, expected: bool):
    assert solve(input) == expected
