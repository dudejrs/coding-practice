package main

import (
	"container/heap"
	"fmt"
	"math/rand"
)

const (
	TEST_CASES = 10
	N          = 10000
	MAX_VALUE  = 10000
)

type Heap struct {
	Data     []int
	LessFunc func(i, j int) bool
}

func (h Heap) Len() int {
	return len(h.Data)
}

func (h Heap) Swap(i, j int) {
	h.Data[i], h.Data[j] = h.Data[j], h.Data[i]
}

func (h Heap) Less(i, j int) bool {
	return h.LessFunc(h.Data[i], h.Data[j])
}

func (h *Heap) Push(x any) {
	h.Data = append(h.Data, x.(int))
}

func (h *Heap) Pop() any {
	old := h.Data
	n := len(old)
	x := old[n-1]
	h.Data = old[0 : n-1]
	return x
}

func minmax(x, y int) (min, max int) {
	if x > y {
		min, max = y, x
		return
	}
	min, max = x, y
	return
}

func solve(nums []int) []int {
	ret := make([]int, 0)

	minheap := &Heap{[]int{}, func(i, j int) bool { return i < j }}
	maxheap := &Heap{[]int{}, func(i, j int) bool { return i > j }}

	/*
		1. minHeap의 크기는 maxHeap의 크기와 같거나 크다
		2. maxHeap의 top <= minHeap의 top
	*/

	for _, v := range nums {
		if minheap.Len() == maxheap.Len() {
			heap.Push(minheap, v)
		} else {
			heap.Push(maxheap, v)
		}

		if minheap.Len() != 0 && maxheap.Len() != 0 {
			x := heap.Pop(minheap)
			y := heap.Pop(maxheap)

			min, max := minmax(x.(int), y.(int))
			heap.Push(maxheap, min)
			heap.Push(minheap, max)
		}

		x := heap.Pop(minheap)
		ret = append(ret, x.(int))
		heap.Push(minheap, x)
	}

	return ret
}

func main() {
	random := rand.New(rand.NewSource(43))

	for it := 0; it < TEST_CASES; it++ {
		n := random.Intn(N-3) + 3
		nums := make([]int, n)

		for i, _ := range nums {
			nums[i] = random.Intn(MAX_VALUE)
		}

		fmt.Println(solve(nums))
	}
}
