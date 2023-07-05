import random

INFINTIY = 987654321 

class Graph :
	def __init__(self) :
		return
	def add_edge() :
		return
	def find_path(self, start, end, path=[]) :
		return []
	def find_all_path(self, start, end, path=[]):
		return []
	def find_shortest_path(self, start, end, path=[]):
		return []
	def __repre__(self):
		return


class MatrixGraph(Graph) : 
	def __init__(self, w) :
		super().__init__();
		self.n = len(w)
		self.w = [[INFINTIY for _ in range(len(w))] for _ in  range(len(w))]
		
		for i in range(len(w)) :
			for j in range(len(w[0])) : 
				if i != j :
					self.w[i][j] = w[i][j]
		return

	def __repr__ (self) :

		ret = "["
		for i in range(self.n) :
			if i != 0 : 
				ret += " "
			ret += "["
			for j in range(self.n) : 
				if (self.w[i][j] != INFINTIY) :
					ret += '{:>4d}'.format(self.w[i][j])
				else :
					ret += '{:>4s}'.format("_")
			ret += "]"
			if i != self.n-1 : 
				ret += "\n"
		ret += "]"

		return ret 


class LinkedListGraph(Graph) :

	def __init__(self, w) : 
		super().__init__()
		self.connection = [[] for _ in range(len(w))]
		self.n = len(w)

		for i in range(self.n) :
			for j, weight in zip(range(self.n), w[i]) :
				if weight != 987654321 and i != j: 
					self.connection[i].append((j, weight))
		return

	def __repr__(self) :

		ret = "["
		for i in range(self.n) :
			if i != 0 : ret += " "
			ret += str(self.connection[i])
			if i != self.n-1 : ret+="\n"
		ret += "]"
		return ret


def generate_matrix(n) :
	ret = [[INFINTIY for _ in range(n)] for _ in range(n)]

	for i in range(n) :
		for j in range(n) :
			tmp = random.randrange(1,100)
			if tmp % 7 == 0  or i == j:
				tmp = INFINTIY
			ret[i][j] = tmp


	return ret

if __name__ == "__main__" :
	random.seed(43)

	graph1 = MatrixGraph(generate_matrix(5))
	print(graph1)
	graph2 = LinkedListGraph(generate_matrix(5))
	print(graph2)

	pass;