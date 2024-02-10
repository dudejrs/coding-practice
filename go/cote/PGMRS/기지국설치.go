package main

import (
	"fmt"
	"os"
	"bufio"
	"strconv"
	"strings"
	"container/list"
)

func solve(numApartment int, equipped []int, wide int) int {

	queue := list.New()

	for _, v := range equipped {
		queue.PushBack(v)
	}

	ret := 0
	position := 1
	for {
		if position > numApartment {
			break
		}

		if queue.Len() != 0 &&  queue.Front().Value.(int) <= position + wide  {
			position = queue.Remove(queue.Front()).(int) + wide + 1
		} else {
			ret++
			position += 2 * wide + 1
		}
	}

	return ret
}

func main() {

	f, _ := os.Open("data/기지국설치.txt")
	r := bufio.NewReader(f)
	s, _ := r.ReadString('\n')
	testcases, _ := strconv.Atoi(strings.Trim(s, "\n"))

	for {
		if testcases <= 0 {
			break
		}

		s, _ = r.ReadString('\n')
		numApartment, _ := strconv.Atoi(strings.Trim(s, "\n"))

		s, _ = r.ReadString('\n')
		tokens := strings.Split(strings.Trim(s, "\n"), " ")
		equipped := make([]int,0)

		for _, apartment := range tokens {
			n, _ := strconv.Atoi(apartment)
			equipped = append(equipped, n)
		}

		s, _ = r.ReadString('\n')
		wide, _ := strconv.Atoi(strings.Trim(s, "\n"))

		s, _ = r.ReadString('\n')
		answer, _ := strconv.Atoi(strings.Trim(s, "\n"))

		fmt.Printf("%d %d\n", answer, solve(numApartment, equipped, wide))
		testcases--;
	}
}