import random

TEST_CASES = 10

def partial_sum(t) :
	ret = [0 for _ in range(len(t))]

	ret[0] = t[0]

	for i in range(1,len(t)) :
		ret[i] = ret[i-1] + t[i]

	return ret

if __name__ == "__main__" :
	n = 10
	for _ in range(TEST_CASES) :
		t = [ random.randrange(1,10) for i in range(n)]
		print(partial_sum(t))


