package main 

import (
	"fmt"
	"os"
	"bufio"
	"strconv"
	"strings"
)

var convertTypes = [4][3][2]int{
	{{0,0},{0,1},{1,0}},
	{{0,0},{0,1},{1,1}},
	{{0,0},{1,0},{1,1}},
	{{0,0},{1,0},{1,-1}}} 


func getLimit(s string) (int, int) {

	tokens := strings.Split(s, " ")
	ret := []int{}

	for _, token := range tokens {
		v, _ := strconv.Atoi(token)
		ret = append(ret, v)
	}

	return ret[0], ret[1]
}

func getBoard(reader *bufio.Reader, ylim, xlim int) [][]int {
	
	ret := make([][]int, ylim)

	for i :=0; i<ylim; i++ {
		ret[i] = make([]int, xlim)
	}

	for i :=0; i<ylim; i++ {
		s, _ := reader.ReadString('\n')
		s = strings.Trim(s, "\n")

		for j, char := range s {
			if j >= xlim {
				break
			}

			switch char {
				case '.' :
					ret[i][j] = 0
				case '#' :
					ret[i][j] = 1
				default :
					//do nothing
			}
		}
	}

	return ret
}

func set(board [][]int, y, x, ylim, xlim int, type_ [3][2]int, delta int) bool {

	ret := true

	for _, coord := range type_ {
		dy, dx	:= coord[0], coord[1]
		ny, nx := y+dy, x+dx
			
		
		if ny < 0 || ny >= ylim || nx < 0 || nx >= xlim	 {
			ret = false
			continue	
		} 

		board[ny][nx] += delta

		if board[ny][nx] > 1 {
			ret = false
		}
		
	}

	return ret
}

func solve(board [][]int, ylim, xlim int) int {

	y, x := -1, -1

	for i:=0; i<ylim; i++ {
		for j:=0; j<xlim; j++ {
			if board[i][j] == 0 {
				y, x = i, j
				break;
			}
		}

		if y != -1 {
			break
		}
	}

	if y == -1 {
		return 1
	}

	ret := 0

	for _, t := range convertTypes {
		
		if set(board, y, x, ylim, xlim, t, 1) {
			ret += solve(board, ylim, xlim)
		}
		set(board, y, x, ylim, xlim, t, -1)

	}

	return ret
}

func main() {

	f, _ := os.Open("./data/게임판_덮기.txt");
	defer f.Close()

	reader := bufio.NewReader(f)

	s, _ := reader.ReadString('\n')
	
	testcases, _ := strconv.Atoi(strings.Trim(s, "\n"))

	for {
		if testcases == 0 {
			break
		}

		s, _ = reader.ReadString('\n')
		s = strings.Trim(s, "\n")
		
		ylim, xlim := getLimit(s)		


		board := getBoard(reader, ylim, xlim)
		fmt.Println(solve(board, ylim, xlim))


		testcases--
	}
}