package main

import (
	"fmt"
	"math/rand"
	"sort"
	"container/list"
)

const (
	TEST_CASE = 10
	N = 10000
	MAX_VALUE = 100
)

type Node struct {
	Value int
	Left *Node
	Right *Node
}

func (node *Node) String() string {
	if node == nil {
		return "nil"
	}

	queue := list.New()
	queue.PushBack(node)
	ret := make([]int , 0)

	for {
		if queue.Len() == 0 {
			break
		}

		cur := queue.Front().Value.(*Node)
		queue.Remove(queue.Front())

		if cur != nil {
			ret = append(ret, cur.Value)
			queue.PushBack(cur.Left)
			queue.PushBack(cur.Right)
		}
	}

	return fmt.Sprint(ret)
}

func solve(nums []int) *Node {
	if len(nums) == 0 {
		return nil
	}	
	mid := len(nums) / 2
	node := new(Node)
	node.Value = nums[mid]
	node.Left, node.Right = solve(nums[:mid]), solve(nums[mid + 1:])

	return node
}

func main() {
	random := rand.New(rand.NewSource(43))

	for it := 0; it < TEST_CASE; it++ {
		n := random.Intn(N - 1) + 1
		
		nums := make([]int, n)
		for i, _ := range nums {
			nums[i] = random.Intn(MAX_VALUE)
		}
		sort.Ints(nums)
		fmt.Println(solve(nums))
	}
}