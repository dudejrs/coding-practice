package main

import (
	"fmt"
	"math/rand"
)

const (
	TEST_CASES = 10
	N          = 100
)

func initialize(random *rand.Rand) [][]int {
	n := random.Intn(N-3) + 3
	ret := make([][]int, n)

	for i, _ := range ret {
		for j := 0; j < n; j++ {
			if random.Float32() < 0.95 {
				continue
			}
			ret[i] = append(ret[i], j)
		}
	}

	return ret
}

func dfs(cur int, graph [][]int, visited []bool) {
	visited[cur] = true

	for _, next := range graph[cur] {
		if !visited[next] {
			dfs(next, graph, visited)
		}
	}
}

func solve(a, b int, graph [][]int) bool {
	visited := make([]bool, len(graph))

	for i, _ := range visited {
		visited[i] = false
	}

	dfs(a, graph, visited)

	return visited[b]
}

func main() {
	random := rand.New(rand.NewSource(43))

	for it := 0; it < TEST_CASES; it++ {
		graph := initialize(random)
		b := random.Intn(len(graph)-1) + 1
		a := random.Intn(b)

		fmt.Println(solve(a, b, graph))
	}
}
