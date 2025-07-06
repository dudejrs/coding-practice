import re


def solve(word) -> bool:
    word = word.lower()
    word = re.sub("[^a-z0-9]", "", word)

    return word == word[::-1]


if __name__ == "__main__":
    with open("data/유효한_팰린드롬.txt") as fout:
        TEST_CASE = int(fout.readline())
        for _ in range(TEST_CASE):
            word = fout.readline()
            print(solve(word))
