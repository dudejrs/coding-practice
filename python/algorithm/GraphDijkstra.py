import random

INFINITY = 987654321
TEST_CASES = 10

class Graph :

	def __init__(self) :
		pass
	def __repr__(self) :
		pass
	def find_shortest_path_from(self):
		pass


class MatrixGraph(Graph) :

	def __init__(self, w) :
		self.n = len(w)
		self.w = [[w[i][j] for j in range(self.n)] for i in range(self.n)]
		return

	def __repr__(self) :
		ret = "["
		for i in range(self.n) :
			if i != 0 : 
				ret += " "
			ret += "["
			for j in range(self.n) : 
				if (self.w[i][j] != INFINITY) :
					ret += '{:>4d}'.format(self.w[i][j])
				else :
					ret += '{:>4s}'.format("_")
			ret += "]"
			if i != self.n-1 : 
				ret += "\n"
		ret += "]"

		return ret 

	def find_shortest_path_from(self, src):
		ret = []
		vnear = src
		distance = [ self.w[src][i] for i in range(self.n) ]
		nearest = [ src for i in range(self.n ) ]

		distance[src] = -1

		for k in range(self.n-1) :

			vcur = 0
			min_distance = INFINITY

			for i in range(self.n) :
				if 0 < distance[i] and distance[i] < min_distance :
					vcur = i
					min_distance = distance[i]

			ret.append((src, vcur, min_distance))
			vnear = vcur

			for i in range(self.n) :
				if(distance[vnear] + self.w[vnear][i] < distance[i]) :
					distance[i] = distance[vnear] + self.w[vnear][i]
					nearest[i] = vnear

			distance[vnear] = -1

		return ret


class LinkedListGraph(Graph) :

	def __init__(self, w) :
		self.n = len(w)
		self.connection = [[] for _ in range(self.n)] 

		for i in range(self.n) :
			for j, weight in zip(range(self.n), w[i]):
				if weight != INFINITY :
					self.connection[i].append((j,weight))
		return

	def __repr__(self) :
		ret = "["
		for i in range(self.n) :
			if i != 0 : ret += " "
			ret += str(self.connection[i])
			if i != self.n-1 : ret+="\n"
		ret += "]"
		return ret

	def find_shortest_path_from(self, src):
		ret = []
		vnear = src
		distance = [ INFINITY for i in range(self.n) ]
		nearest = [ src for i in range(self.n ) ]

		for i, weight in self.connection[src] :
			distance[i] = weight

		distance[src] = -1

		for k in range(self.n-1) :

			vcur = 0
			min_distance = INFINITY

			for i in range(self.n) :
				if 0 < distance[i] and distance[i] < min_distance :
					vcur = i
					min_distance = distance[i]

			ret.append((src, vcur, min_distance))
			vnear = vcur

			for i, weight in self.connection[vnear] :
				if(distance[vnear] + weight < distance[i]) :
					distance[i] = distance[vnear] + weight
					nearest[i] = vnear

			distance[vnear] = -1

		return ret



def generate_matrix(n) :
	ret = [[INFINITY for _ in range(n)] for _ in range(n)]

	for i in range(n) :
		for j in range(i) : 
			tmp = random.randrange(1,100)
			if tmp % 7 == 0 :
				tmp = INFINITY
			ret[i][j] = tmp
			ret[j][i] = tmp

	return ret

if __name__ == "__main__" :
	random.seed(43)

	for _ in range(TEST_CASES) :
		graph1 = MatrixGraph(generate_matrix(5))
		print(graph1)
		graph2 =  LinkedListGraph(generate_matrix(5))
		print(graph2)

		print(graph1.find_shortest_path_from(0))
		print(graph2.find_shortest_path_from(0))
		print("\n\n")



