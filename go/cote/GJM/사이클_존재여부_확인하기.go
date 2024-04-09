package main

import (
	"fmt"
	"math/rand"
	"slices"
)

const (
	TEST_CASES = 10
	N = 10
)

func _dfs(cur int, adj [][]int, visited []bool) {
	visited[cur] = true

	for _, next := range adj[cur] {
		if !visited[next] {
			_dfs(next, adj, visited)
		}
	}
}

func check_reachable(adj [][]int) bool {
	visited := make([]bool, len(adj)) 

	_dfs(0, adj, visited)

	for _, v := range visited {
		if !v {
			return false
		} 
	}

	return true
}

func initialize(random *rand.Rand) (ret [][]int) {

	for {
		n := random.Intn(N - 3) + 3
		ret = make([][]int, n)
		for i, _ := range ret {
			for j := 0; j < n; j++ {
				if i == j || random.Float32() < 0.9 {
					continue
				}
				ret[i] = append(ret[i], j)
			}
		}

		if check_reachable(ret)  {
			return
		}

	}
	return
}

func dfs(cur int, adj [][]int, visited []bool, path []int) bool {
	visited[cur] = true

	for _, next := range adj[cur] {
		if !visited[next]  {
			newPath := append(slices.Clone(path), next)
			if dfs(next, adj, visited, newPath) {
				return true
			}

		} else if slices.Contains(path, next){
			return true
		}
	}

	return false
}

func solve(adj [][]int) bool {
	visited := make([]bool, len(adj))

	for i := 0; i < len(adj); i++ {
		if !visited[i] && dfs(i, adj, visited, []int{i}) {
			return true
		}
	}

	return false
}

func main() {
	random := rand.New(rand.NewSource(43))

	for it := 0; it < TEST_CASES; it++ {
		adj := initialize(random)
		fmt.Println(solve(adj))
	}
}