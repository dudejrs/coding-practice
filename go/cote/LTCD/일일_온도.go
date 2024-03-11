package main

import (
	"fmt"
	"math/rand"
	"container/list"
)

const (
	TEST_CASE = 10
	N = 10000
	MAX_TEMPERATURE = 40
	MIN_TEMPERATURE = -10
)

// 온도가 올라가기 까지 걸린 시간
func solve(T []int)[]int {
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

func main() {
	random := rand.New(rand.NewSource(43))

	for it := 0; it < TEST_CASE; it++ {
		T := make([]int, random.Intn(N - 1) + 1)
		for i, _ := range T {
			T[i] = random.Intn(MAX_TEMPERATURE - MIN_TEMPERATURE) + MIN_TEMPERATURE
		}
		fmt.Println(solve(T))
	}
}