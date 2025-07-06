from typing import *
import random


TEST_CASES = 10
MAX_NODE = 5


class Node:
    def __init__(self, value, next=None):
        self.value = value
        self.next = next

    def __repr__(self):
        ret = [self.value]
        cur = self.next

        while cur:
            ret.insert(0, cur.value)
            cur = cur.next

        return str(ret)


def create_list() -> Node:
    node = Node(random.randrange(1, 9))

    for _ in range(n):
        node = Node(random.randrange(9), node)

    return node


def copy_node(node: Node) -> Node:
    head = Node(node.value)
    prev = head
    node = node.next

    while node:
        prev.next = Node(node.value)
        prev = prev.next
        node = node.next

    return head


def reverse_list(node: Node) -> Node:
    cur, prev = node, None

    while cur:
        next, cur.next = cur.next, prev
        prev, cur = cur, next

    return prev


def to_list(node: Node) -> List[str]:
    ret = []
    while node:
        ret.append(str(node.value))
        node = node.next
    return ret


def to_linked_list(x: str) -> Node:
    prev = None

    for num in x:
        node = Node(int(num))
        node.next = prev
        prev = node

    return node


def solve1(l1: Node, l2: Node) -> Node:

    a = to_list(reverse_list(copy_node(l1)))
    b = to_list(reverse_list(copy_node(l2)))

    result = int("".join(a)) + int("".join(b))

    return to_linked_list(str(result))


def solve2(l1: Node, l2: Node) -> Node:

    l1 = copy_node(l1)
    l2 = copy_node(l2)
    root = head = Node(0)
    carry = 0

    while l1 or l2 or carry:
        sum = 0
        if l1:
            sum += l1.value
            l1 = l1.next

        if l2:
            sum += l2.value
            l2 = l2.next

        carry, val = divmod(sum + carry, 10)
        head.next = Node(val)
        head = head.next

    return root.next


if __name__ == "__main__":
    random.seed(43)

    for _ in range(TEST_CASES):
        n = random.randrange(1, MAX_NODE)
        l1 = create_list()
        l2 = create_list()

        print(l1, l2, solve1(copy_node(l1), copy_node(l2)))
        print(l1, l2, solve2(copy_node(l1), copy_node(l2)))
