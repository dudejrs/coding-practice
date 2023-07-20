import random
from functools import reduce
from pprint import pprint

TEST_CASES = 10
N = 10
MAX_WEIGHT = 15



def promising(cur, total , left, W, stack, w) :
	return (total + left >= W) and ((total == W) or (total + w[cur] <= W))


def checknode(cur, total, left, W, stack, w) :
	if promising(cur, total, left, W, stack, w) :
		if total == W :
			pprint(stack)
		else :
			stack.append(cur)
			checknode(cur+1, total + w[cur], left-w[cur], W, stack, w)
			stack.remove(cur)
			checknode(cur+1, total, left-w[cur], W, stack, w)

	return 

def solve(w, W) :

	stack = []
	left = reduce(lambda a,b : a+b , w)

	checknode(0, 0, left, W, stack, w)
	return 

if __name__ == "__main__" :
	random.seed(43)

	for _ in range(TEST_CASES) :
	
		n = random.randint(5, N)
		w = [ random.randrange(1,MAX_WEIGHT) for _ in range(n)]
		w.sort(key= lambda a : -a)
		total = reduce(lambda a,b : a+b , w)
		W = int(0.5 * total)

		print(n, W)
		print (w)
		
		solve( w, W)

		print("\n\n")

