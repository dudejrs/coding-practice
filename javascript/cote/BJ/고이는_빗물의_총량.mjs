import {readFileSync} from 'fs'

const [H, W] = [500, 500];

Object.defineProperty(Array.prototype, Symbol.for("top"), {get :function(){
		return this.at(this.length - 1)
	}
})

function solve(heigths) {
	const stack = []

	let volumne = 0

	for (let i = 0; i < heigths.length; i++) {
		while (stack.length != 0 && heigths[stack[Symbol.for("top")]] < heigths[i]) {
			let top = stack.pop()

			if (stack.length == 0) {
				break
			}

			const distance = i - stack[Symbol.for("top")] - 1
			const h = Math.min(heigths[stack[Symbol.for("top")]], heigths[i]) - heigths[top]
			volumne += distance * h
		}

		stack.push(i)
	}

	return volumne
}

(function main(){
	const [tc, ...data] = readFileSync('./data/고이는_빗물의_총량.txt', {encoding: "utf-8"}).split("\n");

	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const [h, w] = data[cur++].split(" ").map(i => parseInt(i))
		const heigths = data[cur++].split(" ").map(i => parseInt(i))
		const answer = parseInt(data[cur++])
		console.log(answer, solve(heigths))
	}
})()

