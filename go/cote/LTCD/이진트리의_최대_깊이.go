package LTCD

import (
	"fmt"
	"math/rand"
	"container/list"
)

// const (
// 	TEST_CASE = 10
// 	MAX_VALUE = 100
// 	MAX_DEPTH = 20
// )

type 이진트리의_최대_깊이 struct {
	TEST_CASE int 
	MAX_VALUE int 
	MAX_DEPTH int
}

type Node3 struct {
	Value int
	Left *Node3
	Right *Node3
}

func (problem 이진트리의_최대_깊이) max(x, y int) int {
	if x >= y {
		return x
	}
	return y
}

func (problem 이진트리의_최대_깊이) initialize(depth int, random *rand.Rand) *Node3 {

	if depth >= problem.MAX_DEPTH {
		return nil
	}

	if depth > 0 && random.Float32() / float32(depth) < 1.0 / float32(problem.MAX_DEPTH) {
		return nil
	}

	left := problem.initialize(depth + 1, random)
	right := problem.initialize(depth + 1, random)


	return &Node3{random.Intn(problem.MAX_VALUE), left, right}
}

func (problem 이진트리의_최대_깊이) solve(node *Node3) int {
	depth := 0
	queue := list.New()
	queue.PushBack(node)

	for {
		if queue.Len() == 0 {
			break
		}
		depth ++ 

		for i :=0; i < queue.Len(); i++ {
			cur := queue.Front().Value.(*Node3)

			if cur.Left != nil {
				queue.PushBack(cur.Left)
			}

			if cur.Right != nil {
				queue.PushBack(cur.Right)
			}

			queue.Remove(queue.Front())
		}
	}


	return depth
}

func (problem 이진트리의_최대_깊이) main() {
	random := rand.New(rand.NewSource(43))

	for it := 0; it < problem.TEST_CASE; it++ {
		node := problem.initialize(0, random)
		fmt.Println(problem.solve(node))
	}
}