package LTCD

import (
	"container/heap"
	"fmt"
	"math/rand"
)

// const (
// 	TEST_CASES = 10
// 	K = 10
// 	MAX_VALUE = 10000
// 	STEP =100
// )

type k개의_정렬리스트_병합 struct {
	TEST_CASES int
	K          int
	MAX_VALUE  int
	STEP       int
}

type Node1 struct {
	Value int
	Next  *Node1
}

func (n Node1) String() string {
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

type NodeHeap1 []*Node1

func (h NodeHeap1) Len() int           { return len(h) }
func (h NodeHeap1) Less(x, y int) bool { return h[x].Value < h[y].Value }
func (h NodeHeap1) Swap(x, y int) {
	h[x], h[y] = h[y], h[x]
}

func (h *NodeHeap1) Push(a any) {
	*h = append(*h, a.(*Node1))
}

func (h *NodeHeap1) Pop() any {
	old := *h
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]

	return x
}

func (problem k개의_정렬리스트_병합) initialize(random *rand.Rand) []*Node1 {
	k := random.Intn(problem.K-2) + 2
	ret := make([]*Node1, k)

	for i, _ := range ret {
		ret[i] = &Node1{random.Intn(problem.STEP), nil}
		cur := ret[i]

		for {
			tmp := cur.Value + random.Intn(problem.STEP)

			if tmp > problem.MAX_VALUE {
				break
			}
			cur.Next = &Node1{tmp, nil}

			cur = cur.Next
		}
	}

	return ret
}

func (problem k개의_정렬리스트_병합) solve(nodelists []*Node1) *Node1 {
	h := &NodeHeap1{}

	for _, node := range nodelists {
		heap.Push(h, node)
	}

	root := &Node1{0, nil}
	cur := root

	for {
		if h.Len() == 0 {
			break
		}
		cur.Next = heap.Pop(h).(*Node1)
		cur = cur.Next

		if cur.Next != nil {
			heap.Push(h, cur.Next)
		}
	}

	return root.Next
}

func (problem k개의_정렬리스트_병합) main() {
	random := rand.New(rand.NewSource(43))
	for it := 0; it < problem.TEST_CASES; it++ {
		nodelists := problem.initialize(random)
		fmt.Println(nodelists)
		fmt.Println(problem.solve(nodelists))
	}
}
