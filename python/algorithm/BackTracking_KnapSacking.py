import random

TEST_CASES = 10
N = 30
MAX_PROFIT = 100
MAX_WEIGHT = 30
MIN_WEIGHT = 1


max_profit = -1


def promising(cur, cur_profit, cur_weight, items, W):
    global max_profit
    if cur_weight >= W:
        return False

    i = cur
    weight = cur_weight
    bound_profit = cur_profit

    while i < len(items) and weight + items[i][1] < W:
        bound_profit += items[i][0]
        weight += items[i][1]
        i += 1

    if i < len(items):
        bound_profit += int((W - weight) * items[i][0] / items[i][1])

    return bound_profit > max_profit


def check_node(cur, cur_profit, cur_weight, items, W):
    global max_profit

    if cur == len(items):
        return

    if cur_weight < W and cur_profit > max_profit:
        max_profit = cur_profit

    if not promising(cur, cur_profit, cur_weight, items, W):
        return

    check_node(cur + 1, cur_profit, cur_weight, items, W)
    check_node(cur + 1, cur_profit + items[cur][0], cur_weight + items[cur][1], items, W)

    return


def solve(n, items, W):

    check_node(0, 0, 0, items, W)

    return max_profit


if __name__ == "__main__":
    random.seed(43)
    for _ in range(10):
        max_profit = -1
        n = random.randint(5, N)
        items = [
            (random.randint(0, MAX_PROFIT), random.randint(MIN_WEIGHT, MAX_WEIGHT))
            for _ in range(n)
        ]
        W = MAX_WEIGHT * 1.5

        print(solve(n, items, W))

        pass
