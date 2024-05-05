import {readFileSync} from 'fs'

const open = ["[", "("]
const closed = { 
	"(" : ")",
	"[" : "]",
}
const value = {
	")" : 2,
	"]" : 3
}

function solve(s) {
	const bracketStack = []
	const expressionStack = []
	let lastToken = ""

	for (let token of s.split("")) {
		if (open.includes(token)) {
			bracketStack.push(closed[token])
			if (lastToken !== "" && !open.includes(lastToken)) {
				expressionStack.push("+")
			} else if (lastToken !== "") {
				expressionStack.push("(")
			}
		} else if (Object.values(closed).includes(token)) {
			if (bracketStack.pop() !== token) {
				return 0
			}
			if (closed[lastToken] === token) {
				expressionStack.push(value[token])
			
			} else {
				expressionStack.push(")")
				expressionStack.push("*")
				expressionStack.push(value[token])
			}
		} else {
			return 0
		}
		lastToken = token
	}

	if (bracketStack.length !== 0) {
		return 0
	}

	return eval(expressionStack.join(""))
}

function main() {
	const [tc, ...data] = readFileSync('./data/괄호의_값.txt', {encoding: 'utf-8'})
		.split("\n")

	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const s = data[cur++]
		const answer = parseInt(data[cur++])
		console.log(answer, solve(s))
	}
}

main()