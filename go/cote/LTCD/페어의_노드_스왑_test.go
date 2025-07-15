package LTCD

import (
	"slices"
	"testing"
)

func (problem 페어의_노드_스왑) getTestCases() []struct {
	input    *Node5
	expected []int
} {
	return []struct {
		input    *Node5
		expected []int
	}{
		{
			input:    problem.makeLinkedList([]int{1, 2, 3, 4}),
			expected: []int{2, 1, 4, 3},
		},
		{
			input:    problem.makeLinkedList([]int{1, 2, 3}),
			expected: []int{2, 1, 3},
		},
	}
}

func (problem 페어의_노드_스왑) test_정확도(t *testing.T, f func(input *Node5) []int) {
	testCases := problem.getTestCases()

	for _, testCase := range testCases {
		t.Run("정확도 테스트", func(t *testing.T) {
			result := f(testCase.input)
			equal := slices.Equal(testCase.expected, result)
			if !equal {
				t.Errorf("got %v, want %v", result, testCase.expected)
			}
		})
	}
}

func Test페어의_노드스왑(t *testing.T) {
	problem := new(페어의_노드_스왑)

	problem.test_정확도(t, func(input *Node5) []int {
		resultRoot := problem.solve(input)
		return problem.toInts(resultRoot)
	})

	problem.test_정확도(t, func(input *Node5) []int {
		resultRoot := problem.solve2(input)
		return problem.toInts(resultRoot)
	})

}
