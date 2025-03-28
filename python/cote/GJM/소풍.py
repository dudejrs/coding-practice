def get_friendship(s, n, m):
    areFriend = [[False for _ in range(n)] for _ in range(n)]

    for i in range(m):
        a, b = int(s[2 * i]), int(s[2 * i + 1])
        areFriend[a][b] = True
        areFriend[b][a] = True

    return areFriend


def search(areFriend, checked):

    target = -1
    for i in range(len(checked)):
        if not checked[i]:
            target = i
            break

    if target == -1:
        return 1

    ret = 0
    i = target

    for j in range(len(areFriend)):
        if not checked[j] and areFriend[i][j]:
            checked[j], checked[i] = True, True
            ret += search(areFriend, checked)
            checked[j], checked[i] = False, False

    return ret


def solve(areFriend, n):
    checked = [False for _ in range(n)]
    return search(areFriend, checked)


if __name__ == "__main__":
    with open('data/소풍.txt') as fd:

        TEST_CASES = int(fd.readline())
        while TEST_CASES > 0:
            n, m = map(int, fd.readline().split(" "))
            areFriend = get_friendship(fd.readline().split(" "), n, m)
            print(solve(areFriend, n))
            TEST_CASES -= 1
