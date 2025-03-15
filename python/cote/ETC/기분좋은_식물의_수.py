from dataclasses import (
    dataclass,
)
import random
import heapq

TEST_CASES = 10
MAX_PLANTS_LEN = 300_000
MAX_WATERED_LEN = 300_000


@dataclass
class Plant:
    date: int
    index: int

    def __gt__(self, other):
        return self.date > other.date

    def __iter__(self):
        return iter(
            (
                self.date,
                self.index,
            )
        )


def solve(plants, watered):
    h = [Plant(v, i) for i, v in enumerate(plants)]
    m = {plant.index: plant for plant in h}
    heapq.heapify(h)

    ret = []
    for today, target in zip(
        range(
            1,
            len(watered) + 1,
        ),
        watered,
    ):
        m[target].date = today + plants[m[target].index]

        while h and h[0].date < today:
            heapq.heappop(h)

        ret.append(len(h))

    return ret


if __name__ == "__main__":
    random.seed(43)

    for _ in range(TEST_CASES):
        n = random.randrange(1, MAX_PLANTS_LEN)
        m = random.randrange(1, MAX_WATERED_LEN)
        plants = [random.randrange(m) for _ in range(n)]
        watered = [random.randrange(n) for _ in range(m)]

        print(
            solve(
                plants,
                watered,
            )
        )
