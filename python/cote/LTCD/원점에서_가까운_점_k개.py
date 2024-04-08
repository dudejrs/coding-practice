from typing import List, Tuple
from dataclasses import dataclass
import heapq
import random

TEST_CASES = 10
N = 1000
X = 1000
Y = 1000

@dataclass
class Point :
	y: int
	x: int
	distance: int

	def __lt__(self, other) :
		return self.distance < other.distance

	def __iter__(self) :
		return iter((self.y, self.x))

def solve(points: List[Tuple[int, int]], k:int) -> List[Tuple[int, int]]: 
	p = [Point(y, x, y ** 2 + x ** 2)  for (y, x) in points]
	heapq.heapify(p)

	ret = []

	for _ in range(k) :
		(y, x) = heapq.heappop(p)
		ret.append((y, x))

	return ret
	
if __name__ == "__main__" :
	random.seed(43)
	for _ in range(TEST_CASES) :
		n = random.randrange(3, N)
		k = random.randrange(1, n)
		points = [(random.randrange(X), random.randrange(Y)) for _ in range(n)]
		print(solve(points, k))
