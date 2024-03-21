from typing import *

def solve( s : str) -> str :

	def expand( left: int, right:int) -> str :

		while left>=0 and right < len(s) :
			if s[left] != s[right] : 
				break
			left -= 1
			right += 1


		return s[left+1 : right]

	if (len(s) < 2) :
		return ""
	if s == s[::-1] :
		return s

	result = ''
	for i in range(len(s)-1) :
		result = max(result, expand(i,i+1), expand(i,i+2), key=len)

	return result

if __name__ == "__main__" :

	with open("data/가장_긴_팰린드롬_부분_문자열.txt") as fout :

		TEST_CASES = int(fout.readline())

		for _ in range(TEST_CASES) :
			s = fout.readline().strip()
			answer = fout.readline().strip()
			print(solve(s), answer)
