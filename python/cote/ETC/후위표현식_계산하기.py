import sys


def solve(expression: str) -> int:
    tokens = expression.split(" ")
    stack = []

    for token in tokens:
        if token in ["+", "-", "*", "/"]:
            if stack and stack[-2]:
                rhs, lhs = stack.pop(), stack.pop()

                if token == "+":
                    stack.append(lhs + rhs)
                    continue
                elif token == "-":
                    stack.append(lhs - rhs)
                    continue
                elif token == "*":
                    stack.append(lhs * rhs)
                    continue
                elif token == "/":
                    stack.append(lhs / rhs)
                    continue

                return -sys.maxsize
        else:
            stack.append(int(token))

    return int(stack[-1])


if __name__ == "__main__":
    with open("data/후위표현식_계산하기.txt") as f:
        testcases = int(f.readline())

        for _ in range(testcases):
            expression = f.readline().strip()
            answer = int(f.readline())
            print(f'{answer} {solve(expression)}')
