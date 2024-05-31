import {readFileSync} from 'fs'

function solve(relation) {
	const [n, m] = [relation.length, relation[0].length]

	function isIndentifiable(key) {
		const values = new Set()

		for (let r of relation) {
			let val = r.filter((_, i) => key.includes(i))
			if (values.has(val.join(" "))) {
				return false
			}
			values.add(val.join(" "))
		}

		return true;
	} 

	function isUnique(key) {
		for (let cand of candidates.values()) {
			if (cand.every(c => key.includes(c))) {
				return false
			}
		}

		return true;
	}	

	let count = 0
	const queue =[]
	const candidates = new Set()
	queue.push([0, []])

	while (queue.length > 0) {
		let [cur, key] = queue.shift()

		if (isIndentifiable(key)) {
			if (isUnique(key)) {
				candidates.add(key)
				count++
			}
			continue
		}

		for (let i = cur; i < m; i++) {
			queue.push([i + 1, [...key, i]])
		}
	}
	

	return count
}

(function main() {
	const [tc, ...data] = readFileSync('./data/후보키.txt', {encoding : 'utf-8'}).split("\n")

	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const n = parseInt(data[cur++])
		const relation = new Array(n).fill(0).map(_ => data[cur++].split(" "))
		const answer = parseInt(data[cur++])
		console.log(answer, solve(relation))
	}	
})()