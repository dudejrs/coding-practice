package main

import (
	"fmt"
	"os"
	"bufio"
	"strconv"
	"strings"
	"slices"
	"math"
)

func sum(coin []int) int {
	ret := 0

	for _, v := range coin {
		ret += v
	}

	return ret
}

	
func min(x, y int) int {
	if x < y {
		return x
	}
	return y
}

func flipCoins(coin []int, k, target int) int {

	count := 0

	for i := 0; i < len(coin) - k +1; i++ {
		if coin[i] == target {
			continue
		}

		for j := 0; j < k; j++ {
			coin[i+j] = 1 - coin[i+j]
		}

		count++
	}

	if sum(coin) != len(coin) && sum(coin) != 0 {
		return math.MaxInt32
	}

	return count
}


func solve(coin []int, k int) int {

	if len(coin) == 1 {
		return 0
	}

	sum := sum(coin)

	if sum == 0 || sum == len(coin) {
		return 0
	}

	if sum != k && len(coin) == k {
		return -1
	}


	all0 := flipCoins(slices.Clone(coin), k, 0)
	all1 := flipCoins(slices.Clone(coin), k, 1)

	ret := min(all0, all1)

	if ret == math.MaxInt32 {
		return -1
	}

	return ret
}

func main() {

	f, _ := os.Open("data/동전_뒤집기.txt")
	
	r := bufio.NewReader(f)

	s, _ := r.ReadString('\n')
	testcases, _ := strconv.Atoi(strings.Trim(s,"\n"))

	for it := 0; it < testcases; it++ {
		s, _ = r.ReadString('\n')
		tokens := strings.Split(strings.Trim(s, "\n"), " ")
		coin := make([]int, 0) 

		for _, v := range tokens {
			num, _ := strconv.Atoi(v)
			coin = append(coin, num)
		}

		s, _ = r.ReadString('\n')
		k, _ := strconv.Atoi(strings.Trim(s, "\n"))

		s, _ = r.ReadString('\n')
		answer, _ := strconv.Atoi(strings.Trim(s, "\n"))

		fmt.Printf("%d %d\n", answer, solve(coin, k))
	}
}