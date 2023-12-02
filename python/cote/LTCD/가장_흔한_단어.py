import re
from typing import *
from collections import Counter


def solve(paragraph : str, banned : List[str]) -> str :

	words = [ word for word in re.sub('[^\w\s]','',paragraph).lower().split(" ")
				if word not in banned]

	counts = Counter(words)

	return counts.most_common()[0][0]

if __name__ == "__main__" :

	with open("data/가장_흔한_단어.txt") as fout :

		TEST_CASES = int(fout.readline());
		for _ in range(TEST_CASES) :
			paragraph = fout.readline().strip();
			banned = fout.readline().strip().split(" ")
			print(solve(paragraph, banned))

