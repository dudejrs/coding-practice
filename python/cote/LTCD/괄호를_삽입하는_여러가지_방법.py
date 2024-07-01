from typing import List


def solve(expression: str) -> List[int] :
	def compute(left, right, op) :
		ret = [] 
		for l in left :
			for r in right :
				ret.append(eval(str(l) + op + str(r)))

		return ret

	if expression.isdigit() :
		return [int(expression)]

	ret = [] 
	for i, v in enumerate(expression) :
		if v in "-+*" :
			left = solve(expression[:i])
			right = solve(expression[i + 1:])
			ret.extend(compute(left, right, v))

	return ret

if __name__ == "__main__" :
	with open('./data/괄호를_삽입하는_여러가지_방법.txt') as f :
		for _ in range(int(f.readline())) :
			expression = f.readline().strip()
			answer = list(map(int, f.readline().strip().split(" ")))
			print(answer, solve(expression))