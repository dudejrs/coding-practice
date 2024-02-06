package main

import (
	"fmt"
	"os"
	"bufio"
	"strconv"
	"strings"
	"container/list"
)

func getContact(s string) [][2]int {

	l := strings.Split(s, " ")

	ret := make([][2]int, 0)

	for i := 0; i < len(l)/2; i++ {
		a, _ := strconv.Atoi(l[2*i])
		b, _ := strconv.Atoi(l[2*i+1])
		ret = append(ret, [2]int{a,b})
	}

	return ret
}

func solve(n, c, k int, contact [][2]int) int {

	graph := make([][]bool, n)

	for i := 0; i < n; i++ {
		graph[i] = make([]bool, n)
	}

	for _, c := range contact {
		i, j := c[0]-1, c[1]-1
		graph[i][j] = true
	}


	counts := make([]int, n)
	queue := list.New()

	for i := 0; i < c; i++ {
		counts[i] = -1
		queue.PushBack(i)
	}

	for {
		if queue.Len() == 0 {
			break
		}

		cur := queue.Front().Value.(int)
		queue.Remove(queue.Front())

		for i := c; i < n; i++ {
			if counts[i] >= 0 && graph[cur][i]  {
				counts[i]++
			}
		}

		for i := 0; i < n; i++ {
			if counts[i] >=k {
				queue.PushBack(i)
				counts[i] = -1
			}
		}
	}

	ret := 0

	for i := 0; i < n; i++ {
		if counts[i] == 0 {
			ret++
		}
	}

	return ret
}

func main() {

	f, _ := os.Open("data/행운의_편지.txt")
	r :=  bufio.NewReader(f)

	s, _ := r.ReadString('\n')
	testcases, _ := strconv.Atoi(strings.Trim(s, "\n"))

	for it := 0; it < testcases; it++ {
		s, _ := r.ReadString('\n')
		n, _ := strconv.Atoi(strings.Trim(s, "\n"))
		
		s, _ = r.ReadString('\n')
		c, _ := strconv.Atoi(strings.Trim(s, "\n")) 

		s, _ = r.ReadString('\n')
		k, _ := strconv.Atoi(strings.Trim(s, "\n"))

		s, _ = r.ReadString('\n')
		contact := getContact(strings.Trim(s, "\n"))

		s, _ = r.ReadString('\n')
		answer, _ := strconv.Atoi(strings.Trim(s, "\n"))

		fmt.Println(answer, solve(n,c,k,contact))
	}

}