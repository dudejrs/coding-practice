package main

import (
	"fmt"
	"math/rand"
)

const (
	TEST_CASE = 10
	N = 1000
	TARGET = 1.5 * N
)

func initialize(random *rand.Rand) []int {
	n := random.Intn(N - 1) + 1
	ret := make([]int, n)

	set := make(map[int]bool, 0)

	for i :=0; i < n; i++ {
		
		for {
			c := random.Intn(N)
			_, ok := set[c]
			if !ok {
				set[c] = true
				ret[i] = c
				break;
			}
		}
	}

	return ret 
}

func solve(nums []int, target int) [][]int {
	num_to_index := make(map[int]int)
	ret := make([][]int, 0)

	for i, n := range nums {
		num_to_index[n] = i
	}

	for i, num := range nums {
		v, ok := num_to_index[target - num]
		if ok && i != v {
			ret = append(ret, []int{i, v})
		}
	}

	return ret
}

func main() {
	random := rand.New(rand.NewSource(43))

	for it := 0; it < TEST_CASE; it++ {
		nums := initialize(random)
		target := random.Intn(TARGET - 1) + 1
		fmt.Println(solve(nums, target))
	}
}