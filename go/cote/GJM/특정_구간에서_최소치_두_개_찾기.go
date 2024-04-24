package main

import (
	"fmt"
	"math"
	"math/rand"
	"sort"
)

const (
 	TEST_CASES = 10
 	N = 100
 	K = 1000
)

type Range struct{
	left int
	right int
}

type Entry struct{
	first int
	second int
}

func (e Entry) Merge(other Entry) Entry {
	values := []int{0, 0, 0, 0}
	values[0], values[1] = e.first, e.second
	values[2], values[3] = other.first, other.second

	sort.Ints(values)

	return Entry{values[0], values[1]}
}

type RMQ struct {
	n int
	rangeMin []Entry
}

func (rmq *RMQ) Init(array []int) {
	rmq.n = len(array)
	rmq.rangeMin = make([]Entry, 4 * len(array))
	rmq.init(array, 0, len(array), 0)
}

func (rmq RMQ) Query(left, right int) []int {
	result := rmq.query(left, right, 0, rmq.n, 0)
	return []int{result.first, result.second}
}


func (rmq *RMQ) init(array []int, left, right, cur int) Entry {
	if left + 1 == right  {
		rmq.rangeMin[cur] = Entry{array[left], math.MaxInt32}
		return rmq.rangeMin[cur]
	}

	mid := (left + right) / 2
	leftEntry := rmq.init(array, left, mid, 2 * cur + 1)
	rightEntry := rmq.init(array, mid, right, 2 * cur + 2)

	rmq.rangeMin[cur] = leftEntry.Merge(rightEntry)
	return rmq.rangeMin[cur]
}

func (rmq RMQ) query(left, right, curLeft, curRight, cur int) Entry {
	if right <= curLeft || curRight <= left {
		return Entry {math.MaxInt32, math.MaxInt32}
	}

	if left <= curLeft && curRight <= right {
		return rmq.rangeMin[cur]
	}

	mid := (curLeft + curRight) / 2

	leftEntry := rmq.query(left, right, curLeft, mid, 2 * cur + 1)
	rightEntry := rmq.query(left, right, mid, curRight, 2 * cur + 2)

	return leftEntry.Merge(rightEntry)
}

func solve(queries []Range, nums []int) [][]int {

	rmq := new(RMQ)	
	rmq.Init(nums)

	ret := make([][]int, len(queries)) 

	for i, query := range queries {
		ret[i] = rmq.Query(query.left, query.right)
	}

	return ret
}

func main() {
	random := rand.New(rand.NewSource(43))

	for it := 0; it < TEST_CASES; it++ {
		n := random.Intn(N - 3) + 3
		nums := make([]int, n)
		for i, _ := range nums {
			nums[i] = random.Intn(N * 5)
		}

		k := random.Intn(K - 1) + 1
		queries := make([]Range, k)

		for i, _ := range queries {
			right := random.Intn(n + 1 - 2) + 1 + 2
			left := random.Intn(right - 1)
			queries[i] = Range{left, right}
		}

		fmt.Println(solve(queries, nums))
	}
}