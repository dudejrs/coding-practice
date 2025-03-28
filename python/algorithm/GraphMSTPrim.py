import random

INFINTIY = 987654321


class Graph:
    def __init__(self):
        return

    def __repr__(self):
        return

    def find_mst(self):
        return


class MatrixGraph(Graph):
    def __init__(self, w):
        super().__init__()
        self.n = len(w)
        self.w = [[w[i][j] for j in range(len(w))] for i in range(len(w))]

        return

    def __repr__(self):

        ret = "["
        for i in range(self.n):
            if i != 0:
                ret += " "
            ret += "["
            for j in range(self.n):
                if self.w[i][j] != INFINTIY:
                    ret += '{:>4d}'.format(self.w[i][j])
                else:
                    ret += '{:>4s}'.format("_")
            ret += "]"
            if i != self.n - 1:
                ret += "\n"
        ret += "]"

        return ret

    def find_mst(self):
        ret = []
        vcur = 0
        distance = [self.w[i][vcur] for i in range(self.n)]
        nearest = [vcur for i in range(self.n)]
        distance[vcur] = -1

        for i in range(self.n - 1):
            min_distance = INFINTIY
            vnear = 0

            for j in range(self.n):
                if 0 < distance[j] and distance[j] < min_distance:
                    min_distance = distance[j]
                    vnear = j

            distance[vnear] = -1
            ret.append((vcur, vnear))
            vcur = vnear

            for j in range(self.n):
                if self.w[vcur][j] < distance[j]:
                    distance[j] = self.w[vcur][j]
                    nearest[j] = vcur

        return ret


class LinkedListGraph(Graph):

    def __init__(self, w):
        super().__init__()
        self.connection = [[] for _ in range(len(w))]
        self.n = len(w)

        for i in range(self.n):
            for j, weight in zip(range(self.n), w[i]):
                if weight != INFINTIY and i != j:
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

    def find_mst(self):
        ret = []
        vcur = 0
        distance = [INFINTIY for i in range(self.n)]
        nearest = [vcur for i in range(self.n)]
        vnear = [vcur for i in range(self.n)]
        for j, weight in self.connection[vcur]:
            distance[j] = weight
        distance[vcur] = -1

        for k in range(self.n - 1):
            vnear = 0
            min_distance = INFINTIY
            for i in range(self.n):
                if (0 < distance[i]) and (distance[i] < min_distance):
                    vnear = i
                    min_distance = distance[i]

            distance[vnear] = -1
            ret.append((vcur, vnear))
            vcur = vnear

            for i, weight in self.connection[vcur]:
                if weight < distance[i]:
                    distance[i] = weight
                    nearest[i] = vcur

        return ret


def generate_matrix(n):
    ret = [[INFINTIY for _ in range(n)] for _ in range(n)]

    for i in range(n):
        ret[i][i] = INFINTIY
        for j in range(i):
            tmp = random.randrange(1, 100)
            if tmp % 7 == 0 or i == j:
                tmp = INFINTIY
            ret[i][j] = tmp
            ret[j][i] = tmp

    return ret


if __name__ == "__main__":
    random.seed(43)

    graph1 = MatrixGraph(generate_matrix(5))
    print(graph1)
    print(graph1.find_mst())
    graph2 = LinkedListGraph(generate_matrix(5))
    print(graph2)
    print(graph2.find_mst())

    pass
