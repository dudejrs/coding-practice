import {readFile} from 'fs/promises'

function search(i, n, picked, notChoosed, result) {
	if (picked.length == n) {
		result.push(picked)
		return
	}
	if (i == notChoosed.length) {
		return
	}

	search(i+1, n, [...picked], notChoosed, result)
	search(i+1, n, [notChoosed[i], ...picked], notChoosed, result)
}

function solve(toppings, n, picked) {
	const choosed = new Set(picked)
	const notChoosed = toppings.filter(t => !choosed.has(t))
	const result = []
	search(0, n, picked, [...notChoosed], result)
	return result
}


const lines = await readFile('data/포케리스트.txt', {encoding : 'UTF-8'})
	.then(lines => lines.split("\n")
		.map(line => line.trim()))

const toppings = lines[0].split(" ")
let testcases = parseInt(lines[1])

let cur = 2
while (testcases > 0){
	const numberOfToppings = parseInt(lines[cur++])
	const picked = lines[cur++].split(" ")
		.flatMap(t => t ? [t] : [])
	console.log(solve(toppings, numberOfToppings, picked)) 
	testcases--
}

