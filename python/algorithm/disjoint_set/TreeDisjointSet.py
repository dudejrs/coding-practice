class DisjointSet:
    def __init__(self, n: int):
        self.n = n
        self._parent = [i for i in range(n)]
        self._rank = [1 for _ in range(n)]

    def find(self, a: int) -> int:
        if self._parent[a] != a:
            self._parent[a] = self.find(self._parent[a])
        return self._parent[a]

    def merge(self, a: int, b: int):

        a, b = self.find(a), self.find(b)

        if a == b:
            return
        if self._rank[a] > self._rank[b]:
            a, b = b, a

        self._parent[a] = b
        if self._rank[a] == self._rank[b]:
            self._rank[b] += 1


if __name__ == "__main__":
    tmp = DisjointSet(10)
    tmp.merge(0, 1)
    print(tmp.find(0))
