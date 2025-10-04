import pytest
from typing import Iterable
from ..array_stack import ArrayStack


@pytest.fixture
def stack():
    return ArrayStack[int](5)


@pytest.fixture
def empty_stack():
    return ArrayStack[int](5)


@pytest.mark.parametrize(
    "initial_values, pop_count, expected_remaining, expected_removed",
    [
        (range(5), 1, range(4), [5]),
        (range(5), 2, range(3), [4, 5]),
        (range(3), 3, [], range(3)),
        ([1, 1, 1], 2, [1], []),
        ([1, 2, 2], 2, [1], [2]),
    ],
)
def test_accruacy(
    initial_values: Iterable[int],
    pop_count: int,
    expected_remaining: Iterable[int],
    expected_removed: Iterable[int],
    stack: ArrayStack[int],
):

    for item in initial_values:
        stack.push(item)

    for _ in range(pop_count):
        stack.pop()

    assert all(item in stack for item in expected_remaining)
    assert all(item not in stack for item in expected_removed)


def test_should_raise_exception_when_overflow(stack):

    with pytest.raises(Exception):
        for _ in range(6):
            stack.push(1)


def test_should_raise_exception_when_empty(empty_stack):
    with pytest.raises(Exception):
        empty_stack.pop()
