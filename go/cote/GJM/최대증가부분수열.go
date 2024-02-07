package main

import (
	"fmt"
	"math/rand"
)

const (
	TEST_CASES = 10
	N = 20
	MAX_VALUE = 100
)


var cache = make([]int, N+1)

func max(x,y int) int {
	if x < y {
		return y
	}
	return x 
} 

func search(cur int, l []int) int {

	var ret *int

	ret = &cache[cur+1]

	if *ret != -1 {
		return *ret
	}

	*ret = 0

	for i := cur+1; i < len(l); i++ {
		if cur == -1 || l[cur] < l[i] {
			*ret = max(*ret, 1 + search(i, l))
		}
	}

	return *ret
}

func solve(l []int) int {

	for i, _ := range cache {
		cache[i] = -1
	}

	return search(-1, l)
}

func main() {
	rand.Seed(43)
	for it := 0; it < TEST_CASES; it++ {
		n := rand.Intn(N-10)+10
		l := make([]int, n)

		for i := 0; i < n; i++ {
			l[i] = rand.Intn(MAX_VALUE)
		}
		fmt.Println(solve(l))
	}
}