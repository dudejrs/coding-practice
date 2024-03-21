package main

import (
	"fmt"
	"math/rand"
)

const (
	TEST_CASES = 10
	N = 100
	MAX_VALUE = 10
)

var cache [][]int

func initialize(n int, random *rand.Rand) [][]int {

	ret := make([][]int, n)

	for i := 0; i < n; i++ {
		ret[i] = make([]int, n)

		for j := 0; j < n; j++ {
			ret[i][j] = random.Intn(MAX_VALUE - 1) + 1
		}
	}

	return ret
}

func search(map_ [][]int, y, x int) bool {
	n := len(map_)
	
	if y >= n || x >= n {
		return false
	}

	if y == n - 1 && x == n - 1 {
		return true
	}

	ret := cache[y][x]

	if ret != -1 {
		return ret == 1
	}

	jump := map_[y][x]
	result := search(map_, y + jump, x) || search(map_, y, x + jump)

	if result {
		cache[y][x] = 1
	} else {
		cache[y][x] = 0
	}

	return result
}

func solve(map_ [][]int) bool {
	cache = make([][]int, len(map_))
	
	for i, _ := range map_ {
		cache[i] = make([]int, len(map_))
		for j, _ := range cache[i] {
			cache[i][j] = -1
		}
	}

	return search(map_, 0, 0)
}

func main() {
	random := rand.New(rand.NewSource(43))

	for it := 0; it < TEST_CASES; it++ {
		n := random.Intn(N - 1) + 1
		map_ := initialize(n, random)

		fmt.Println(solve(map_))
	}
}	