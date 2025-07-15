package LTCD

import (
	"container/list"
	"fmt"
	"math/rand"
)

// const (
// 	TEST_CASE = 10
// 	N = 10000
// 	MAX_TEMPERATURE = 40
// 	MIN_TEMPERATURE = -10
// )

type 일일_온도 struct {
	TEST_CASE       int
	N               int
	MAX_TEMPERATURE int
	MIN_TEMPERATURE int
}

// 온도가 올라가기 까지 걸린 시간
func (problem 일일_온도) solve(T []int) []int {
	ret := make([]int, len(T))
	stack := list.New()
	for i, cur := range T {
		for {
			if stack.Len() == 0 {
				break
			}
			if T[stack.Back().Value.(int)] >= cur {
				break
			}

			j := stack.Back().Value.(int)
			ret[j] = i - j
			stack.Remove(stack.Back())
		}

		stack.PushBack(i)
	}

	return ret
}

func (problem 일일_온도) main() {
	random := rand.New(rand.NewSource(43))

	for it := 0; it < problem.TEST_CASE; it++ {
		T := make([]int, random.Intn(problem.N-1)+1)
		for i, _ := range T {
			T[i] = random.Intn(problem.MAX_TEMPERATURE-problem.MIN_TEMPERATURE) + problem.MIN_TEMPERATURE
		}
		fmt.Println(problem.solve(T))
	}
}
