package main

import (
	"fmt"
	"math/rand"
)

const (
	TEST_CASE = 10
	MAX_VALUE = 100
	N = 10
	K = 5
)

func dfs(nums []int, elements []int, start int, k int, ret *[][]int) {
	if k == 0 {
		*ret = append(*ret, elements)
		return
	}
	for i, v := range nums {
		if i < start {
			continue
		}
		temp := append(elements, v)
		dfs(nums, temp, i + 1, k - 1, ret)
	}
}

func solve(nums []int, k int) [][]int {
	ret := make([][]int, 0)
	elements := make([]int, 0)
	dfs(nums, elements, 0, k, &ret)

	return ret
}

func main() {
	random := rand.New(rand.NewSource(43))

	for it := 0; it < TEST_CASE; it++ {
		n := random.Intn(N - 2) + 2
		k := random.Intn(n - 1) + 1
		nums := make([]int, n)
		for i, v := range random.Perm(MAX_VALUE) {
			if i >= n {
				break
			}
			nums[i] = v 
		}
		fmt.Println(solve(nums, k))
	}
}