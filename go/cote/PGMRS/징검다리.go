package main

import (
	"fmt"
	"math/rand"
	"slices"
)

const (
	TEST_CASE       = 10
	MAX_DISTANCE    = 1000000000
	MAX_ROCK_NUMBER = 50000
)

func isValid(rocks []int, n, distance int) bool {

	last, removed := 0, 0

	for _, rock := range rocks {
		if rock-last < distance {
			removed++
			continue
		}
		last = rock
	}

	return removed <= n
}

func solve(rocks []int, n int) int {

	lo, hi := 0, MAX_DISTANCE

	for {
		if lo+1 == hi {
			break
		}

		mid := int((lo + hi) / 2)

		if isValid(rocks, n, mid) {
			lo = mid
		} else {
			hi = mid
		}
	}

	return lo
}

func main() {

	for it := 0; it < TEST_CASE; it++ {
		r := rand.Intn(MAX_ROCK_NUMBER-1) + 1
		n := rand.Intn(r-1) + 1

		rocks := make([]int, r)

		for i := range rocks {
			rocks[i] = rand.Intn(MAX_DISTANCE)
		}

		slices.Sort(rocks)

		fmt.Println(solve(rocks, n))
	}
}
