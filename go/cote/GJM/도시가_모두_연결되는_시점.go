package main

import (
	"fmt"
	"math/rand"
	"sort"
)

const (
	TEST_CASE = 10
	N = 10
	MAX_DELAY = 100
)

type Edge struct {
	From int
	To int
	Delay int
}

type Edges []Edge

func (e Edges) Len() int {
	return len(e)
}

func (e Edges) Less(i, j int) bool {
	return e[i].Delay < e[j].Delay
}

func (e Edges) Swap(i, j int) {
	e[i], e[j] = e[j], e[i]
}

type DisjointSet interface {
	Init(n int)
	Find(u int) int
	Merge(u, v int)
}

type TreeSet struct {
	Parent []int 
	Rank []int
	Size int
}

func (s *TreeSet) Init(n int){
	s.Parent = make([]int, n)
	s.Rank = make([]int, n)
	s.Size = n

	for i, _ := range s.Parent {
		s.Parent[i] = i 
	}
}

func (s *TreeSet) Find(u int) int {
	if s.Parent[u] == u {
		return u
	}

	s.Parent[u] = s.Find(s.Parent[u])

	return s.Parent[u]
}

func (s *TreeSet) Merge(u, v int) {
	u = s.Find(u)
	v = s.Find(v)

	if u == v {
		return
	}

	if s.Rank[u] < s.Rank[v] {
		u, v = v, u
	}
	s.Parent[v] = u
	
	if s.Rank[u] == s.Rank[v] {
		s.Rank[u]++ 
	} 
	s.Size--
}

func initialize(random *rand.Rand) (n int, edges []Edge) {
	n = random.Intn(N - 3) + 3
	edges = make([]Edge, n)

	for i, _ := range edges {
		for j := 0; j < n; j++ {
			if i == j || random.Float32() < 0.75 {
				continue
			}
			edges = append(edges, Edge{i, j, random.Intn(MAX_DELAY)})
		}
	}

	sort.Sort(Edges(edges))
	return 
}

func solve(n int, edges []Edge) int {
	set := new(TreeSet)
	set.Init(n)

	for _, edge := range edges{
		i, j, delay := edge.From, edge.To, edge.Delay

		if set.Size == 1 {
			return delay
		}

		set.Merge(i, j)
	}

	return -1
}

func main() {
	random := rand.New(rand.NewSource(43))

	for it := 0; it < N; it++ {
		n, edges := initialize(random)
		fmt.Println(solve(n, edges))
	}
}