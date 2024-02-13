package main 

import (
	"fmt"
	"os"
	"bufio"
	"strconv"
	"strings"
)

const (
	MAX_SEARCH_STRING_LENGTH = 100
	MAX_WORD_LENGTH = 100
)

var cache = [MAX_SEARCH_STRING_LENGTH+1][MAX_WORD_LENGTH+1]int16{}

func match(a, b int, w, s string) bool {
	ret := &cache[a][b]

	if *ret != -1 {
		return (*ret == 1)
	}

	if a < len(w) && b < len(s) {
		if w[a] == '?' || w[a] == s[b] {
			if match(a+1, b+1, w,s) {
				*ret = 1
				return true
			}
			return false
		}
	}

	if a == len(w) && b == len(s) {
		return true
	}

	if a < len(w) && w[a] == '*' {
		if match(a+1, b, w, s){
			*ret= 1
			return true
		}

		if b < len(s) && match(a, b+1, w, s) {
			*ret = 1
			return true
		}
	}

	return false
}

func solve(w, s string) bool {
	
	for i, _  := range cache  {
		for j, _ := range cache[i] {
			cache[i][j] = -1
		}
	}
	
	return match(0, 0, w, s)
}

func main() {

	f, _ := os.Open("data/와일드카드.txt")
	r := bufio.NewReader(f)

	s, _ := r.ReadString('\n')

	testcases, _ := strconv.Atoi(strings.Trim(s, "\n"))

	for it := 0; it < testcases; it++ {
		
		s, _ = r.ReadString('\n')
		w := strings.Trim(s, "\n")

		s, _ = r.ReadString('\n')
		n, _ := strconv.Atoi(strings.Trim(s, "\n"))

		fmt.Printf("matched : ")
		for i := 0; i < n; i++ {
			s, _ = r.ReadString('\n') 
			word := strings.Trim(s, "\n") 

			if solve(w, word) {
				fmt.Printf("%s ", word)
			}
		}
		fmt.Println()
	}
}