import random 	


TEST_CASES = 10
N = 10
INF = 987654321


random.seed(43);

cache = [[-1]*(1<<N)] * N


def initialize() : 

	ret = [];

	for i in range(0, N) :

		row = [];
		for j in range(0, N) :
			tmp = random.randint(0, 100)
			if(i == j or tmp % 37 < 1) : tmp = INF
			row.append(tmp)

		ret.append(row)	

	return ret


def solve(cur, vistied, W) :


	if (vistied == (1<<N)-1) : return W[cur][0]

	ret = cache[cur][vistied];
	if ret != -1 : return ret

	ret = INF

	for i in range(0, N) :
		if not (vistied & (1 << i) ) and  W[cur][i] != INF :
			if(cur == 0) : print(W[cur][i] + solve(i,  vistied | (1 << i), W))
			ret = min(ret, W[cur][i] + solve(i,  vistied | (1 << i), W))


	cache[cur][vistied] = ret;

	return ret

def print_solution(W, ret) :
	for i in range(0, N):
		tmp = list(map(
			lambda a :   " _ " if a == INF  else "%3d"%a, W[i])
		)
		print(" ".join(tmp))
	print("ret : {}".format(ret))
	print("\n\n")



if __name__ == "__main__"  : 

	for _ in range(0,TEST_CASES) :

		cache = [[-1]*(1<<N)] * (N+1)

		W = initialize()
		visited = 1 
		ret = solve(0, visited, W);
		print_solution(W,ret);



