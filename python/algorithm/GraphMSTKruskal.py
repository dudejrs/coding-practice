import random

TEST_CASES = 10
INFINITY = 987654321


class Graph:
    def __init__(self):
        pass

    def __repr__(self):
        pass

    def find_mst(self):
        pass

    def get_edges(self):
        pass


class MatrixGraph:
    def __init__(self, w):
        self.n = len(w)
        self.w = [[w[i][j] for j in range(self.n)] for i in range(self.n)]
        return

    def __repr__(self):
        ret = "["
        for i in range(self.n):
            if i != 0:
                ret += " "
            ret += "["
            for j in range(self.n):
                if self.w[i][j] != INFINITY:
                    ret += "{:>4d}".format(self.w[i][j])
                else:
                    ret += "{:>4s}".format("_")
            ret += "]"
            if i != self.n - 1:
                ret += "\n"
        ret += "]"
        return ret

    def get_edges(self):
        edges = []
        for i in range(self.n):
            for j in range(self.n):
                edges.append(((i, j), w[i][j]))
        return edges

    def find_mst(self):

        edges = self.get_edges()
        edges.sort(key=lambda e: e[1])

        disjoint_set = DisjointSet(self.n)
        mst = []

        for (i, j), weight in edges:
            if len(disjoint_set) == 1:
                break
            if disjoint_set.equal(i, j):
                continue
            disjoint_set.merge(i, j)
            mst.append((i, j))
        return mst


class LinkedListGraph:
    def __init__(self, w):
        self.n = len(w)
        self.connection = [[] for _ in range(self.n)]
        for i in range(self.n):
            for j, weight in zip(range(self.n), w[i]):
                if weight != INFINITY and i != j:
                    self.connection[i].append((j, weight))
        return

    def __repr__(self):
        ret = "["
        for i in range(self.n):
            if i != 0:
                ret += " "
            ret += str(self.connection[i])
            if i != self.n - 1:
                ret += "\n"
        ret += "]"
        return ret

    def get_edges(self):
        edges = []
        for i in range(self.n):
            for j, weight in self.connection[i]:
                edges.append(((i, j), weight))
        return edges

    def find_mst(self):
        edges = self.get_edges()
        edges.sort(key=lambda e: e[1])
        mst = []
        disjoint_set = DisjointSet(self.n)

        for (i, j), weight in edges:
            if len(disjoint_set) == 1:
                break
            if disjoint_set.equal(i, j):
                continue
            disjoint_set.merge(i, j)
            mst.append((i, j))

        return mst


class DisjointSet:
    def __init__(self, n):
        self.__set = []
        for i in range(n):
            self.__set.append({i})
        return

    def findIdx(self, a):
        for i in range(len(self.__set)):
            if a in (self.__set)[i]:
                return i
        return -1

    def find(self, a):
        for s in self.__set:
            if a in s:
                return s
        return set()

    def equal(self, a, b):
        idxA = self.findIdx(a)
        idxB = self.findIdx(b)
        return idxA == idxB

    def merge(self, a, b):

        idxA = self.findIdx(a)
        idxB = self.findIdx(b)

        setA = self.find(a)
        setB = self.find(b)

        if idxA == idxB:
            return

        self.__set[idxA] |= setB
        del self.__set[idxB]

        return

    def __len__(self):
        return len(self.__set)


def generate_matrix(n):
    ret = [[INFINITY for _ in range(n)] for _ in range(n)]
    for i in range(n):
        for j in range(i, n):
            tmp = random.randint(1, 100)
            if tmp % 17 <= 1:
                continue
            ret[i][j] = tmp
            ret[j][i] = tmp

    return ret


if __name__ == "__main__":
    random.seed(43)

    for _ in range(TEST_CASES):

        w = generate_matrix(5)

        mg = MatrixGraph(w)
        lg = LinkedListGraph(w)

        print(mg.find_mst())
        print(lg.find_mst())
