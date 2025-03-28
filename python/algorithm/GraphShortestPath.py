import random

INFINITY = 987654321


class Graph:
    def __init__(self):
        pass

    def __repr__(self):
        pass

    def find_shortest_path(self, start, end, path=[]):
        pass

    def find_path(self, i, j, p):
        from collections import deque

        s = deque()
        s.append((i, j))
        ret = [
            i,
        ]
        while len(s) != 0:
            start, end = s.pop()
            mid = p[start][end]

            if mid == -1:
                ret.append(end)
                continue
            s.append((mid, end))
            s.append((start, mid))

        return ret


class MatrixGraph(Graph):
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
                    ret += '{:>4d}'.format(self.w[i][j])
                else:
                    ret += '{:>4s}'.format("_")
            ret += "]"
            if i != self.n - 1:
                ret += "\n"
        ret += "]"
        return ret

    def floyd(self, shortest_path, p):

        for k in range(self.n):
            for i in range(self.n):
                for j in range(self.n):
                    if shortest_path[i][k] == INFINITY or shortest_path[k][j] == INFINITY:
                        continue
                    if shortest_path[i][k] + shortest_path[k][j] < shortest_path[i][j]:
                        p[i][j] = k
                        shortest_path[i][j] = shortest_path[i][k] + shortest_path[k][j]

        return

    def find_shortest_path(self, start, end, path=[]):
        shortest_path = [[self.w[i][j] for j in range(self.n)] for i in range(self.n)]
        p = [[-1 for _ in range(self.n)] for _ in range(self.n)]

        w = self.floyd(shortest_path, p)
        ret = self.find_path(start, end, p)
        return ret


class LinkedListGraph(Graph):
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

    def floyd(self, shortest_path, path):

        for k in range(self.n):
            for i in range(self.n):
                for j in range(self.n):
                    if shortest_path[i][k] == INFINITY or shortest_path[k][j] == INFINITY:
                        continue
                    if shortest_path[i][k] + shortest_path[k][j] < shortest_path[i][j]:
                        path[i][j] = k
                        shortest_path[i][j] = shortest_path[i][k] + shortest_path[k][j]

    def find_shortest_path(self, start, end, path=[]):

        shortest_path = [[INFINITY for _ in range(self.n)] for _ in range(self.n)]
        for i in range(self.n):
            for j, weight in self.connection[i]:
                shortest_path[i][j] = weight
        path = [[-1 for _ in range(self.n)] for _ in range(self.n)]

        self.floyd(shortest_path, path)
        ret = self.find_path(start, end, path)

        return ret


def generate_matrix(n):
    ret = [[INFINITY for _ in range(n)] for _ in range(n)]
    for i in range(n):
        for j in range(n):
            tmp = random.randrange(1, 100)
            if tmp % 5 == 0 or i == j:
                tmp = INFINITY
            ret[i][j] = tmp
    return ret


if __name__ == "__main__":
    random.seed(43)

    graph1 = MatrixGraph(generate_matrix(10))
    print(graph1)
    for i in range(1, 10):
        print(graph1.find_shortest_path(0, i))

    graph2 = LinkedListGraph(generate_matrix(10))
    print(graph2)
    for i in range(1, 10):
        print(graph2.find_shortest_path(0, i))
