import random 	


TEST_CASES = 10
N = 10
INF = 987654321


random.seed(43);


def initialize() : 

	ret = [];

	for i in range(0, N) :

		row = [];
		for j in range(0, N) :
			tmp = random.randint(0,100)
			if(i == j or tmp % 37 < 1) : tmp = INF
			row.append(tmp)

		ret.append(row)	

	return ret


def solve(cur, path, vistied, W) :

	if(len(path) == N) :
		return W[cur][0]; 

	ret = INF

	for i in range(0, N) :
		if not vistied[i] and  W[cur][i] != INF :
			visited[i] = True
			path.append(i)
			ret = min(ret, W[cur][i] + solve(i, path, vistied, W))
			visited[i] = False
			del path[-1]


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

		W = initialize()
		path = [0]
		visited = [False] * N;
		visited[0] = True
		ret = solve(0, path, visited, W);
		print_solution(W,ret);



