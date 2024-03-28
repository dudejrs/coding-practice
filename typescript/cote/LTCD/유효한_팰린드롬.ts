import {readFile} from "fs/promises"

function solve(s : string): boolean {
	const reg = /[^a-zA-Z]/g
	s = s.replaceAll(reg, "")
		.toLowerCase()

	let [lo, hi] = [0, s.length - 1]

	while (lo < hi) {
		if (s[lo] != s[hi]) {
			return false
		}

		lo++; hi--
	}

	return true
}

async function main() {

	const data = await readFile('data/유효한_팰린드롬.txt', {encoding : 'utf-8'})
		.then(lines => lines.split("\n").map(
				line => line.trim()))

	let cur = 0
	const testCases = parseInt(data[cur++])

	for (let it = 0; it < testCases; it++) {
		console.log(solve(data[cur++]))
	}
}

main()