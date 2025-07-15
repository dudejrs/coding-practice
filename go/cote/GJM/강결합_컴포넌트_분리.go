package main

import (
	"container/list"
	"fmt"
	"math/rand"
	"slices"
)

const (
	TEST_CASES = 10
	N          = 1000
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

func initialize(random *rand.Rand) (ret [][]int) {
	n := random.Intn(N-3) + 3
	for {
		ret = make([][]int, n)

		for i, _ := range ret {
			for j := 0; j < n; j++ {
				if i == j || random.Float32() < 0.975 {
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

func min(x, y int) int {
	if x < y {
		return x
	}
	return y
}

func dfs(cur int, finished []bool, discovered, sccIds []int, stack *list.List, vertex_counter, scc_counter *int, adj [][]int) int {
	discovered[cur] = *vertex_counter
	(*vertex_counter) += 1
	ret := discovered[cur]

	stack.PushBack(cur)

	for _, next := range adj[cur] {
		if discovered[next] == -1 {
			subtree := dfs(next, finished, discovered, sccIds, stack, vertex_counter, scc_counter, adj)
			ret = min(ret, subtree)
		} else if discovered[next] < discovered[cur] && !finished[next] {
			ret = min(ret, discovered[next])
		}
	}

	if ret == discovered[cur] {
		for {
			t := stack.Back().Value.(int)
			stack.Remove(stack.Back())
			sccIds[t] = *scc_counter

			if t == cur {
				break
			}
		}
		(*scc_counter) += 1
	}

	finished[cur] = true

	return ret
}

func solve(adj [][]int) []int {
	n := len(adj)
	finished := make([]bool, n)
	discovered := make([]int, n)
	sccIds := make([]int, n)
	stack := list.New()
	vertex_counter, scc_counter := 0, 0

	for i, _ := range finished {
		finished[i] = false
	}

	for i, _ := range discovered {
		discovered[i] = -1
	}

	for i, _ := range sccIds {
		sccIds[i] = -1
	}

	dfs(0, finished, discovered, sccIds, stack, &vertex_counter, &scc_counter, adj)

	return sccIds
}

func main() {
	random := rand.New(rand.NewSource(43))

	for it := 0; it < TEST_CASES; it++ {
		adj := initialize(random)
		fmt.Println(solve(adj))
	}
}
