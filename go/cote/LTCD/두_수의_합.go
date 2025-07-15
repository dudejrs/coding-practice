package LTCD

import (
	"fmt"
	"math/rand"
)

// const (
// 	TEST_CASE = 10
// 	N = 1000
// 	TARGET = 1.5 * N
// )

type 두_수의_합 struct {
	TEST_CASE int
	N int
	TARGET int
}

func (problem 두_수의_합) initialize(random *rand.Rand) []int {
	n := random.Intn(problem.N - 1) + 1
	ret := make([]int, n)

	set := make(map[int]bool, 0)

	for i :=0; i < n; i++ {
		
		for {
			c := random.Intn(problem.N)
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

func (problem 두_수의_합) solve(nums []int, target int) [][]int {
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

func (problem 두_수의_합) main() {
	random := rand.New(rand.NewSource(43))

	for it := 0; it < problem.TEST_CASE; it++ {
		nums := problem.initialize(random)
		target := random.Intn(problem.TARGET - 1) + 1
		fmt.Println(problem.solve(nums, target))
	}
}