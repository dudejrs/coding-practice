package main

import (
	"fmt"
	"os"
	"bufio"
	"strconv"
	"strings"
)

func token(s string) []int {
	tokens := strings.Split(strings.Trim(s, "\n"), " ")
	ret := make([]int, len(tokens))

	for i, v := range tokens {
		ret[i], _ = strconv.Atoi(v)
	}

	return ret
}

func get_degree(graph [][]int) []int {
	count := make([]int, len(graph))

	for i, row := range graph {
		count[i] = 0
		for _, cell := range row {
			if cell == 1 {
				count[i]++
			}
		}
	}

	return count
}

func search(cur, q, days, d int, graph [][]int, degree []int, cache [][]float32) float32 {

	if days == d {
		if cur == q {
			return 1
		}

		return 0
	}

	ret := &cache[cur][days]

	if *ret > -1 {
		return *ret
	}

	*ret = float32(0.)

	for i, cell := range graph[cur] {
		if cell == 1 {
			*ret += search(i, q, days +1, d, graph, degree, cache) / float32(degree[cur])
		}
	}

	return *ret
}

func solve(n, d, p int, graph [][]int, queries []int) []float32 {

	degree := get_degree(graph)
	ret := make([]float32, len(queries))

	for i, q := range queries {
		cache := make([][]float32 , n)
		for i, _ := range cache {
			cache[i] = make([]float32, d + 1)
			for j, _ := range cache[i] {
				cache[i][j] = float32(-1)
			}
		}
		ret[i] = search(p, q, 0, d, graph, degree, cache)
	}

	return ret
}

func main(){
	f, _ := os.Open("./data/두니발_박사의_탈옥.txt")
	defer f.Close()

	reader := bufio.NewReader(f)
	s, _ := reader.ReadString('\n')

	test_cases, _ := strconv.Atoi(strings.Trim(s, "\n"))

	for it := 0; it < test_cases; it++ {
		s, _ = reader.ReadString('\n')
		tokens := token(s)
		n, d, p := tokens[0], tokens[1], tokens[2]

		graph := make([][]int, n)

		for i, _ := range graph {
			s, _ = reader.ReadString('\n')
			graph[i] = token(s)
		}
		s, _ = reader.ReadString('\n')
		s, _ = reader.ReadString('\n')
		queries := token(s)

		fmt.Println(solve(n, d, p, graph, queries))
	}

}