package main 

import (
	"fmt"
	"math/rand"
)

const (
	N = 10
)

func test(f func([]int)) {

	rand.Seed(43)
	a := make([]int, N)

	for i, _ := range a {
		a[i] = rand.Intn(1.5 * N)
	}

	f(a)

	fmt.Println(a)

}

func insertionSort(a []int) {

	for i := 0; i < len(a); i++ {
		j := i-1

		for {
			if j < 0 || a[j] <= a[j+1] {
				break
			}
				a[j], a[j+1] = a[j+1], a[j]
				j--
		}
	}
}

func bubbleSort(a []int) {

	for i := 0; i < len(a); i++ {
		for j := 0; j < len(a)-1; j++ {
			if a[j] > a[j+1] {
				a[j], a[j+1] = a[j+1], a[j]
			}
		}
	}
}

func selectionSort(a []int) {

	for i := 0; i < len(a); i++ {
		target := len(a) - i - 1
		max := 0

		for j := 0; j < len(a) - i; j++ {
			if a[j] > a[max] {
				max = j
			}
		}

		a[target], a[max] = a[max], a[target]
	}
}

func main () {

	test(insertionSort)
	test(bubbleSort)
	test(selectionSort)
}