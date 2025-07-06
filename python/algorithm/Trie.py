from collections import defaultdict


class Node:

    def __init__(self):
        self.terminals = defaultdict(int)
        self.children = defaultdict(Node)

    def add(self, word, offset=0):
        length = len(word) - offset
        self.terminals[length] += 1

        if length > 0:
            c = word[offset]
            child = self.children[c]
            child.add(word, offset + 1)

    def search(self, word, offset=0):
        if offset == len(word):
            return self.terminals[0] > 0

        if word[offset] not in self.children.keys():
            return False

        return self.children[word[offset]].search(word, offset + 1)

    def count(self, keyword, offset=0):
        if offset == len(keyword):
            return self.terminals[0]

        if keyword[offset] == "?":
            return self.terminals[len(keyword) - offset]

        if keyword[offset] not in self.children.keys():
            return 0

        return self.children[keyword[offset]].count(keyword, offset + 1)


if __name__ == "__main__":

    trie = Node()

    words = ["hello", "hell", "helio", "help", "held", "helicopter"]

    for word in words:
        trie.add(word)

    print(trie.search("hell"))
    print(trie.search("helium"))
    print(trie.count("hel?"))
