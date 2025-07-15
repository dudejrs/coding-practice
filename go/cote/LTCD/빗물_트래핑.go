package LTCD

import (
	"container/list"
	"fmt"
	"math/rand"
)

// const (
// 	TEST_CASE = 10
// 	N = 10
// 	MAX_HEIGHT = 100
// )

type 빗물_트래핑 struct {
	TEST_CASE  int
	N          int
	MAX_HEIGHT int
}

func (problem 빗물_트래핑) max(a, b int) int {
	if a < b {
		return b
	}
	return a
}

func (problem 빗물_트래핑) min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func (problem 빗물_트래핑) solve1(heights []int) int {
	volumne := 0
	left, right := int(0), len(heights)-1
	leftmax, rightmax := int(0), int(0)

	for ok := true; ok; ok = (left < right) {

		leftmax = problem.max(leftmax, heights[left])
		rightmax = problem.max(rightmax, heights[right])

		if leftmax <= rightmax {
			volumne += leftmax - heights[left]
			left++
		} else {
			volumne += rightmax - heights[right]
			right--
		}
	}

	return volumne
}

func (problem 빗물_트래핑) solve2(heights []int) int {

	volume := 0
	stack := list.New()

	for i, _ := range heights {

		for {
			if stack.Len() == 0 {
				break
			}

			top := stack.Back().Value.(int)

			if heights[i] <= heights[top] {
				break
			}

			cur := stack.Remove(stack.Back()).(int)

			if stack.Len() == 0 {
				break
			}

			left := stack.Back().Value.(int)
			distance := i - left - 1
			waters := min(heights[left], heights[i]) - heights[cur]
			volume += distance * waters

		}

		stack.PushBack(i)
	}

	return volume
}

func (problem 빗물_트래핑) main() {
	rand.Seed(41)

	for it := 0; it < problem.TEST_CASE; it++ {
		n := rand.Intn(problem.N-2) + 2
		h := rand.Intn(problem.MAX_HEIGHT-1) + 1

		heights := make([]int, n)

		for i, _ := range heights {
			heights[i] = rand.Intn(h)
		}

		fmt.Println(problem.solve1(heights), problem.solve2(heights))

	}
}
