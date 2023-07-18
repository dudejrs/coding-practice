import random
from pprint import pprint

TEST_CASES = 10
N = 5

def partial_sum(t) : 
	ret = [0 for i in range(len(t))]

	ret[0] = t[0]

	for i in range(1,len(t)) :
		ret[i] = ret[i-1] + t[i]

	return ret


def partial_sum_2dim(t) :
	
	ret =[[]for _ in range(len(t))]

	for i in range(len(t)) :
		for _ in range(len(t)) :
			ret[i] = partial_sum(t[i])

	for i in range(1, len(t)) :
		for j in range(len(t)) :
			ret[i][j] += ret[i-1][j] 

	return ret


def grid_sum(t, y1, x1, y2, x2):

	pSum = partial_sum_2dim(t)

	ret = pSum[y2][x2]
	if(y1 > 0) : ret -= pSum[y1-1][x2]
	if(x1 > 0) : ret -= pSum[y2][x1-1]
	if y1 >0 and x1>0  : ret += pSum[y1-1][x1-1]

	return ret

if __name__ == "__main__" :
	random.seed(43)

	
	for _ in range(TEST_CASES) :

		t = [[ random.randrange(0,10) for j in range(N)]for i in range(N)]

		(y1,y2) = random.sample(range(N),2)  
		if y1 > y2 : y1, y2 = y2, y1

		(x1,x2) = random.sample(range(N),2)
		if x1 > x2 : x1,x2 = x2,x1
		

		pprint(t)
		print (x1, y1, x2, y2)
		print(grid_sum(t, y1, x1, y2, x2))
		print()