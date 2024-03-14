import {readFile} from 'fs/promises'

const TEST_CASES = 10
const MAX_NUMBER_LENGTH = 10000000

function solve(number, k) {
	const stack = []

	for (let c of number){
		while (k > 0 && !(stack.length == 0)) {
			if (parseInt(stack[stack.length - 1]) >= parseInt(c)) {
				break
			}
			stack.pop()
			k--
		}
		stack.push(c)
	}

	while (k > 0) {
		stack.pop()
		k--
	}

	return stack.join("")
}

const data = await readFile("data/큰_수_만들기.txt", {encoding : "utf-8"})
	.then(lines => lines.split("\n").map(line => line.trim()))

const testCases = data[0]
let cur = 1

for(let it = 0; it < testCases; it++) {
	const number = data[cur++]	
	const k = parseInt(data[cur++])
	const answer = parseInt(data[cur++])

	console.log(solve(number, k), answer)
}

for (let it = 0; it < TEST_CASES; it++) {
	const n = Math.floor(Math.random() * MAX_NUMBER_LENGTH - 1) + 1
	const number = new Array(n).fill(0)
		.map(i => Math.floor(Math.random() * 10))
		.join("")

	const k = Math.floor(Math.random() * n)

	console.log(solve(number, k))
}