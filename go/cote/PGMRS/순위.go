package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func countBackard(cur int, graph [][]bool, visited []bool) int {
	ret := 1
	visited[cur] = true

	for i := 0; i < len(visited); i++ {
		if !visited[i] && graph[i][cur] {
			ret += countBackard(i, graph, visited)
		}
	}

	return ret
}

func countForward(cur int, graph [][]bool, visited []bool) int {
	ret := 1
	visited[cur] = true

	for i := 0; i < len(visited); i++ {
		if !visited[i] && graph[cur][i] {
			ret += countForward(i, graph, visited)
		}
	}

	return ret
}

func solve(n int, edges [][]int) int {
	graph := make([][]bool, n)

	for i := 0; i < n; i++ {
		graph[i] = make([]bool, n)
	}

	for _, edge := range edges {
		i, j := edge[0], edge[1]
		graph[i-1][j-1] = true
	}

	count := 0

	for i := 0; i < n; i++ {
		wins := countForward(i, graph, make([]bool, n)) - 1
		loses := countBackard(i, graph, make([]bool, n)) - 1

		if wins+loses == n-1 {
			count++
		}
	}

	return count
}

func main() {

	f, _ := os.Open("data/순위.txt")
	r := bufio.NewReader(f)

	s, _ := r.ReadString('\n')
	testcases, _ := strconv.Atoi(strings.Trim(s, "\n"))

	for it := 0; it < testcases; it++ {
		s, _ = r.ReadString('\n')
		n, _ := strconv.Atoi(strings.Trim(s, "\n"))

		s, _ = r.ReadString('\n')
		numEdges, _ := strconv.Atoi(strings.Trim(s, "\n"))
		edges := make([][]int, numEdges)

		for i := 0; i < numEdges; i++ {
			s, _ = r.ReadString('\n')
			edge := strings.Split(strings.Trim(s, "\n"), " ")
			edges[i] = make([]int, 2)

			for j := 0; j < 2; j++ {
				v, _ := strconv.Atoi(edge[j])
				edges[i][j] = v
			}
		}
		s, _ = r.ReadString('\n')
		answer, _ := strconv.Atoi(strings.Trim(s, "\n"))

		fmt.Printf("%d %d\n", answer, solve(n, edges))
	}
}
