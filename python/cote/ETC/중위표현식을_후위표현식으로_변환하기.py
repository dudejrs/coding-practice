def solve(expression: str) -> str:
    tokens = expression.split(" ")
    priority = {"+": 1, "-": 1, "*": 2, "/": 2, "(": 0}
    stack, ret = [], []

    for token in tokens:
        if token in ["+", "-", "*", "/"]:
            while stack and priority[token] < priority[stack[-1]]:
                ret.append(stack.pop())
            stack.append(token)
        elif token == "(":
            stack.append(token)
        elif token == ")":
            while stack and stack[-1] != "(":
                ret.append(stack.pop())
            if stack and stack[-1] == "(":
                stack.pop()
            else:
                return "bad expression"
        else:
            ret.append(token)

    while stack:
        ret.append(stack.pop())

    return " ".join(ret)


if __name__ == "__main__":

    with open("data/중위표현식을_후위표현식으로_변환하기.txt") as f:
        num = int(f.readline())

        for _ in range(num):
            expression = f.readline().strip()
            answer = f.readline().strip()
            print(f"{answer} : {solve(expression)}")
