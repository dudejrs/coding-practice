import {readFileSync} from 'fs'

class Result {
	static ZERO = new Result(0, 0)

	constructor(min, max) {
		this._min = min
		this._max = max
	}

	apply(other) {
		const min = Math.min(this.min, other.min)
		const max = Math.max(this.max, other.max)

		return new Result(min, max)
	}

	add(other) {
		if (other instanceof Result) {
			return new Result(this.min + other.min, this.max + other.max)
		}

		return new Result(this.min + other, this.max + other)
	}

	get min() {
		return this._min
	}

	get max() {
		return this._max
	}
}

function* tokens(num) {

	for (let l1 = 1; l1 < num.length - 1; l1++) {
		for (let l2 = l1 + 1; l2 < num.length; l2++) {
			yield [num.substring(0, l1), num.substring(l1, l2), num.substring(l2)]
		}
	}

	return
}

function count(n) {
	const numbers = n.split("").map(i => parseInt(i))

	return numbers.reduce((acc, num)=>{
		return acc + (num % 2 == 1)
	}, 0)
} 

function solve(n) {
	const cache = new Map()

	function search(n) {

		if (cache.has(n)) {
			return cache.get(n)
		}

		if (n.length == 1) {
			const k = count(n)
			cache.set(n, new Result(k, k))
			return cache.get(n)
		} 

		if (n.length == 2) {
			const k = count(n)
			const num = n.split("").map(i => parseInt(i)).reduce((a, b)=> a + b).toString()
			
			cache.set(n, search(num).add(k))

			return cache.get(n)
		}

		const k = count(n)
		let ret = new Result(Number.MAX_VALUE, 0)

		for (let t of tokens(n)) {
			const num = t.map(i => parseInt(i)).reduce((a,b)=> a + b).toString()
			ret = ret.apply(search(num))
		}

		ret = ret.add(k)

		cache.set(n, ret)
		return cache.get(n)
	}

	const result = search(n.toString())

	return [result.min, result.max]
}

(function main(){
	const [tc, ...data] = readFileSync('data/홀수_홀릭_호석.txt', {encoding : 'utf-8'}).split("\n")

	const testCases = parseInt(tc);

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const n = parseInt(data[cur++])
		const answer = data[cur++].split(" ").map(i => parseInt(i))

		console.log(answer ,solve(n))
	}
})()

