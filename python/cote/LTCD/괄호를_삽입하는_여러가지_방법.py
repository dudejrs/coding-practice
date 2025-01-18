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