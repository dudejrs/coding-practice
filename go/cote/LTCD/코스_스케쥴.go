package LTCD

import (
	"fmt"
	"math/rand"
)

// const (
// 	TEST_CASE = 10
// 	N = 100
// )

type 코스_스케쥴 struct {
	TEST_CASE int
	N         int
}

func (problem 코스_스케쥴) initialize(n int, random *rand.Rand) [][]int {
	ret := make([][]int, 0)
	set := make(map[int]map[int]bool, 0)

	for i := 0; i < n; i++ {
		set[i] = make(map[int]bool, 0)
	}

	for i := 0; i < n; i++ {
		for j := 0; j < n; j++ {
			if i == j {
				continue
			}

			if set[i][j] || set[j][i] {
				continue
			}

			if random.Float32() < 0.975 {
				continue
			}

			ret = append(ret, []int{i, j})
			set[j][i], set[i][j] = true, true
		}
	}

	return ret
}

func (problem 코스_스케쥴) dfs(cur int, graph [][]int, traced []bool, visited []bool) bool {

	if traced[cur] {
		return false
	}

	if visited[cur] {
		return true
	}

	traced[cur] = true

	for _, y := range graph[cur] {
		if !problem.dfs(y, graph, traced, visited) {
			return false
		}
	}

	traced[cur] = false
	visited[cur] = true

	return true
}

func (problem 코스_스케쥴) solve(n int, prerequisites [][]int) bool {

	graph := make([][]int, n)

	for i := 0; i < n; i++ {
		graph[i] = make([]int, 0)
	}

	for _, p := range prerequisites {
		graph[p[0]] = append(graph[p[0]], p[1])
	}

	traced := make([]bool, n)
	visited := make([]bool, n)

	for i := 0; i < n; i++ {
		if !problem.dfs(i, graph, traced, visited) {
			return false
		}
	}

	return true
}

func (problem 코스_스케쥴) main() {
	random := rand.New(rand.NewSource(43))
	for it := 0; it < problem.TEST_CASE; it++ {
		n := random.Intn(problem.N)
		prerequisites := problem.initialize(n, random)

		fmt.Println(problem.solve(n, prerequisites))
	}
}
