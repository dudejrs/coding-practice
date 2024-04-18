import {readFile} from 'fs/promises'

function shiftType(type, name, additional) {
	const pattern = /[&*]|\[\]/g

	let tokens = additional.match(pattern) 
	tokens = tokens ? tokens.toReversed() : []

	return `${type}${tokens.join('')} ${name};`
}

function solve(declaration){
	const ret = []
	const first = /([a-zA-Z]+[&\[\]*]*)\s+([a-zA-Z]+)([&\[\]*]*)/
	const others = /\s([a-zA-Z]+)([&\[\])*]*)/

	const variables = declaration.split(",")

	const [_, type, name, additional]= variables[0].match(first)
	ret.push(shiftType(type, name, additional))
	
	for (let variable of  variables.splice(1)) {
		const [_, name, additional] = variable.match(others)
		ret.push(shiftType(type, name, additional))
	}

	return ret
}

async function main() {
	const data = await readFile('./data/iSharp.txt', {encoding : 'utf-8'})
		.then(lines => lines.split("\n").map(line => line.trim()))

	let cur = 0;
	const testCases = parseInt(data[cur++])

	for (let it = 0; it < testCases; it++) {
		const declaration = data[cur++];

		const answer = new Array(parseInt(data[cur++])).fill(1)
			.map(_ => data[cur++])
		console.log(solve(declaration), answer)
	}
}

main()
