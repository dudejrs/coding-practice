package main

import (
	"container/heap"
	"fmt"
	"math"
	"math/rand"
	"slices"
)

type State struct {
	Cur  int
	Cost float32
}

type PQ []State

func (p PQ) Len() int {
	return len(p)
}

func (p PQ) Less(i, j int) bool {
	return p[i].Cost < p[j].Cost
}

func (p PQ) Swap(i, j int) {
	p[i], p[j] = p[j], p[i]
}

func (p *PQ) Push(x any) {
	*p = append(*p, x.(State))
}

func (p *PQ) Pop() any {
	old := *p
	n := len(old)
	x := old[n-1]
	*p = old[0 : n-1]
	return x
}

const (
	N          = 1000
	M          = 10 * N
	TEST_CASES = 10
	MIN_COST   = 1.0
	MAX_COST   = 3.0
)

func _dfs(cur int, graph [][]float32, visited []bool) {
	visited[cur] = true

	for next := 0; next < len(graph); next++ {
		if graph[cur][next] == 0 || visited[next] {
			continue
		}
		_dfs(next, graph, visited)
	}
}

func _all_reachable(graph [][]float32) bool {
	visited := make([]bool, len(graph))

	for i, _ := range visited {
		visited[i] = false
	}

	_dfs(0, graph, visited)

	return !slices.Contains(visited, false)
}

func initialize(n int, random *rand.Rand) [][]float32 {
	var ret [][]float32
	for {
		ret = make([][]float32, n)

		for i, _ := range ret {
			ret[i] = make([]float32, n)
			for j, _ := range ret[i] {
				if random.Float32() >= 0.05 {
					continue
				}

				ret[i][j] = random.Float32()*float32(MAX_COST-MIN_COST) + float32(MIN_COST)
			}
		}

		if _all_reachable(ret) {
			break
		}
	}

	return ret
}

func solve(n, src, dst int, graph [][]float32) float32 {

	pq := &PQ{}
	dist := make([]float32, len(graph))

	for i, _ := range dist {
		dist[i] = math.MaxFloat32
	}
	dist[0] = 1
	heap.Push(pq, State{0, 1})

	for {
		if pq.Len() == 0 {
			break
		}

		state := heap.Pop(pq).(State)
		cur, cost := state.Cur, state.Cost

		if dist[cur] < cost {
			dist[cur] = cost
		}

		for next, v := range graph[cur] {
			if v == 0 {
				continue
			}

			next_cost := cost * v

			if next_cost < dist[next] {
				dist[next] = next_cost
				heap.Push(pq, State{next, next_cost})
			}
		}
	}

	return dist[dst]
}

func main() {
	random := rand.New(rand.NewSource(43))

	for it := 0; it < TEST_CASES; it++ {
		n := random.Intn(N-3) + 3
		k := random.Intn(n-1) + 1

		graph := initialize(n, random)
		fmt.Println(solve(n, 0, k, graph))
	}
}
