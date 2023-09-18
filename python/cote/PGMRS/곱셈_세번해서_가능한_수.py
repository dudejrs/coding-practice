import random
import math

TEST_CASES = 10
MAX_BUTTONS_SIZE=100
MAX_NUMS_SIZE = 100
N = 10000


def power_possible(num, n, depth) :  
	cur = num

	while depth > 0 :
		cur = cur/ n
		depth -= 1

	return cur == 1


def search(buttons, chosen, num):

	ret = 0

	for button in buttons :
		
		if num % button != 0 : continue
		if num / button == 1 : 
			return (1 if len(chosen) == 2 else 0)

		if power_possible(num, button, 3-len(chosen)) :
			return 1

		chosen.append(button)
		
		if len(chosen) == 2 : 
			ret = 1
		else : 
			ret = search(buttons, chosen, num/button)
		chosen.pop(-1)

		if ret == 1 : 
			return 1 


	return 0;

def solve(buttons, nums) :

	cache = [[-1 for num in nums] for _ in range(3)] 

	ret = []

	return [ search(buttons, [], num) for num in nums ]

if __name__ == "__main__" :

	random.seed(43)

	for _ in range(TEST_CASES) :

		buttons_size = random.randint(3, MAX_BUTTONS_SIZE)
		nums_size = random.randint(1,MAX_NUMS_SIZE)

		buttons = random.sample([ i for i in range(1,buttons_size*2)], buttons_size)	
		nums = [ random.randint(1,N) for _ in range(nums_size) ]

		print(solve(buttons, nums))


	buttons= [2,3,4,5,6]
	nums = [6, 12, 144, 28, 8, 121, 17, 78, 125]
	print(solve(buttons, nums))

	pass