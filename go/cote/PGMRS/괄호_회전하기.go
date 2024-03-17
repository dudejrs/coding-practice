package main

import (
	"fmt"
	"os"
	"bufio"
	"strconv"
	"strings"
	"container/list"
)

func match(offset int, s string) bool {
	stack := list.New()
	target := []rune(s)

	for i := 0; i < len(s); i++ {
		cur := target[(offset + i) % len(s)]

		switch {
			case cur == '(' : 
				stack.PushBack(')')
			case cur == '[' :
				stack.PushBack(']')
			case cur == '{' :
				stack.PushBack('}')
			case stack.Len() == 0 :
				return false
			case cur == stack.Back().Value :
				stack.Remove(stack.Back())
			default :
				return false
		}
	}

	return stack.Len() == 0
}

func solve(s string) int {
	count := 0
	for i := 0; i < len(s); i++ {
		if match(i, s) {
			count++
		}
	}

	return count
}

func main() {
	f, _ := os.Open("data/괄호_회전하기.txt")
	r := bufio.NewReader(f)
	s, _ := r.ReadString('\n')
	testcases, _ := strconv.Atoi(strings.Trim(s, "\n"))
	
	for it := 0; it < testcases; it++ {
		s, _ = r.ReadString('\n')
		s = strings.Trim(s, "\n")
		answerString, _ := r.ReadString('\n')
		answer, _ := strconv.Atoi(strings.Trim(answerString, "\n"))
		fmt.Printf("%d %d\n", answer, solve(s))
	}
}