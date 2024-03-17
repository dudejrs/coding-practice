from collections import defaultdict

class Node :

	def __init__(self) :
		self.terminate = False
		self.children = defaultdict(Node)

class Trie : 

	def __init__(self) :
		self.root = Node()

	def insert(self, word: str) :
		node = self.root
		
		for char in word :
			node = node.children[char]

		node.terminate = True

	def search(self, word: str) -> bool :
		node = self.root

		for char in word :
			if not node.children[char] :
				return False

			node = node.children[char]

		return node.terminate

	def startsWidth(self, word: str) -> bool :
		node = self.root

		for char in word :
			if not node :
				return False
			node = node.children[char]

		return True

if __name__ == "__main__" :
	trie = Trie()

	trie.insert("apple")
	print(trie.search("apple"))
	print(trie.search("app"))
	print(trie.startsWidth("app"))