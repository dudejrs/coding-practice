import random 
from pprint import pprint

TEST_CASES = 10
N = 10


def promising(cur, path, W) :

	if len(path) == len(W) and not W[path[-1]][0] : return False
	i=0
	while i < len(path)-1 :
		if path[i] == cur : return False
		i+=1


	return True

def check_node(cur, path, W) :
	if not promising(cur, path, W) : return
	if len(path) == len(W) : 
		path.append(0)
		pprint(path)
		path.pop(-1)
		return

	for j in range(len(W)) :
		if not W[cur][j] : continue
		path.append(j)
		check_node(j, path, W)
		path.pop(-1)

	return

def solve(W):
	check_node(0, [0], W)
	return 

if __name__ == "__main__" :

	random.seed(43)

	for _ in range(TEST_CASES) :
		n = random.randint(5,N)
		W = [[ random.randrange(0,2) == 0 for _ in range(n)]for _ in range(n)]

		solve(W)