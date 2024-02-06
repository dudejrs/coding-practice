import {readFile} from 'fs/promises'


function solve(s) {

	function expand(left, right) {
		while (0 <= left && right < s.length && s[left] == s[right]){
			left--
			right++
		}

		return s.slice(left+1, right)
	}

	if (s.length < 2) {
		return ""
	}

	if (s[0] == s[s.length-1]) {
		return s
	}

	let result = ""

	for (let i = 0; i < s.length-2; i++) {
		const e1 = expand(i, i+1)
		const e2 = expand(i, i+2) 

		if (result.length < e1.length) {
			result = e1
		}

		if (result.length < e2.length) {
			result = e2
		}
	}

	return result
}

const lines = await readFile('data/가장_긴_팰린드롬_부분_문자열.txt', {encoding: 'UTF-8'})
				.then(lines => lines
								.split("\n")
								.map(line=> line.trim()))

let test_cases = parseInt(lines[0])
let i = 1;

while (test_cases > 0) {
	const s = lines[i++]
	const answer = lines[i++]
	console.log(solve(s), answer)
	test_cases--
}