package main

import (
	"container/list"
	"math/rand"
	"fmt"
)

const (
	TEST_CASE = 10
	N = 10
	MAX_HEIGHT = 100
)

func max(a, b int) int {
	if a < b {
		return b
	}
	return a
}

func solve1(heights []int) int {
	volumne := 0
	left, right  := int(0), len(heights)-1
	leftmax, rightmax := int(0), int(0)

	for ok:= true; ok; ok = (left < right) {

		leftmax = max(leftmax, heights[left])
		rightmax = max(rightmax, heights[right])

		if leftmax <= rightmax {
			volumne += leftmax - heights[left]
			left ++
		} else {
			volumne += rightmax - heights[right]
			right--
		}
	}


	return volumne
}

func min(a, b int) int {
	if a < b {
		return a
	}
	return b
}

func solve2(heights []int) int {

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

func main() {
	rand.Seed(41)

	for it :=0; it < TEST_CASE; it++ {
		n := rand.Intn(N-2)+2
		h := rand.Intn(MAX_HEIGHT-1)+1
		
		heights := make([]int, n)

		for i, _ := range heights {
			heights[i] = rand.Intn(h)
		}

		fmt.Println(solve1(heights), solve2(heights))

	}
}