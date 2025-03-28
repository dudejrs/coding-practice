class Node:

    def __init__(self, value, parent=None, left=None, right=None):

        self.value = value
        self.parent = parent
        self.left = left
        self.right = right

    def __iter__(self):
        yield self.value
        if self.left:
            for item in self.left:
                yield item
        if self.right:
            for item in self.right:
                yield item
        return


class BinarySearchTree:

    def __init__(self, root=None):
        self.root = root

    def __iter__(self):
        for children in self.root:
            yield children

    def _find_lmc(self, cur):
        while cur.left:
            cur = cur.left
        return cur

    def _insert(self, cur, newer):
        if cur.value > newer.value:
            if not cur.left:
                cur.left = newer
                newer.parent = cur
            else:
                self._insert(cur.left, newer)
        else:
            if not cur.right:
                cur.right = newer
                newer.parent = cur
            else:
                self._insert(cur.right, newer)

        return

    def insert(self, newer):
        self._insert(self.root, newer)
        return

    def _search(self, cur, value):
        if value < cur.value:
            return self._search(cur.left, value)
        if value > cur.value:
            return self._search(cur.right, value)

        return cur

    def search(self, value):
        return self._search(self.root, value)

    def _remove(self, current, value):

        if not current:
            return

        target = self._search(current, value)
        if not target:
            return
        if target.left and target.right:
            n = self._find_lmc(target.right)
            target.value = n.value
            self._remove(target.right, n.value)
        elif target.left or target.right:
            n = target.left if target.left else target.right
            if target == target.parent.left:
                target.parent.left = n
                n.parent = target.parent.left
            else:
                target.parent.right = n
                n.parent = target.parent.right
        else:
            if target == target.parent.left:
                target.parent.left = None
            else:
                target.parent.right = None

    def remove(self, value):
        self._remove(self.root, value)


class BinarySearchTreeBuilder:

    def __init__(self, root=None):
        self.tree = BinarySearchTree(root)

    def setRoot(self, value):
        if self.tree.root:
            self.tree.root.value = value
        else:
            self.tree.root = Node(value)

        return self

    def insert(self, value):
        if not self.tree.root:
            self.setRoot(value)
        else:
            self.tree.insert(Node(value))
        return self

    def remove(self, value):
        self.tree.remove(value)
        return self

    def build(self):
        tree = self.tree
        self.tree = BinarySearchTree()
        return tree


if __name__ == "__main__":

    builder = BinarySearchTreeBuilder()
    tree = (
        builder.setRoot(0)
        .insert(1)
        .insert(2)
        .insert(3)
        .insert(4)
        .insert(5)
        .remove(2)
        .insert(2)
        .remove(4)
        .insert(4)
        .build()
    )

    for node in tree:
        print(node)
