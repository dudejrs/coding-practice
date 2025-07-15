package main

import (
	"container/list"
	"fmt"
	"math/rand"
	"slices"
)

const (
	N          = 10
	TEST_CASES = 10
	MAX_EDGES  = 3
)

func check_euler(adj [][]int) bool {
	for i, _ := range adj {
		tmp := 0
		for _, v := range adj[i] {
			tmp += v
		}

		if tmp%2 == 1 {
			return false
		}
	}
	return true
}

func check_reachable(adj [][]int) bool {
	visited := make([]bool, len(adj))

	stack := list.New()
	stack.PushBack(0)

	for {
		if stack.Len() == 0 {
			break
		}

		cur := stack.Remove(stack.Back()).(int)
		visited[cur] = true

		for next, connected := range adj[cur] {
			if connected > 0 && !visited[next] {
				stack.PushBack(next)
			}
		}
	}

	for _, v := range visited {
		if !v {
			return false
		}
	}

	return true
}

func initialize(random *rand.Rand) (ret [][]int) {

	for {
		n := random.Intn(N-2) + 2
		ret = make([][]int, n)

		for i, _ := range ret {
			ret[i] = make([]int, n)
		}

		for i, _ := range ret {
			for j := i + 1; j < n; j++ {
				if random.Float32() < 0.05 {
					continue
				}
				ret[i][j] = random.Intn(3-1) + 1
				ret[j][i] = ret[i][j]
			}
		}

		if check_euler(ret) && check_reachable(ret) {
			return
		}
	}
}

func dfs(cur int, graph [][]int, ret *[]int) {

	for i, _ := range graph[cur] {
		for {
			if graph[cur][i] == 0 {
				break
			}
			graph[cur][i]--
			graph[i][cur]--
			dfs(i, graph, ret)
		}
	}
	*ret = append(*ret, cur)
}

func solve(adj [][]int, start int) []int {
	ret := make([]int, 0)

	dfs(start, adj, &ret)
	slices.Reverse(ret)

	return ret
}

func main() {
	random := rand.New(rand.NewSource(43))

	for it := 0; it < TEST_CASES; it++ {
		adj := initialize(random)
		n := random.Intn(len(adj))
		fmt.Println(solve(adj, n))
	}
}
