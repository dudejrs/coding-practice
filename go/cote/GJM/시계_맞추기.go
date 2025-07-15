package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

const INF = 987654321

func min(x, y int) int {
	if x < y {
		return x
	}
	return y
}

func aligned(clocks []int) bool {

	for _, clock := range clocks {
		if clock != 12 {
			return false
		}
	}

	return true
}

func push(cur int, linked [][]bool, clocks []int) {
	for i, v := range clocks {
		if linked[cur][i] == true {
			clocks[i] = (v + 3) % 12
		}
	}
}

func search(cur int, linked [][]bool, clocks []int) int {
	if cur == len(linked) {
		if aligned(clocks) {
			return 0
		}
		return INF
	}

	ret := INF

	for it := 0; it < 4; it++ {
		ret = min(ret, it+search(cur+1, linked, clocks))
		push(cur, linked, clocks)
	}

	return ret
}

func solve(linked [][]bool, clocks []int) int {
	return search(0, linked, clocks)
}

func main() {
	f, _ := os.Open("data/시계_맞추기.txt")
	r := bufio.NewReader(f)
	s, _ := r.ReadString('\n')

	l := strings.Split(strings.Trim(s, "\n"), " ")

	numButtons, _ := strconv.Atoi(l[0])
	numClocks, _ := strconv.Atoi(l[1])
	linked := make([][]bool, numButtons)

	for i, _ := range linked {
		s, _ = r.ReadString('\n')
		linked[i] = make([]bool, numClocks)
		s = strings.Trim(s, "\n")

		for j, v := range s {
			switch v {
			case 'x':
				linked[i][j] = true
			default:
				linked[i][j] = false
			}
		}
	}

	s, _ = r.ReadString('\n')
	testcases, _ := strconv.Atoi(strings.Trim(s, "\n"))
	for it := 0; it < testcases; it++ {
		s, _ = r.ReadString('\n')
		s = strings.Trim(s, "\n")

		clocks := make([]int, numClocks)
		states := strings.Split(s, " ")

		for j, v := range states {
			time, _ := strconv.Atoi(v)
			clocks[j] = time
		}
		fmt.Println(solve(linked, clocks))
	}
}
