import random

TEST_CASES = 10


def balance(amount, duration, rates, monthlyAmount) :
	balance = amount

	for _ in range(duration) :
		balance *= (1.0 + (rates/12.0)/100.0) 
		balance -= monthlyAmount

	return balance


def payment(amount, duration, rates) :
	lo = 0
	hi = amount 

	for _ in range(100): 
		mid = (lo + hi)/2.0
		if  balance(amount, duration, rates, mid) > 0 :
			lo = mid 
		else :
			hi = mid

	return hi

if __name__ == "__main__" :
	random.seed(43)

	for _ in range(TEST_CASES) :

		amount = random.randrange(10000)
		duration = random.randint(1,120)
		rates = random.random() * 5 + 2

		print(payment(amount, duration, rates))

	pass