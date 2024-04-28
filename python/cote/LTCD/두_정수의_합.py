import random

TEST_CASES = 10
MAX_VAL = 1000

def solve(a: int, b: int)-> int :
	MASK = 0xFFFFFFFF
	MAX = MAX_VAL * 2

	a_ = bin(a & MASK)[2:].zfill(32)
	b_ = bin(b & MASK)[2:].zfill(32)

	result = []
	carry = 0
	sum = 0

	for i in range(32) :
		A, B = int(a_[31 - i]), int(b_[31 - i])

		Q1 = A & B
		Q2 = A ^ B
		Q3 = Q2 & carry
		sum = carry ^ Q2 
		carry = Q1 | Q3

		result.append(str(sum))

	if carry == 1 :
		result.append('1')

	result = int(''.join(result[::-1]), 2) & MASK

	if result > MAX :
		result = ~(result & MASK)

	return result

if __name__ == "__main__" :
	random.seed(43)
	for _ in range(TEST_CASES) :
		a, b= random.randrange(MAX_VAL), random.randrange(MAX_VAL)
		print(a, b, solve(a, b))