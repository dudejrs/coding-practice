import random

TEST_CASES = 10
MAX_LENGTH = 1000
MAX_VALUE = 1000


class Node:

    def __init__(self, value, next=None):
        self.value = value
        self.next = next

    def __iter__(self):
        cur = self

        while cur != None:
            yield cur.value
            cur = cur.next


def solve(node: Node):

    prev = None

    while node:
        next, node.next = node.next, prev
        prev, node = node, next

    return prev


if __name__ == "__main__":
    random.seed(43)

    for _ in range(TEST_CASES):
        n = random.randrange(1, MAX_LENGTH)
        prev = Node(random.randrange(MAX_VALUE))
        for _ in range(n - 1):
            prev = Node(random.randrange(MAX_VALUE), prev)
        print([*solve(prev)])
