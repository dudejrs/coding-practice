package main

import (
	"fmt"
	"math/rand"
	"container/list"
)

const (
	TEST_CASE = 10
	N = 4
)

var brackets = [...]rune{'(',')','[',']','{','}'}
var closed = map[rune]rune {
	'(' : ')',
	'[' : ']',
	'{' : '}'}


func generate(random *rand.Rand) string {

	b := make([]rune, N)

	for i, _ := range b {
		j := random.Intn(len(brackets))
		b[i] = 	brackets[j]
	}

	return string(b)
}

func solve(s string) bool {

	stack := list.New()

	for _, v := range s {
		switch v {
			case '(', '{', '[' :
				stack.PushBack(closed[v])
			case ')', '}',']' :
				if stack.Len() == 0 || stack.Back().Value != v {
					return false
				}
				stack.Remove(stack.Back())
		}
	}

	return stack.Len() == 0
}

func main() {
	random := rand.New(rand.NewSource(15));
	
	for it := 0; it < TEST_CASE; it++ {

		s := generate(random)
		fmt.Println(solve(s))
	}
}