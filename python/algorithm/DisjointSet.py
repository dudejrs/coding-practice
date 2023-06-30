

class DisjointSet :

	def __init__ (self, n) :

		self.__tmp = []
		for i in range(n) :
			self.__tmp.append({i})

		return

	def find(self, a) :
		for s in self.__tmp :
			if a in s :
				return s

		return None;

	def findIdx(self, a) :
		for i in range(len(self.__tmp)) :
			if a in (self.__tmp)[i] :
				return i
		return -1

	def merge(self, a, b) :

		sA = self.find(a)
		sB = self.find(b)

		iA = self.findIdx(a)
		iB = self.findIdx(b)

		(self.__tmp)[iB] |= sA

		del (self.__tmp)[iA]

		return



if __name__ == "__main__" :

	tmp = DisjointSet(10)
	tmp.merge(0,1)
	print(tmp.find(0))



