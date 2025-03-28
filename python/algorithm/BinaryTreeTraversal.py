class Node:
    def __init__(self, value, parent=None, left=None, right=None):
        self.value = value
        self.parent = parent
        self.left = left
        self.right = right


class BinaryTree:
    def __init__(self, root=None):
        self.root = root


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

    def set_root(self, val):
        if not self.tree.root:
            newroot = Node(val)
            self.tree.root = newroot
            self.last = newroot
        else:
            self.tree.root.value = val
        return self

    def set_leftchild(self, parent, leftchild):
        parent.left = leftchild
        leftchild.parent = parent
        return self

    def set_rightchild(self, parent, rightchild):
        parent.right = rightchild
        rightchild.parent = parent
        return self

    def build(self):
        return self.tree


class BinaryTreeTraversal:

    def __init__(self, cur):
        self.cur = cur


class InorderBinaryTreeTraversal(BinaryTreeTraversal):
    def __iter__(self):
        yield self.cur.value
        if self.cur.left:
            for item in InorderBinaryTreeTraversal(self.cur.left):
                yield item
        if self.cur.right:
            for item in InorderBinaryTreeTraversal(self.cur.right):
                yield item


class PreorderBinaryTreeTraversal(BinaryTreeTraversal):

    def __iter__(self):
        if self.cur.left:
            for item in PreorderBinaryTreeTraversal(self.cur.left):
                yield item
        yield self.cur.value
        if self.cur.right:
            for item in PreorderBinaryTreeTraversal(self.cur.right):
                yield item


class PostorderBinaryTreeTraversal(BinaryTreeTraversal):

    def __iter__(self):
        if self.cur.left:
            for item in PostorderBinaryTreeTraversal(self.cur.left):
                yield item
        if self.cur.right:
            for item in PostorderBinaryTreeTraversal(self.cur.right):
                yield item
        yield self.cur.value


class LevelorderBinaryTreeTraversal(BinaryTreeTraversal):

    def __iter__(self):
        from queue import Queue

        q = Queue()
        q.put(self.cur)

        while not q.empty():
            cur = q.get()
            yield cur.value
            if cur.left:
                q.put(cur.left)
            if cur.right:
                q.put(cur.right)


if __name__ == "__main__":

    tree = BinaryTreeBuilder().set_root(1).insert(2).insert(3).insert(4).insert(5).build()

    for cur in InorderBinaryTreeTraversal(tree.root):
        print(cur, end=' ')
    print()

    for cur in PreorderBinaryTreeTraversal(tree.root):
        print(cur, end=' ')
    print()

    for cur in PostorderBinaryTreeTraversal(tree.root):
        print(cur, end=' ')
    print()
    for cur in LevelorderBinaryTreeTraversal(tree.root):
        print(cur, end=' ')
    print()
