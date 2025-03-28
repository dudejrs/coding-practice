from typing import List
import heapq


def solve(people: List[List[int]]) -> List[List[int]]:
    heap = []

    for person in people:
        heapq.heappush(heap, (-person[0], person[1]))

    result = []

    while heap:
        person = heapq.heappop(heap)
        result.insert(person[1], [-person[0], person[1]])

    return result


if __name__ == "__main__":
    with open("data/키에_따른_대기열_재구성.txt") as f:
        testcases = int(f.readline())
        for _ in range(testcases):
            n = int(f.readline())
            people = [list(map(int, f.readline().split(" "))) for _ in range(n)]
            print(solve(people))
