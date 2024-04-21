package main

import (
	"math/rand"
	"fmt"
	"container/heap"
)

const (
	TEST_CASES = 10
	K = 10
	MAX_VALUE = 10000
	STEP =100
)

type Node struct {
	Value int
	Next *Node
}

func (n Node) String() string {
	ret := make([]int, 0)
	cur := n

	for {
		if cur.Next == nil {
			break
		}
		ret = append(ret, cur.Value)

		cur = *cur.Next
	}

	return fmt.Sprint(ret)
}

type NodeHeap []*Node

func (h NodeHeap) Len() int {return len(h)}
func (h NodeHeap) Less(x, y int) bool {return h[x].Value < h[y].Value}
func (h NodeHeap) Swap(x, y int)  { 
	h[x], h[y] = h[y], h[x]
}

func (h *NodeHeap) Push(a any) {
	*h = append(*h, a.(*Node))
}

func (h *NodeHeap) Pop() any {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]

	return x
}

func initialize(random *rand.Rand) []*Node  {
	k := random.Intn(K - 2) + 2
	ret := make([]*Node, k)

	for i, _ := range ret {
		ret[i] = &Node{random.Intn(STEP), nil}
		cur := ret[i]
		
		for {
			tmp := cur.Value + random.Intn(STEP)

			if tmp > MAX_VALUE {
				break
			}
			cur.Next = &Node{tmp, nil}

			cur = cur.Next
		}
	}

	return ret
}

func solve(nodelists []*Node) *Node {
	h := &NodeHeap{}

	for _, node := range nodelists {
		heap.Push(h, node)
	}

	root := &Node{0, nil}
	cur := root

	for {
		if h.Len() == 0 {
			break
		}
		cur.Next = heap.Pop(h).(*Node)
		cur = cur.Next
		
		if cur.Next != nil {
			heap.Push(h, cur.Next)
		}
	}

	return root.Next
}

func main() {
	random := rand.New(rand.NewSource(43))
	for it := 0; it < TEST_CASES; it++ {
		nodelists := initialize(random)
		fmt.Println(nodelists)
		fmt.Println(solve(nodelists))
	}
}