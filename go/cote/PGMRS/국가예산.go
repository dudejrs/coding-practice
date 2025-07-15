package main

import (
	"fmt"
	"math/rand"
)

const (
	TEST_CASE  = 10
	MAX_BUDGET = 100
	N          = 10
)

func check(budgets []int, mid float64, m int) bool {
	sum := 0.

	for _, v := range budgets {
		if float64(v) < mid {
			sum += float64(v)
		} else {
			sum += mid
		}
	}

	return sum <= float64(m)
}

func solve(budgets []int, m int) float64 {
	lo, hi := 0., float64(m)

	for it := 0; it < 100; it++ {

		mid := float64(lo+hi) / 2.0

		if check(budgets, mid, m) {
			lo = mid
		} else {
			hi = mid
		}
	}

	return lo
}

func main() {
	random := rand.New(rand.NewSource(43))
	for it := 0; it < TEST_CASE; it++ {
		budgets := make([]int, N)

		for i, _ := range budgets {
			budgets[i] = random.Intn(MAX_BUDGET)
		}

		m := random.Intn(MAX_BUDGET*N/3) + MAX_BUDGET*N/3
		fmt.Printf("%.3f\n", solve(budgets, m))
	}
}
