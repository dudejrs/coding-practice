from typing import List
import random

N = 10
TEST_CASES = 10

dic = {
	"2" : "abc",
	"3" : "def",
	"4" : "ghi",
	"5" : "jkl",
	"6" : "mno",
	"7" : "pqks",
	"8" : "tuv",
	"9" : "wxyz"
}

def solve(digits: str) -> List[str] :
	global dic
		
	ret = []

	def dfs(i: int, acc: str) :
		if i == len(digits) :
			ret.append(acc)
			return


		for j in dic[digits[i]] : 
			dfs(i+1, acc + j)

		return

	dfs(0, "")

	return ret

if __name__ == "__main__" :
	random.seed(43)
	for _ in range(TEST_CASES) :
		digits = "".join([str(random.randrange(2,9)) for _ in range(random.randrange(1, N))])
		print(solve(digits))