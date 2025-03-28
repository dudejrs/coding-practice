import random

TEST_CASE = 10
N = 5


def initialize():

    l = []
    for _ in range(2 * N):
        tmp = (random.random()) * (random.randrange(10 * N))
        l.append(tmp)

    l.sort()

    return l


def decision(gap, locations, cameras):

    limit = -1
    selected = 0

    for location in locations:
        if limit <= location:
            selected += 1
            limit = location + gap

    return selected >= cameras


def search(locations, cameras):
    lo, hi = 0, sum(locations)

    for _ in range(100):
        mid = (lo + hi) / 2.0
        if decision(mid, locations, cameras):
            lo = mid
        else:
            hi = mid

    return lo


if __name__ == "__main__":

    for _ in range(TEST_CASE):
        locations = initialize()
        cameras = random.randrange(2, N)
        print(search(locations, cameras))
