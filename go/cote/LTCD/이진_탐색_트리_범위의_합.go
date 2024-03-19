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

func initialize(depth int, left, right int, random *rand.Rand) *Node {
	if (left + 1 >= right){
		return nil
	}

	if depth >= MAX_DEPTH {
		return nil
	}

	if random.Float32() / float32(depth) < 1.0 / float32(MAX_DEPTH) {
		return nil
	}

	node := new(Node)

	node.Value = random.Intn(right - left) + left
	node.Left = initialize(depth + 1, left, node.Value - 1, random)
	node.Right = initialize(depth + 1, node.Value, right, random)

	return node
}

func dfs(node * Node, left, right int) int {
	if node == nil {
		return 0
	}

	if node.Value < left {
		return dfs(node.Right, left, right)
	}

	if node.Value >= right {
		return dfs(node.Left, left, right) 
	}

	return node.Value + dfs(node.Left, left, right)+ dfs(node.Right, left, right) 
}

func solve1(node *Node, left, right int) int {
	return dfs(node, left, right)
}

func solve2(node *Node, left, right int) int {

	queue := list.New()
	queue.PushBack(node)

	acc :=0
	for {
		if queue.Len() == 0 {
			break
		}

		cur := queue.Front().Value.(*Node)
		queue.Remove(queue.Front())

		if cur == nil {
			continue
		}

		if cur.Value > left {
			queue.PushBack(cur.Left)
		}

		if cur.Value < right {
			queue.PushBack(cur.Right)
		}

		if left <= cur.Value && cur.Value < right {
			acc += cur.Value
		}

	}

	return acc
}

func main() {
	random := rand.New(rand.NewSource(43))
	for it := 0; it < TEST_CASE; it++ {
		node := initialize(0, 0, MAX_VALUE, random)
		right := random.Intn(MAX_VALUE - 1) + 1
		left := random.Intn(right)
		fmt.Println(solve1(node, left, right), solve2(node, left, right))
	}
}