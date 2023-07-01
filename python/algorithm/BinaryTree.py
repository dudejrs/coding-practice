
class Node : 
	def __init__(self, value, parent=None, left=None, right=None):
		self.value = value
		self.parent = parent
		self.left = left
		self.right = right

	def __iter__(self) :
		yield self.value;
		if self.left :
			for i in self.left :
				yield i
		if self.right :
			for i in self.right :
				yield i


class BinaryTree :
	def __init__ (self, root=None) :
		self.root= root

	def __iter__(self) :
		for children in self.root : 
			yield children

class BinaryTreeBuilder :

	def __init__(self, root=None) :
		self.tree = BinaryTree(root);
		self.last = root

	def insert(self, val) :
		cur = self.last
		parent = cur.parent
		newnode = Node(val,cur)

		if not cur.left : 
			self.set_leftchild(cur, newnode)
		elif not cur.right : 
			self.set_rightchild(cur, newnode)
		elif (parent.left == cur) :
			self.set_leftchild(parent.right, newnode)
		else : 
			self.set_leftchild(parent.left.left, newnode)

		self.last = newnode
		return self

	def set_root(self, value) :
		newroot = Node(value)
		self.tree.root = newroot
		self.last = newroot
		return self

	def set_leftchild(self, parent, leftchild) :
		parent	.left = leftchild
		leftchild.parent = parent;
		return self

	def set_rightchild(self, parent, rightchild) :
		parent.right = rightchild
		rightchild.parent = parent;
		return self

	def build(self,) :
		return self.tree


if __name__ == "__main__" :


	tree = BinaryTreeBuilder()\
				.set_root(1)\
				.insert(2)\
				.insert(3)\
				.insert(4)\
				.insert(5)\
				.build()
	for node in tree :
		print(node)
	pass