import random

TEST_CASES = 10
N = 10
INF = 987654321


def initialize():
    random.seed(43)
    ret = []

    for i in range(0, N):
        row = []
        for j in range(0, N):
            tmp = random.randint(0, 100)
            if i == j or tmp % 37 < 1:
                tmp = INF
            row.append(tmp)
        ret.append(row)

    return ret


def calcualte(W, path):
    ret = 0

    for i in range(len(path) - 1):
        ret += W[path[i]][path[i + 1]]

    return ret


def tspTest(search):

    def tsp():
        W = initialize()
        visited = [False for _ in range(N)]
        path = [0]
        visited[0] = True
        best = search(W, path, visited)
        print(best)

    return tsp


# 1. Simple 완전 탐색
@tspTest
def search1(W, path, visited):
    best = INF

    def search(W, path, visited):
        nonlocal best

        if len(path) == N:
            best = min(best, calcualte(W, path) + W[path[-1]][path[0]])
            return

        cur = path[-1]

        for i in range(N):
            if visited[i]:
                continue
            path.append(i)
            visited[i] = True
            search(W, path, visited)
            visited[i] = False
            path.pop()
        return

    search(W, path, visited)
    return best


# 2. 최적해보다 나빠지면 그만 두기


@tspTest
def search2(W, path, visited):
    best = INF

    def search(W, path, visited):
        nonlocal best

        if best < calcualte(W, path):
            return

        if len(path) == N:
            best = min(best, calcualte(W, path) + W[path[-1]][path[0]])
            return

        cur = path[-1]

        for i in range(N):
            if visited[i]:
                continue
            path.append(i)
            visited[i] = True
            search(W, path, visited)
            visited[i] = False
            path.pop()

        return

    search(W, path, visited)
    return best


# 3. 휴리스틱을 이용 : "가장 짧은 간선의 길이 만을 모으면 실제 최단 경로 이하의 값이 될수 밖에 없음" 을 이용


@tspTest
def search3(W, path, visited):
    best = INF
    min_edges = [min(*W[j]) for j in range(N)]

    def simple_hueristic(W, visited):
        nonlocal min_edges
        ret = min_edges[0]

        for i in range(N):
            if visited[i]:
                continue
            ret += min_edges[i]

        return ret

    def search(W, path, visited):
        nonlocal best

        if best <= calcualte(W, path) + simple_hueristic(W, visited):
            return

        if len(path) == N:
            best = min(best, calcualte(W, path) + W[path[-1]][0])
            return

        cur = path[-1]

        for i in range(N):
            if visited[i]:
                continue
            path.append(i)
            visited[i] = True
            search(W, path, visited)
            visited[i] = False
            path.pop()

        return

    search(W, path, visited)

    return best


# 4. 가까운 도시부터 방문하기


@tspTest
def search4(W, path, visited):
    best = INF

    def near(i, W):
        ret = [*enumerate(W[i])]

        return sorted(filter(lambda a: a[1] != INF, ret), key=lambda a: a[1])

    nearest = [near(i, W) for i in range(N)]

    def search(W, path, visited):
        nonlocal best
        nonlocal nearest

        if best <= calcualte(W, path):
            return

        if len(path) == N:
            best = min(best, calcualte(W, path) + W[path[-1]][0])
            return

        cur = path[-1]

        for i, _ in nearest[cur]:
            if visited[i]:
                continue
            path.append(i)
            visited[i] = True
            search(W, path, visited)
            visited[i] = False
            path.pop()

        return

    search(W, path, visited)

    return best


# 5. 지나온 경로를 이용한 가지치기 : " 지금까지 만든 경로가 최적해가 아니면, 남은 경로를 만들 필요가 없다"
#
# 	두개의 인접한 도시를 골라서 이 둘의 순서를 바꿔 본 뒤, 경로가 더 짧아지면 탐색을 중단
# 	(..., p,a,b,q, ..., cur)
# 	(..., p,b,a,q, ..., cur)


@tspTest
def search5(W, path, visited):
    return INF


# 6. MST 휴리스틱을 이용한 가지치기 : 현재 선택된 노드에서, 최소 스패닝트리를 만든것 보다 작으면 가지치기
@tspTest
def search6(W, path, visited):
    return INF


# 7. 남은 조각의 수가 k이하일 때만 메모이제이션
@tspTest
def search7(W, path, visited):
    return INF


if __name__ == "__main__":
    search1()
    search2()
    search3()
    search4()
    search5()
    search6()
    search7()
