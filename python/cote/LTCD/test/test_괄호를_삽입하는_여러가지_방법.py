import os
from pathlib import Path
from ..괄호를_삽입하는_여러가지_방법 import solve


def test_accuracy():
    path = Path(__file__).parent.parent

    with open(f'{path}/data/괄호를_삽입하는_여러가지_방법.txt') as f:
        for _ in range(int(f.readline())):
            expression = f.readline().strip()
            answer = list(map(int, f.readline().strip().split(" ")))
            assert sorted(answer) == sorted(solve(expression))
