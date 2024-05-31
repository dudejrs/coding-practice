import {readFileSync} from 'fs'

function solve(k) {
	return (k + 1).toString(2).replaceAll('1', '7').replaceAll('0', '4').slice(1)
}

(function main(){
	let [tc, ...data] = readFileSync('./data/4와_7.txt', {encoding : 'utf-8'}).split("\n")
	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const k = parseInt(data[cur ++].trim())
		const answer = parseInt(data[cur++].trim())

		console.log(answer, solve(k))
	}
})()
