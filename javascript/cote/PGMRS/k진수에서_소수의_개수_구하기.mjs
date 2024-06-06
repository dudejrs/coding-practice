import {readFileSync} from 'fs'

function isPrime(n) {
    if (n <= 1) {
        return false
    } 
    if (n == 2) {
        return true
    }
    if (n % 2 == 0) {
        return false
    }
    
    for (let i = 3; i <= Math.floor(Math.sqrt(n)); i += 2) {
        if (n % i == 0) {
            return false
        }
    }
    return true
}

function solve(n, k) {
    return n.toString(k).split("0")
        .filter(i => i > 1)
        .map(i => parseInt(i))
        .filter(i => isPrime(i)).length;
}

(function main() {

	const [tc, ...data] = readFileSync('./data/k진수에서_소수의_개수_구하기.txt', {encoding : 'utf-8'}).split("\n").map(l => l.trim())

	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const [n, k] = data[cur++].split(" ").map(i => parseInt(i))
		let answer = parseInt(data[cur++])
		console.log(answer, solve(n, k))
	}

})()