package main

import (
	"fmt"
	"os"
	"bufio"
	"strconv"
	"strings"
)


func max(x, y int) int {
	if x < y {
		return y
	}

	return x
}

func min(x, y int) int {
	if y < x {
		return y
	}
	return x
}


func search(left, right int, h []int) int {

	if left == right {
		return h[left]
	}

	mid := (left + right) / 2
	ret := max(search(left, mid, h), search(mid+1, right, h))
	lo, hi := mid, mid+1
	height := min(h[lo], h[hi])
	ret = max(ret, 2 * height)


	for {
		if left == lo && hi == right {
			break
		}

		if left < lo && (hi == right || h[hi+1] < h[lo-1]) {
			height = min(height, h[lo-1])
			lo--
		} else {
			height = min(height, h[hi+1])
			hi++
		}

		ret = max(ret, height * (hi - lo +1))
	}

	return ret
}

func solve(n int, h []int) int {

	return search(0, n-1, h)
}


func main() {
	f, _ := os.Open("data/울타리_잘라내기.txt")
	r := bufio.NewReader(f)
	s, _:= r.ReadString('\n')
	testcases, _ := strconv.Atoi(strings.Trim(s, "\n"))

	for {
		if testcases == 0 {
			break
		}
		s, _ := r.ReadString('\n')
		n, _ := strconv.Atoi(strings.Trim(s, "\n"))
		s , _ = r.ReadString('\n')
		tokens := strings.Split(strings.Trim(s, "\n"), " ")
		h := make([]int, len(tokens))

		for i, v := range tokens {
			h[i], _ = strconv.Atoi(v)
		}


		fmt.Println(solve(n, h))
		testcases--
	}
}