package LTCD

type 페어의_노드_스왑 struct {
}

type Node5 struct {
	next  *Node5
	value int
}

func (problem 페어의_노드_스왑) makeLinkedList(ints []int) *Node5 {
	node := new(Node5)
	cur := node

	for _, val := range ints {
		cur.next = &Node5{nil, val}
		cur = cur.next
	}

	return node.next
}

func (problem 페어의_노드_스왑) toInts(root *Node5) []int {
	result := make([]int, 0)
	cur := root

	for {
		if cur == nil {
			break
		}

		result = append(result, cur.value)

		cur = cur.next
	}

	return result
}

func (problem 페어의_노드_스왑) solve(root *Node5) *Node5 {
	newRoot := &Node5{next: root}
	prev := newRoot

	for {
		if prev.next == nil || prev.next.next == nil {
			break
		}

		a := prev.next
		b := a.next
		c := b.next

		prev.next = b
		a.next = c
		b.next = a

		prev = prev.next.next
	}

	return newRoot.next
}

func (problem 페어의_노드_스왑) solve2(cur *Node5) *Node5 {
	if cur == nil || cur.next == nil {
		return cur
	}

	node := cur.next
	cur.next = problem.solve2(node.next)
	node.next = cur

	return node
}
