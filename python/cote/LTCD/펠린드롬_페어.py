from collections import defaultdict
from typing import List


class Node:

    def __init__(self):
        self.children = defaultdict(Node)
        self.word_id = -1
        self.palindrome_word_ids = []


class Trie:

    def __init__(self):
        self.root = Node()

    @staticmethod
    def is_palindrome(word: str) -> bool:
        return word[::] == word[::-1]

    # 단어를 거꾸로한 트라이를 생성
    def insert(self, index, word):
        node = self.root

        for i, char in enumerate(reversed(word)):
            if self.is_palindrome(word[0 : len(word) - i]):
                node.palindrome_word_ids.append(index)
            node = node.children[char]

        node.word_id = index

    def search(self, index, word) -> List[List[int]]:
        result = []
        node = self.root

        while word:
            # case1 : 검색 단어를 탐색 도중에 다른 단어에 끝에 도착하고, 검색 단어의 나머지 부분이 펠린드롬인 경우
            if node.word_id >= 0:
                if self.is_palindrome(word):
                    result.append([index, node.word_id])

            if not word[0] in node.children:
                return result

            node = node.children[word[0]]
            word = word[1:]

        # case2 : 완전히 반전인 단어가 존재하는 경우
        if node.word_id >= 0 and node.word_id != index:
            result.append([index, node.word_id])

        # case2 : 검색 단어의 끝에 도착하고, 나머지 부분이 팰린드롬인 단어가 있는 경우
        for palindrome_word_id in node.palindrome_word_ids:
            result.append([index, palindrome_word_id])

        return result


def solve(workds: List[int]) -> List[List[int]]:
    trie = Trie()

    for i, word in enumerate(words):
        trie.insert(i, word)

    results = []

    for i, word in enumerate(words):
        results.extend(trie.search(i, word))

    return results


if __name__ == "__main__":

    f = open("data/펠린드롬_페어.txt")
    testcases = int(f.readline())

    for _ in range(testcases):
        words = f.readline().strip().split(" ")
        tokens = f.readline().strip().split(",")
        answer = [] if len(tokens) == 1 else [list(map(int, token.split(" "))) for token in tokens]
        print(f"answer: {answer}")
        print(f"sovled: {solve(tokens)}")
