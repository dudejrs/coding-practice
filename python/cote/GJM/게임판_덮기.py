convertType = [
    [[0, 0], [0, 1], [1, 0]],
    [[0, 0], [1, 0], [1, 1]],
    [[0, 0], [0, 1], [1, 1]],
    [[0, 0], [0, 1], [-1, 1]],
]


def process(board, H, W):

    ret = []

    for j in range(0, H):
        ret.append([])

        for c in board[j]:
            if c == "#":
                ret[j].append(1)
            else:
                ret[j].append(0)

    return ret


def set(board, x, y, points, H, W, delta):

    ret = True

    for dx, dy in points:
        nx = x + dx
        ny = y + dy

        if not (nx < 0 or nx >= W or ny < 0 or ny >= H):
            board[ny][nx] += delta
            if board[ny][nx] > 1:
                ret = False

    return ret


def solve(board, H, W):

    x = -1
    y = -1

    for r in range(len(board)):
        for c in range(len(board[r])):
            if board[r][c] == 0:
                x = c
                y = r
                break
        if y != -1:
            break

    if y == -1:
        return 1

    result = 0

    for points in convertType:
        if set(board, x, y, points, H, W, 1):
            result += solve(board, H, W)
        set(board, x, y, points, H, W, -1)

    return result


if __name__ == "__main__":
    with open("data/게임판_덮기.txt", "r") as f:

        test_cases = int(f.readline())

        for _ in range(0, test_cases):
            H, W = list(map(lambda i: int(i), f.readline().split(' ')))

            board = []
            for _ in range(0, H):
                board.append(f.readline().strip('\n'))

            board = process(board, H, W)

            print(solve(board, H, W))
