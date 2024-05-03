package main

import (
	"fmt"
	"math/rand"
	"container/list"
	"slices"
)

const (
	TEST_CASES = 10
	N = 1000
)

func initialize(random *rand.Rand) ([][]int, int, int) {
	n := random.Intn(N - 3) + 3
	ret := make([][]int, n)

	for i := 0; i < n; i++ {
		for j := i + 1; j < n; j++ {
			if random.Float32() < 0.9775 {
				continue
			}
			ret[i] = append(ret[i], j)
			ret[j] = append(ret[j], i)
		}
	}

	a := random.Intn(n - 1) + 1
	b := random.Intn(a)
	return ret, b, a
}

func bfs(src int, adj [][]int) []int {
	distance := make([]int, len(adj))
	parent := make([]int, len(adj))

	for i, _ := range distance {
		distance[i] = -1
	}

	for i, _ := range parent {
		parent[i] = -1
	}

	queue := list.New()
	queue.PushBack(src)
	parent[src] = src 
	distance[src] = 0

	for{
		if queue.Len() == 0 {
			break
		}

		cur := queue.Front().Value.(int)
		queue.Remove(queue.Front())

		for _, next := range adj[cur] {
			if distance[next] == -1 {
				queue.PushBack(next)
				parent[next] = cur
				distance[next] = distance[cur] + 1
			}
		}
	}

	return parent
}

func shoretest_path(target int, parent []int) []int {
	ret := make([]int, 0)

	ret = append(ret, target)
	for {
		if parent[target] == - 1 {
			return make([]int, 0)
		}

		if parent[target] == target {
			break
		}
		ret = append(ret, parent[target])
		target = parent[target]
	}

	slices.Reverse(ret)

	return ret
}

func solve(src, target int, adj [][]int) []int {
	parent := bfs(src, adj)

	return shoretest_path(target, parent)
}

func main() {
	random := rand.New(rand.NewSource(43))
	for it := 0; it < TEST_CASES; it++ {
		adj, src, target := initialize(random)
		fmt.Println(solve(src, target, adj))
	}
}