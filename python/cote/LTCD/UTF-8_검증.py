def solve(data) -> bool:

    def check(size):
        for i in range(start + 1, start + size + 1):
            if i >= len(data) or (data[i] >> 6) != 0b10:
                return False
        return True

    start = 0

    while start < len(data):
        first = data[start]

        if (first >> 7) == 0:
            start += 1
        elif (first >> 5) == 0b110 and check(1):
            start += 2
        elif (first >> 4) == 0b1110 and check(2):
            start += 3
        elif (first >> 3) == 0b110 and check(3):
            start += 4

        else:
            return False
    return True


if __name__ == "__main__":
    with open("./data/UTF-8_검증.txt") as f:
        testcases = int(f.readline())
        for _ in range(testcases):
            data = list(map(int, f.readline().split(" ")))
            answer = bool(int(f.readline()))
            print(answer, solve(data))
