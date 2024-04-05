from typing import List
import random

TEST_CASES = 10
N = 1000

def solve(colors: List[int]) -> List[int] :
	red, white, blue = 0, 0, len(colors)

	while white < blue :
		if colors[white] < 1 :
			colors[white], colors[red] = colors[red], colors[white]
			red += 1
			white += 1
		elif colors[white] > 1 :
			blue -=1
			colors[blue], colors[white] = colors[white], colors[blue]
		else :
			white += 1

	return colors

if __name__ == "__main__" :
	random.seed(43)

	for _ in range(TEST_CASES) :
		n = random.randrange(3, N)
		colors = [random.randrange(3) for _ in range(n)]
		print(solve(colors))