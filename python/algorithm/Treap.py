import random


class Node:
    def __init__(self, value, left=None, right=None):
        self.value = value
        self._left = left
        self._right = right
        self.priority = random.randrange(0, 100)
        self.size = 0
        pass

    @property
    def left(self):
        return self._left

    @left.setter
    def left(self, left):
        self._left = left
        self.calcSize()

    @property
    def right(self):
        return self._right

    @right.setter
    def right(self, right):
        self._right = right
        self.calcSize()

    def calcSize(self):
        size = 1
        if self.left:
            size += self.left.size
        if self.right:
            size += self.right.size
        self.size = size

    @property
    def min(self):
        if not self._left:
            return value
        return self.left.min

    @property
    def max(self):
        if not self.right:
            return value
        return self.right.max

    def __str__(self):
        return f'Node({self.value})'


def split(root: Node, key):
    if not root:
        return None, None

    if root.value < key:
        left, right = split(root.right, key)
        root.right = left
        return root, right

    left, right = split(root.left, key)
    root.left = right
    return left, root


def insert(root: Node, node: Node):

    if not root:
        return node

    if root.priority < node.priority:
        first, second = split(root, node.value)
        node.left = first
        node.right = second
        return node

    if root.value > node.value:
        root.left = insert(root.left, node)
    else:
        root.right = insert(root.right, node)
    return root


def merge(a: Node, b: Node):
    assert a.max < b.min

    if not a:
        return b
    if not b:
        return a

    if a.priority < b.priority:
        b.left = merge(a, b.left)
        return b

    a.right = merge(a.right, b)
    return a


def erase(root: Node, key):
    if not root:
        return root

    if root.value == key:
        ret = merge(root.left, root.right)
        del root
        return ret

    if root.value < key:
        erase(root.left, key)
    else:
        erase(root.right, key)

    return root


def kth(root: Node, k: int):
    if not root:
        return None

    left_size = 0
    if root.left:
        left_size = root.left.size
    if k <= left_size:
        return kth(root.left, k)
    if k == left_size + 1:
        return root

    return kth(root.right, k - left_size - 1)


def count_less_than(root: Node, key):
    if not root:
        return 0
    if root.value >= key:
        return count_less_than(root.left, key)

    left_side = 0
    if root.left:
        left_side = root.left.size
    return left_side + 1 + count_less_than(root.right, key)


if __name__ == "__main__":
    random.seed(43)

    root = Node(0)
    for i in range(1, 11):
        root = insert(root, Node(i))

    for i in range(1, 12):
        print(kth(root, i))

    print(count_less_than(root, 10))

    pass
