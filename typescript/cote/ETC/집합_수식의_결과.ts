import {readFile} from 'fs/promises'

type Value = Set<string>
type Operator = "+" | "-" | "*" | "/"
type Opening = "("
type Closing = ")"
type Token = Value | Operator | Opening | Closing;
type StackItem = Operator | Opening | Closing;

const priority : {[key in StackItem] : number} = {
	"+" : 1,
	"-" : 1,
	"*" : 1,
	"/" : 1,
	"(" : 0,
	")" : 0
}

function isOperator(token: string) :token is Operator {
	return ["+", "-", "*", "/"].includes(token);
}

function isOpening(token: string) :token is Opening {
	return token === "(";
}

function isClosing(token: string) :token is Closing {
	return token === ")";
}

function tokenize(expression: string): Token[] {
	const tokens : string[] = expression.split(" ")
	const [stack, ret] : [StackItem[], Token[]] = [[],[]]

	for (let i = 0; i < tokens.length; i++) {
		let token = tokens[i]

		if(isOperator(token)) {
			while (stack.length != 0 ) {
				let top  = stack[stack.length - 1];
				if(priority[token] > priority[top]) {
					break
				}
				ret.push(stack.pop()!)
			}
			stack.push(token)
		} else if (isOpening(token)) {
			stack.push(token)
		} else if (isClosing(token)) {
			while(stack.length != 0) {
				let top  = stack.pop()!;
				if (isOpening(top)) {
					break;
				}
				ret.push(top)
			}
		} else {
			if (token !== "{") throw new Error(token);
			i++
			let set : Value = new Set();
			while (tokens[i] !== "}") {
				set.add(tokens[i])
				i++;
			}
			ret.push(set)
		}
	}

	while (stack.length != 0) {
		ret.push(stack.pop()!)
	}

	return ret
}

function evaluate(tokens : Token[]): Value {
	const stack : Value[] = []	

	for (let token  of tokens) {
		if (isOperator(<string> token)) {
			let rVal = stack.pop()! as Set<string>
			let lVal = stack.pop()! as Set<string>

			switch(token) {
				case "+": {
					for (let item of rVal){
						lVal.add(item)
					}
					stack.push(lVal)
					continue;
				}
				case "-": {
					for (let item of rVal) {
						lVal.delete(item)
					}
					stack.push(lVal)
					continue;
				}
				case "*": {
					let newVal = new Set(lVal)

					for (let item of newVal) {
						if (!rVal.has(item)){
							newVal.delete(item)
						}
					}
					stack.push(newVal)
					continue;
				}
				case "/": {
					let newVal = new Set(lVal)

					for (let item of rVal) {
						if (newVal.has(item)) {
							newVal.delete(item)
						} else {
							newVal.add(item)
						}
					}

					stack.push(newVal)
					continue;
				}
			}

		} else {
			stack.push(<Value>token)
		}
	}

	return stack[stack.length - 1]
}

function solve(expression: string): string[] {
	const tokens: Token[] = tokenize(expression)
	return [...evaluate(tokens)]
}

async function main() {
	var cur = 0;
	const data = await readFile("data/집합_수식의_결과.txt", {encoding : "utf-8"})
		.then(lines => lines.split("\n")
			.map(line => line.trim()));

	const testCases = parseInt(data[cur++]);

	for (let i = 0; i < testCases; i++) {
		const expression = data[cur++];
		const answer = data[cur++].split(" ");

		console.log(answer, solve(expression))
	}
}

main()