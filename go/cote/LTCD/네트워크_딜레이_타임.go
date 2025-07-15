package LTCD

import (
	"fmt"
	"math"
	"math/rand"
	"sort"
	"container/heap"
)

// const (
// 	TEST_CASE = 10
// 	N = 20
// 	MAX_DELAY = 10
// )

type 네트워크_딜레이_타입 struct {
	TEST_CASE  int
	N int
	MAX_DELAY int
}

type Entry struct {
	Time int
	Node int
}

type Heap []Entry

func (h Heap) Len() int {
	return len(h)
}

func (h Heap) Less(i, j int) bool {
	return h[i].Time < h[j].Time
}

func (h Heap) Swap(i, j int) {
	h[i], h[j] = h[j], h[i]
}

func (h *Heap) Push(x any) {
	*h = append(*h, x.(Entry))
}

func (h *Heap) Pop() any {
	old := *h 
	n := len(old)
	x := old[n-1]
	*h = old[0 : n-1]
	return x
}

func (problem 네트워크_딜레이_타입) initialize(n int, random *rand.Rand) ([][]int, int) {
	numEdges := random.Intn(int(math.Floor(float64(n * (n-1) / 2.0))))
	ret := make([][]int, 0)
	count := make([]int, n)
	set := make([][]bool, n)

	for i, _ := range set {
		set[i] = make([]bool, n)	
	}

	for {
		if len(ret) == numEdges {
			break
		} 
		i, j := random.Intn(n), random.Intn(n)

		if set[i][j] || i == j {
			continue
		}

		ret = append(ret, []int{i, j, random.Intn(problem.MAX_DELAY)})
		set[i][j], set[j][i] = true, true
		count[i]++
		count[j]++
	}

	sort.Sort(sort.Reverse(sort.IntSlice(count)))

	return ret, count[0]
}

func (problem 네트워크_딜레이_타입) solve(edges [][]int, n, k int) int {

	graph := make(map[int][][]int, n)
	dist := make(map[int]int)

	for _, e := range edges {
		i, j, v := e[0], e[1], e[2]	
		graph[i] = append(graph[i], []int {j, v})
	}	

	h := &Heap{Entry{0, k}}
	heap.Init(h)

	for {
		if h.Len() == 0 {
			break
		}
		
		e := heap.Pop(h).(Entry)
		time, node := e.Time, e.Node

		_, ok := dist[node]

		if !ok {
			dist[node] = time

			for _, e := range graph[node] {
				delay := time + e[1]
				heap.Push(h, Entry{delay, e[0]})
			}
		}
	}

	if len(dist) == n {
		max := -1

		for _, v := range dist {
			if max < v {
				max = v 
			}
		}

		return max
	}

	return -1
}

func (problem 네트워크_딜레이_타입) main() {
	random := rand.New(rand.NewSource(43))

	for it := 0; it < problem.TEST_CASE; it++ {
		n := random.Intn(problem.N - 3) + 3
		edges, k  := problem.initialize(n, random)
		
		fmt.Println(problem.solve(edges, n, k))
	}
}