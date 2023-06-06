import random


TEST_CASES = 10
N = 10
INF = 987654321


random.seed(43);

cache = [[-1 for _ in range(0,(1<<N))] for _ in range(0,N)]


def initialize() : 

	ret = [ [0 for j in range(0,N)] for i in range(0,N) ];
	ret[1][2] = 3;
	for i in range(0, N) :
		ret[i][i] = INF;
		for j in range(0, i) :
			tmp = random.randint(1, 100)
			if(tmp % 37 < 1) : tmp = INF
			ret[i][j] = tmp;
			ret[j][i] = tmp;



	return ret


def solve(cur, visited, W) :


	if (visited == (1<<N)-1) : return W[cur][0]

	ret = cache[cur][visited];
	if ret != -1 : return ret

	ret = INF

	for i in range(0, N) :
		if not (visited & (1 << i) ) and  W[cur][i] != INF :
			newvisited =  visited + (1<<i)
			ret = min(ret, W[cur][i] + solve(i,  newvisited, W))

	cache[cur][visited] = ret;


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

	for _ in range(0,1) :

		cache = [[-1 for _ in range(0,(1<<N))] for _ in range(0,N)]

		W = initialize()
		visited = 1 
		ret = solve(0, visited, W);
		print_solution(W,ret);



