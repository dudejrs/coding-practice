import {readFile} from 'fs/promises'

const MAX = 987654321

function getPartialMatch(m){

	const pi = new Array(m.length).fill(0)

	for (let begin = 1; begin < m.length; begin++) {
		for (let i =0; i < m.length - begin; i++) {
			if (m[begin+i] != m[i]) break
			pi[begin+i] = Math.max(pi[begin+i], i+1)
		}
	}

	return pi
}

function kmpSearch(h, m) {
	const pi = getPartialMatch(m)

	let [begin, matched] = [0, 0]
	while (begin < h.length - m.length) {
		if (begin < m.length && h[begin + matched] == m[matched]) {
			matched ++
			if (matched == m.length) {
				return begin
			}
		} else {
			if (matched == 0) {
				begin++
			} else {
				begin += matched - pi[matched - 1]
				matched = pi[matched -1]
			}
		}
	}

	return MAX
}

function shift(oirignal, target){
	return kmpSearch(oirignal+oirignal, target)
}

function solve(dials){
	let ret = 0

	for (let i = 0; i < dials.length - 1; i++) {
		ret += Math.min(shift(dials[i], dials[i+1]), shift(dials[i+1], dials[i]))
	}

	return ret
}

const lines = await readFile('data/재하의_금고.txt', {encoding : 'UTF-8'})
	.then(lines => lines.split("\n")
		.map(line=> line.trim()))

let testcases = parseInt(lines[0])
let cur = 1
while (testcases > 0) {

	const dials = []
	const n = parseInt(lines[cur++])

	for(let i = 0; i <= n; i++) {
		dials.push(lines[cur++])
	}

	console.log(solve(dials))

	testcases--
}
