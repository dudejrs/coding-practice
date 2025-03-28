from typing import List


def solve(grid: List[List[str]]) -> int:

    def dfs(y: int, x: int):

        if y < 0 or y >= len(grid) or x < 0 or x >= len(grid[0]):
            return

        if grid[y][x] != '1':
            return

        grid[y][x] = '0'

        dfs(y - 1, x)
        dfs(y, x - 1)
        dfs(y, x + 1)
        dfs(y + 1, x)

        return

    count = 0
    for i in range(len(grid)):
        for j in range(len(grid[0])):
            if grid[i][j] == '1':
                dfs(i, j)
                count += 1

    return count


if __name__ == "__main__":

    f = open("data/섬의_개수.txt")
    testcases = int(f.readline())

    for _ in range(testcases):
        row, col = map(int, f.readline().strip().split(" "))
        grid = [[c for c in f.readline()] for _ in range(row)]
        answer = int(f.readline())

        print(answer, solve(grid))
