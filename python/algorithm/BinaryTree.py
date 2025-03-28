class Node:
    def __init__(self, value, parent=None, left=None, right=None):
        self.value = value
        self.parent = parent
        self.left = left
        self.right = right

    def __iter__(self):
        yield self.value
        if self.left:
            for i in self.left:
                yield i
        if self.right:
            for i in self.right:
                yield i


class BinaryTree:
    def __init__(self, root=None):
        self.root = root

    def __iter__(self):
        for children in self.root:
            yield children


class BinaryTreeBuilder:

    def __init__(self, root=None):
        self.tree = BinaryTree(root)
        self.last = root

    def _lmc(self, node):
        cur = node
        while cur.left:
            cur = cur.left
        return cur

    def _depth(self, node):
        ret = 0
        if node.left:
            ret = max(ret, self._depth(node.left))
        if node.right:
            ret = max(ret, self._depth(node.right))
        return ret

    def insert(self, val):

        cur = self.last
        parent = cur.parent
        newnode = Node(val)

        if cur == self.tree.root:
            self.set_leftchild(cur, newnode)
        elif cur == parent.left:
            self.set_rightchild(parent, newnode)
        else:
            cur = parent
            while True:
                if self._depth(cur.left) == self._depth(cur.right):
                    break
                cur = parent.parent

            cur = self._lmc(cur)
            self.set_leftchild(cur, newnode)

        self.last = newnode

        return self

    def set_root(self, value):
        newroot = Node(value)
        self.tree.root = newroot
        self.last = newroot
        return self

    def set_leftchild(self, parent, leftchild):
        parent.left = leftchild
        leftchild.parent = parent
        return self

    def set_rightchild(self, parent, rightchild):
        parent.right = rightchild
        rightchild.parent = parent
        return self

    def build(
        self,
    ):
        return self.tree


if __name__ == "__main__":

    tree = BinaryTreeBuilder().set_root(1).insert(2).insert(3).insert(4).insert(5).build()
    for node in tree:
        print(node)
    pass
