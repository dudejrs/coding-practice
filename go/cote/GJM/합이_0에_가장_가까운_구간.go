package main

import (
	"fmt"
	"math"
	"math/rand"
	"sort"
)

const (
	TEST_CASES = 10
	N          = 1000
	MAX_VAL    = 987654321
)

type Entry struct {
	Sum   int
	Index int
}

func minmax(i, j int) (int, int) {
	if i < j {
		return i, j
	}
	return j, i
}

func partialSum(l []int) []Entry {
	ret := make([]Entry, len(l))

	ret[0] = Entry{Sum: l[0], Index: 0}

	for i := 1; i < len(l); i++ {
		ret[i] = Entry{Sum: ret[i-1].Sum + l[i], Index: i}
	}

	return ret
}

func solve(l []int) (int, int) {

	ps := partialSum(l)

	sort.Slice(ps, func(i, j int) bool {
		return ps[i].Sum < ps[j].Sum
	})

	min, cur := MAX_VAL, 0

	for i := 1; i < len(ps); i++ {
		if math.Abs(float64(ps[i].Sum-ps[i-1].Sum)) < float64(min) {
			min = int(math.Abs(float64(ps[i].Sum - ps[i-1].Sum)))
			cur = i
		}
	}
	start, end := minmax(ps[cur].Index, ps[cur-1].Index)

	return start + 1, end
}

func main() {
	random := rand.New(rand.NewSource(43))

	for it := 0; it < TEST_CASES; it++ {
		n := random.Intn(N-2) + 2
		l := make([]int, n)

		for i := 0; i < n; i++ {
			l[i] = random.Intn(800) - 400
		}

		start, end := solve(l)
		fmt.Println(start, end)
	}
}
