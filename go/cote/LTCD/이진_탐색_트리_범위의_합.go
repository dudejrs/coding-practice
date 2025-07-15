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

type 이진_탐색_트리_범위의_합 struct {
	TEST_CASE int
	MAX_VALUE int
	MAX_DEPTH int
}

type Node2 struct {
	Value int
	Left *Node2
	Right *Node2
}

func (problem 이진_탐색_트리_범위의_합) initialize(depth int, left, right int, random *rand.Rand) *Node2 {
	if (left + 1 >= right){
		return nil
	}

	if depth >= problem.MAX_DEPTH {
		return nil
	}

	if random.Float32() / float32(depth) < 1.0 / float32(problem.MAX_DEPTH) {
		return nil
	}

	node := new(Node2)

	node.Value = random.Intn(right - left) + left
	node.Left = problem.initialize(depth + 1, left, node.Value - 1, random)
	node.Right = problem.initialize(depth + 1, node.Value, right, random)

	return node
}

func (problem 이진_탐색_트리_범위의_합) dfs(node * Node2, left, right int) int {
	if node == nil {
		return 0
	}

	if node.Value < left {
		return problem.dfs(node.Right, left, right)
	}

	if node.Value >= right {
		return problem.dfs(node.Left, left, right) 
	}

	return node.Value + problem.dfs(node.Left, left, right) + problem.dfs(node.Right, left, right) 
}

func (problem 이진_탐색_트리_범위의_합) solve1(node *Node2, left, right int) int {
	return problem.dfs(node, left, right)
}

func (problem 이진_탐색_트리_범위의_합) solve2(node *Node2, left, right int) int {

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

func (problem 이진_탐색_트리_범위의_합) main() {
	random := rand.New(rand.NewSource(43))
	for it := 0; it < problem.TEST_CASE; it++ {
		node := problem.initialize(0, 0, problem.MAX_VALUE, random)
		right := random.Intn(problem.MAX_VALUE - 1) + 1
		left := random.Intn(right)
		fmt.Println(problem.solve1(node, left, right), problem.solve2(node, left, right))
	}
}