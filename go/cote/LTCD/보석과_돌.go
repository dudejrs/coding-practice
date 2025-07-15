package LTCD

import (
	"fmt"	
	"math/rand"
)

// const (
// 	TEST_CASE = 10
// 	STONES = 100
// 	JEWALS = 'z' - 'a' + 1
// )

type 보석과_돌 struct {
	TEST_CASE int 
	STONES int 
	JEWALS int
}

func (problem 보석과_돌) solve(jewals ,stones []string) int {
	ret := 0
	freq := make(map[string]int, 0)

	for _, stone := range stones {
		_, ok := freq[stone]

		if !ok {
			freq[stone] = 0
		}

		freq[stone] += 1
	}

	for _, jewal := range jewals {
		ret += freq[jewal]
	}

	return ret
}

func (problem 보석과_돌) main() {
	random := rand.New(rand.NewSource(43))

	for it := 0; it < problem.TEST_CASE; it++ {
			
		jewals := make([]string, 0)

		for c := 'a'; c < 'z'; c++ {
			if random.Float32() < 0.5 {
				jewals = append(jewals, string(c))
			}
		}

		stones := make([]string, random.Intn(problem.STONES - 1) + 1)

		for i, _ := range stones {
			stones[i] = string('a' + random.Intn(problem.JEWALS))
		}

		fmt.Println(problem.solve(jewals, stones))
	}
}