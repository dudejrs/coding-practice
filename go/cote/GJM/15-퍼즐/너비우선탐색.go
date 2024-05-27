package main

import (
	"fmt"
	"math/rand"
	"container/list"
)

const (
	TEST_CASES = 10
	MAX_ANSWER = 30
)

var FINISHED = [4][4]int{{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,0}}
var DIRECTIONS = [4][2]int{{-1, 0}, {1, 0}, {0, 1}, {0, -1}} 

type State struct {
	Board [4][4]int
	Current [2]int 
}

func (s State) Next() []State {
	ret := make([]State, 0)
	y, x := s.Current[0], s.Current[1]

	for _, d := range DIRECTIONS {
		dy, dx := d[0], d[1]
		ny, nx := y + dy, x + dx 

		if ny < 0 || ny >= 4 || nx < 0 || nx >= 4 {
			continue
		}

		nextState := new(State)
		
		for i, _ := range nextState.Board {
			for j, _ := range nextState.Board[i] {
				nextState.Board[i][j] = s.Board[i][j]
			}
		}

		nextState.Board[ny][nx], nextState.Board[y][x] = nextState.Board[y][x], 
		nextState.Board[ny][nx]

		nextState.Current = [2]int {ny, nx}

		ret = append(ret, *nextState)
	}

	return ret
}

func (s State) IsFinished() bool {

	for i, row := range s.Board {
		for j, cell := range row {
			if cell != FINISHED[i][j] {
				return false 
			}
		}
	}

	return true
}

func initiailize(random *rand.Rand) [4][4]int {
	ret := [4][4]int{}

	for i := 0; i < 4; i++ {
		for j := 0; j < 4; j++ {
			ret[i][j] = FINISHED[i][j]
		}
	}

	count := random.Intn(MAX_ANSWER - 3) + 3
	current := [2]int{3, 3}
	for {
		if count < 0  {
			break
		}

		y, x := current[0], current[1]
		
		r := random.Intn(4)

		for i := r; i < r + 4; i++ {
			d := DIRECTIONS[i % 4]
			ny, nx := y + d[0], x + d[1]

			if ny < 0 || ny >= 4 || nx < 0 || nx >= 4 {
				continue
			}

			ret[y][x], ret[ny][nx] = ret[ny][nx], ret[y][x]
			current[0], current[1] = ny, nx
			break
		}
		count--
	}

	return ret
}

func getCurrent(board [4][4]int)[2]int {
	for i, row := range board {
		for j, cell := range row {
			if cell == 0 {
				return [2]int{i, j}
			}
		}
	}
	return [2]int{-1, -1}
}

func solve(board [4][4]int) int {
	costs := make(map[State]int)
	q := list.New() 
	
	s := State{board, getCurrent(board)}
	if s.IsFinished() {
		return 0
	}
	q.PushBack(s)
	costs[s] = 0
	
	for {
		if q.Len() == 0 {
			break
		}
		cur := q.Front().Value.(State)
		cost := costs[cur]
		q.Remove(q.Front())
		
		for _, next := range cur.Next() {
			if next.IsFinished() {
				return cost + 1
			}

			_, e := costs[next]
			if !e {
				costs[next] = cost + 1
				q.PushBack(next)
			}
		} 
	}

	return -1
}

func main() {
	random := rand.New(rand.NewSource(43))

	for it := 0; it < TEST_CASES; it++ {
		fmt.Println(solve(initiailize(random)))
	}
}