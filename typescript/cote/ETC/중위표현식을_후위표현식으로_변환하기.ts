import {readFile} from 'fs/promises'

type Operator = "+" | "-" | "*" | "/"
type Opening = "("
type Closing = ")"

let priority : {[key in Operator | Opening | Closing] : number} = { 
	"+" : 1,
	"-" : 1,
	"*" : 2,
	"/" : 2,
	"(" : 0,
	")" : 0
}

type StackItem = Operator | Opening

function isOperator (token: string): token is Operator {
	return ["+", "-", "*", "/"].includes(token);
}

function isOpening(token: string): token is Opening {
	return token === "(";
}

function isClosing(token: string): token is Closing {
	return token === ")";
}

function solve(expression : string): string[] {
	const tokens: string[] = expression.split(" ");
	const [stack, ret] : [StackItem[], string[]]  = [[], []]

	for (let token of tokens) {
		if (isOperator(token)) {
			while (stack.length != 0) {
				let top = stack[stack.length - 1]
				if (priority[token] >= priority[top]) {
					break
				} 
				ret.push(stack.pop()!)
			}
			stack.push(token)
		} else if (isOpening(token)) {
			stack.push(token)
		} else if (isClosing(token)) {
			while (stack.length != 0) {
				let top  = stack.pop()!
				if (isOpening(top)) break;
				ret.push(top)
			}
		} else {
			ret.push(token)
		}
	}

	while (stack.length != 0) {
		ret.push(stack.pop()!)
	}

	return ret
}

async function main() {
	const lines = await readFile('data/중위표현식을_후위표현식으로_변환하기.txt', {encoding : 'utf-8'})
		.then(lines => lines.split("\n")
				.map(line => line.trim())
		);
	
	let cur : number = 0;
	const testCases = parseInt(lines[cur++]);

	for (let i = 0; i < testCases; i++) {
		const expression : string = lines[cur++];
		const answer : string[] = lines[cur++].split(" ")
		console.log(answer, solve(expression))
	}
}

main()