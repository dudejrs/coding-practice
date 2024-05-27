import {readFileSync} from 'fs'

const [N, T, M] = [16, 1000, 100]

function solve(n, t, m, p) {
	let str = '';
    for (let i = 0; str.length <= m * t; i++){
        str += i.toString(n).toUpperCase();
    } 
    return [...str].filter((_, i) => i % m === p-1).slice(0, t).join('');
}

(function main() {
	const [tc, ...data] = readFileSync("./data/n진수_게임.txt", {encoding : 'utf-8'}).split("\n")
	const testCases = parseInt(tc);

	let cur = 0;
	for (let i = 0; i < testCases; i++) {
		let [n, t, m, p] = data[cur++].split(" ")
		let answer = data[cur++]
		console.log(answer, solve(n, t, m, p))
	}

})()