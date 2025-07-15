package LTCD

import (
	"fmt"
	"math/rand"
)

// const (
// 	TEST_CASE = 10
// 	MAX_VALUE = 100
// 	N = 10
// 	K = 5
// )

type 조합 struct {
	TEST_CASE int
	MAX_VALUE int
	N int
	K int
}

func (problem 조합) dfs(nums []int, elements []int, start int, k int, ret *[][]int) {
	if k == 0 {
		*ret = append(*ret, elements)
		return
	}
	for i, v := range nums {
		if i < start {
			continue
		}
		temp := append(elements, v)
		problem.dfs(nums, temp, i + 1, k - 1, ret)
	}
}

func (problem 조합) solve(nums []int, k int) [][]int {
	ret := make([][]int, 0)
	elements := make([]int, 0)
	problem.dfs(nums, elements, 0, k, &ret)

	return ret
}

func (problem 조합) main() {
	random := rand.New(rand.NewSource(43))

	for it := 0; it < problem.TEST_CASE; it++ {
		n := random.Intn(problem.N - 2) + 2
		k := random.Intn(n - 1) + 1
		nums := make([]int, n)
		for i, v := range random.Perm(problem.MAX_VALUE) {
			if i >= n {
				break
			}
			nums[i] = v 
		}
		fmt.Println(problem.solve(nums, k))
	}
}