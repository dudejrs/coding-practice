package LTCD

import (
	"fmt"
	"math/rand"
	"container/list"
)

// const (
// 	TEST_CASE = 10
// 	N = 4
// )

// var brackets = [...]rune{'(',')','[',']','{','}'}
// var closed = map[rune]rune {
// 	'(' : ')',
// 	'[' : ']',
// 	'{' : '}'}


type 유효한_괄호 struct {
	TEST_CASE int
	N int
	brackets []rune
	closed map[rune]rune
}


func (problem *유효한_괄호) generate(random *rand.Rand) string {

	b := make([]rune, problem.N)

	for i, _ := range b {
		j := random.Intn(len(problem.brackets))
		b[i] = 	problem.brackets[j]
	}

	return string(b)
}

func (problem *유효한_괄호) solve(s string) bool {

	stack := list.New()

	for _, v := range s {
		switch v {
			case '(', '{', '[' :
				stack.PushBack(problem.closed[v])
			case ')', '}',']' :
				if stack.Len() == 0 || stack.Back().Value != v {
					return false
				}
				stack.Remove(stack.Back())
		}
	}

	return stack.Len() == 0
}

func (problem *유효한_괄호) main() {
	random := rand.New(rand.NewSource(15));
	
	for it := 0; it < problem.TEST_CASE; it++ {

		s := problem.generate(random)
		fmt.Println(problem.solve(s))
	}
}