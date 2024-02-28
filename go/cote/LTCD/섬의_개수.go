package main

import (
	"fmt"
	"os"
	"bufio"
	"strconv"
	"strings"
)

func dfs(y, x int, grid [][]int) {

	if y < 0 || y >= len(grid) || x < 0 || x >= len(grid[0]) {
		return
	} 

	if grid[y][x] != 1 {
		return 
	}

	grid[y][x] = 0 

	dfs(y-1, x, grid)
	dfs(y, x-1, grid)
	dfs(y, x+1, grid)
	dfs(y+1, x, grid)

	return
}

func solve(grid [][]int) int {
	count := 0

	for i, _ := range grid {
		for j, v := range grid[i] {
			if v == 1 {
				dfs(i, j, grid)
				count++
			}
		}
	}

	return count
}

func main() {
	f, _ := os.Open("data/섬의_개수.txt")
	reader := bufio.NewReader(f)
	s, _ := reader.ReadString('\n')
	testcases, _ :=  strconv.Atoi(strings.Trim(s, "\n"))
	
	for it := 0; it < testcases; it++ {
		s, _ = reader.ReadString('\n')
		tokens := strings.Split(strings.Trim(s, "\n"), " ")
		nums := make([]int, 2)

		for i, v := range tokens {
			n, _ := strconv.Atoi(v)
			nums[i] = n
		}

		grid := make([][]int, nums[0])

		for i, _ := range grid {
			s, _ = reader.ReadString('\n')
			row := strings.Split(strings.Trim(s, "\n"), "") 

			grid[i] = make([]int, nums[1])

			for j, _ := range grid[i] {
				n, _ := strconv.Atoi(row[j])
				grid[i][j] = n
			}
		}

		s, _ = reader.ReadString('\n')
		answer, _ := strconv.Atoi(strings.Trim(s, "\n"))

		fmt.Println(answer, solve(grid))
	}
}