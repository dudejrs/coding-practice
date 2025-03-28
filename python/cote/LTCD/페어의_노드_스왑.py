import random

TEST_CASES = 10
MAX_LENGTH = 10
MAX_VALUE = 1000


class Node:
    def __init__(self, value, next_=None):
        self.value = value
        self.next = next_

    def __iter__(self):
        cur = self
        while cur != None:
            yield cur.value
            cur = cur.next


def solve(node: Node):
    root = prev = Node(None)

    prev.next = node

    while node and node.next:

        b = node.next
        node.next = b.next
        b.next = node
        prev.next = b

        node = node.next
        prev = prev.next.next

    return root.next


def solve2(node: Node):

    if node and node.next:
        b = node.next

        node.next = solve2(b.next)
        b.next = node
        return b

    return node


if __name__ == "__main__":
    random.seed(43)

    for _ in range(TEST_CASES):

        n = random.randrange(1, MAX_LENGTH)

        prev = Node(random.randrange(MAX_VALUE))

        for _ in range(n - 1):
            prev = Node(random.randrange(MAX_VALUE), prev)

        print([*solve(prev)])
