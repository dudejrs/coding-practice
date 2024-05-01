package main

import(
	"math/rand"
	"slices"
	"fmt"
	"math"
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

	return !slices.Contains(visited, false)
}

func initialize(random *rand.Rand) [][]int {
	n := random.Intn(N - 3) + 3
	var ret [][]int

	for {
		ret = make([][]int, n)
		for i, _ := range ret {
			for j := 0; j < n; j++ {
				if i == j || random.Float32() < 0.8  {
					continue
				}
				ret[i] = append(ret[i], j)
			}
		}

		if check_reachable(ret) {
			break
		}
	}

	return ret
}

func dfs(cur int, discovered []int, finished []bool, counter *int, adj [][]int) int {

	discovered[cur] = *counter
	(*counter)++

	ret := math.MaxInt32

	for _, next := range adj[cur] {

		if discovered[next] == -1 {
			fmt.Printf("tree edge(%d,%d) ",cur, next)
			dfs(next, discovered, finished, counter, adj)
		
		} else if discovered[next] > discovered[cur] {
			fmt.Printf("forward edge(%d,%d) ",cur, next)

		} else if !finished[next] {
			fmt.Printf("backward edge(%d,%d) ",cur, next)

		} else {
			fmt.Printf("cross edge(%d,%d) ",cur, next)
		}
	}

	finished[cur] = true

	return ret
}


func solve(adj [][]int) {
	discovered := make([]int, len(adj))	
	finished := make([]bool, len(adj))
	counter := 0

	for i, _ := range discovered {
		discovered[i] = -1
	}

	for i := 0; i < len(adj); i++ {
		if discovered[i] == -1 {
			dfs(i, discovered, finished, &counter, adj)
		}
	}
}

func main() {
	random := rand.New(rand.NewSource(43))

	for it := 0; it < TEST_CASES; it++ {
		adj := initialize(random)
		solve(adj)
		fmt.Println()
	}
}