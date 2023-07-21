import random

TEST_CASES = 10
N = 10
M = 5




def promising(cur, n, m, W, vcolor) :

	for i in range(cur) :
		if not W[cur][i] : continue
		if vcolor[i] == vcolor[cur] : return False


	return True

def check_node(cur, n, m, W, vcolor) :
	
	if cur == n :
		print(vcolor)
		return

	for color in range(m):
		vcolor[cur] = color 
		if not promising(cur, n, m, W, vcolor) : continue	
		else :
			check_node(cur+1, n, m, W, vcolor)
	return

def solve(n, m, W) :
	vcolor = [0 for _ in range(n)]
	check_node(0, n, m, W, vcolor)
	return 

if __name__ == "__main__" :
	

	for _ in range(TEST_CASES) :
		n = random.randrange(5,N)
		m = random.randrange(2,M)
		W = [[ False for _ in range(n)] for _ in range(n) ]

		print(f"<<{n}, {m}>>")

		for i in range(n) :
			for j in range(i) :
				if random.randrange(0,2) == 1 :
					W[i][j] = True 
					W[j][i] = True


		solve(n,m,W)
		print()

	