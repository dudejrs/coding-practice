import random

TEST_CASES = 10
N = 10


def promising(col, cur) :

	for i in range(cur) :
		if( col[i] == col[cur] or abs(col[cur] - col[i]) == cur - i ) : return False

	return True

def print_queens(col) :

	for i, j in zip(range(len(col)), col) :
		for k in range(len(col)) :	
			if (k == j) :
				print("X", end=" ");
				continue
			print("O",end=" ")
		print()
	print()

	return 

def checknode(col, cur) :
	for j in range(len(col)) :
		col[cur+1] = j
		if not promising(col, cur+1) : continue
		if (cur+1 == len(col)-1)  :
			print_queens(col)
		else :
			checknode(col, cur+1)


	return


	
if __name__ == "__main__" :
	for _ in range(TEST_CASES) :
		n = random.randrange(5,N)
		col = [0 for _ in range(n)]
		checknode(col, -1)