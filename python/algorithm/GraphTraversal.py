import random

INFINTIY = 987654321


class Graph:
    def __init__(self):
        return

    def __repr__(self):
        return


class MatrixGraph(Graph):
    def __init__(self, w):
        self.n = len(w)
        self.w = [[INFINTIY for _ in range(self.n)] for _ in range(self.n)]

        for i in range(self.n):
            for j in range(self.n):
                if i != j:
                    self.w[i][j] = w[i][j]
        return

    def _dfs(self, visited, cur, fn):
        fn(cur)

        for i in range(self.n):
            if (not visited[i]) and (self.w[cur][i] != INFINTIY):
                visited[i] = True
                self._dfs(visited, i, fn)

        return

    def dfs(self, src, fn):
        visited = [False for _ in range(self.n)]

        visited[src] = True
        self._dfs(visited, src, fn)
        return

    def bfs(self, src, fn):
        from queue import Queue

        q = Queue()
        q.put(src)

        visited = [False for _ in range(self.n)]
        visited[src] = True

        while not q.empty():
            cur = q.get()
            fn(cur)

            for i in range(self.n):
                if (not visited[i]) and (self.w[cur][i] != INFINTIY):
                    visited[i] = True
                    q.put(i)

        return

    def __repr__(self):

        ret = "["
        for i in range(self.n):
            if i != 0:
                ret += " "
            ret += "["
            for j in range(self.n):
                if self.w[i][j] != INFINTIY:
                    ret += "{:>4d}".format(self.w[i][j])
                else:
                    ret += "{:>4s}".format("_")
            ret += "]"
            if i != self.n - 1:
                ret += "\n"
        ret += "]"

        return ret


class LinkedListGraph(Graph):
    def __init__(self, w):
        self.n = len(w)
        self.connection = [[] for _ in range(self.n)]

        for i in range(self.n):
            for j, weight in zip(range(self.n), w[i]):
                if weight != INFINTIY and i != j:
                    self.connection[i].append((j, weight))
        return

    def _dfs(self, visited, cur, fn):

        fn(cur)

        for i, weight in self.connection[cur]:
            if not visited[i]:
                visited[i] = True
                self._dfs(visited, i, fn)
        return

    def dfs(self, src, fn):
        visited = [False for _ in range(self.n)]
        visited[src] = True
        self._dfs(visited, src, fn)
        return

    def bfs(self, src, fn):
        from queue import Queue

        q = Queue()
        q.put(src)

        visited = [False for _ in range(self.n)]
        visited[src] = True

        while not q.empty():
            cur = q.get()
            fn(cur)

            for i, weight in self.connection[cur]:
                if not visited[i]:
                    visited[i] = True
                    q.put(i)
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


def generate_matrix(n):
    ret = [[INFINTIY for _ in range(n)] for _ in range(n)]

    for i in range(n):
        for j in range(n):
            tmp = random.randrange(1, 100)
            if tmp % 7 == 0 or i == j:
                tmp = INFINTIY
            ret[i][j] = tmp

    return ret


if __name__ == "__main__":

    random.seed(43)

    graph1 = MatrixGraph(generate_matrix(5))
    graph1.bfs(0, lambda i: print(str(i) + " ", end=""))
    print()
    graph1.dfs(0, lambda i: print(str(i) + " ", end=""))
    print()
    graph2 = LinkedListGraph(generate_matrix(5))
    graph2.bfs(0, lambda i: print(str(i) + " ", end=""))
    print()
    graph2.dfs(0, lambda i: print(str(i) + " ", end=""))
    print()
    print(graph2)
    pass
