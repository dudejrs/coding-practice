package main

import (
	"fmt"
	"math/rand"
	"sort"
)

const (
	TEST_CASE = 10
	N         = 1000
	MAX_EAT   = 180
	MAX_HEAT  = 180
)

type Person struct {
	Eat  int
	Heat int
}

type People []Person

func (p People) Len() int {
	return len(p)
}

func (p People) Less(i, j int) bool {
	return p[i].Eat > p[j].Eat
}

func (p People) Swap(i, j int) {
	p[i], p[j] = p[j], p[i]
}

func max(i, j int) int {
	if i < j {
		return j
	}
	return i
}

func initialize(n int, random *rand.Rand, max int) []int {
	ret := make([]int, n)

	for i, _ := range ret {
		ret[i] = random.Intn(max)
	}

	return ret
}

func solve(n int, eat, heat []int) int {

	people := make([]Person, n)

	for i, _ := range people {
		people[i].Eat = eat[i]
		people[i].Heat = heat[i]
	}

	sort.Sort(People(people))

	cur, ret := 0, 0
	for _, person := range people {
		cur += person.Heat
		ret = max(ret, cur+person.Eat)
	}

	return ret
}

func main() {
	random := rand.New(rand.NewSource(43))

	for it := 0; it < TEST_CASE; it++ {
		n := random.Intn(N)
		heat := initialize(n, random, MAX_HEAT)
		eat := initialize(n, random, MAX_EAT)
		fmt.Println(solve(n, eat, heat))
	}
}
