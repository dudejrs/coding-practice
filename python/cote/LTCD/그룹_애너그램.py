from typing import *
from collections import defaultdict

def solve( words : List[str] ) -> List[List[str]] :

	anagrams = defaultdict(list)

	for word in words :
		anagrams[''.join(sorted(word))].append(word)

	return list(anagrams.values())

if __name__ == "__main__" :

	with open("data/그룹_애너그램.txt") as fout :

		TEST_CASES = int(fout.readline())
		
		for _ in range(TEST_CASES) :
			words = fout.readline().strip().split(" ")
			print(solve(words))

