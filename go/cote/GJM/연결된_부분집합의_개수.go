package main

import (
	"fmt"
	"math/rand"
)

const (
	TEST_CASES = 10
	N          = 1000
)

func initialize(random *rand.Rand) (ret [][]int) {
	n := random.Intn(N)
	ret = make([][]int, n)

	for i, _ := range ret {
		for j := i + 1; j < n; j++ {
			if random.Float32() < 0.25 {
				ret[i] = append(ret[i], j)
			}
		}
	}
	return
}

func dfs(cur int, visited []bool, graph [][]int) {
	visited[cur] = true

	for _, next := range graph[cur] {
		if !visited[next] {
			dfs(next, visited, graph)
		}
	}

}

func solve(graph [][]int) (count int) {
	visited := make([]bool, len(graph))

	for i := 0; i < len(graph); i++ {
		if !visited[i] {
			dfs(i, visited, graph)
			count++
		}
	}

	return count
}

func main() {
	random := rand.New(rand.NewSource(43))

	for it := 0; it < TEST_CASES; it++ {
		graph := initialize(random)
		fmt.Println(solve(graph))
	}
}
