package main

import (
	"fmt"
	"math/rand"
	"container/list"
)

const (
	TEST_CASE = 10
	MAX_VALUE = 100
	MAX_DEPTH = 20
)

type Node struct {
	Value int
	Left *Node
	Right *Node
}

func max(x, y int) int {
	if x >= y {
		return x
	}
	return y
}

func initialize(depth int, random *rand.Rand) *Node {

	if depth >= MAX_DEPTH {
		return nil
	}

	if depth > 0 && random.Float32() / float32(depth) < 1.0 / float32(MAX_DEPTH) {
		return nil
	}

	left := initialize(depth + 1, random)
	right := initialize(depth + 1, random)


	return &Node{random.Intn(MAX_VALUE), left, right}
}

func solve(node *Node) int {
	depth := 0
	queue := list.New()
	queue.PushBack(node)

	for {
		if queue.Len() == 0 {
			break
		}
		depth ++ 

		for i :=0; i < queue.Len(); i++ {
			cur := queue.Front().Value.(*Node)

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

func main() {
	random := rand.New(rand.NewSource(43))

	for it := 0; it < TEST_CASE; it++ {
		node := initialize(0, random)
		fmt.Println(solve(node))
	}
}