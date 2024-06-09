import {readFileSync} from 'fs'

const [N, M, K] = [50, 50, 6]
const MAX_VALUE = 100

class Matrix {

	static Directions = Object.freeze([[0,1], [1,0], [0,-1], [-1,0]])

	constructor(data, operations) {
		this.data = data
		this.operations = operations
	}

	static copyOf(matrix, operations) {
		let [n, m] = [matrix.data.length, matrix.data[0].length]
		return new Matrix(new Array(n).fill(0).map((_, i) => new Array(m).fill(0).map((_,j) => matrix.data[i][j])), operations)
	}

	*next() { 
		for (let i = 0; i < this.operations.length; i++) {
			const [row, col, span] = this.operations[i]
			const operations = this.operations.slice(0, i).concat(this.operations.slice(i + 1))

			let ret = Matrix.copyOf(this, operations)

			for (let s = span; s > 0; s--) {
				let cur = {y : row - s,  x : col - s}

				for (let [dy, dx] of Matrix.Directions) {
					for (let i = 0; i < 2 * s; cur.y += dy, cur.x += dx,i++) {
						ret.data[cur.y + dy][cur.x + dx] = this.data[cur.y][cur.x]
					}
				}
			}

			yield ret
		}

		return 
	}

	get value() {
		return this.data.map(row => row.reduce((acc, a) => acc + a, 0)).reduce((acc, a) => Math.min(acc, a), Number.MAX_VALUE)
	}

	get left() {
		return this.operations.length
	}
}

function solve(matrix, operations) {
	let m = new Matrix(matrix, operations.map(v => [v[0] - 1, v[1] - 1, v[2]]))
	let ret = Number.MAX_VALUE

	function dfs(m) {
		if (m.left == 0) {
			ret = Math.min(ret, m.value)
			return
		}

		for (let next of m.next()) {
			dfs(next)
		}
	}

	dfs(m)

	return ret
}

(function main() {
	const [tc, ...data] = readFileSync('./data/배열_돌리기4.txt', {encoding : 'utf-8'}).split("\n").map(l => l.trim())

	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const [n, m, k] = data[cur++].split(" ").map(i => parseInt(i))
		const matrix = new Array(n).fill(0).map(_ => data[cur++].split(" ").map(i => parseInt(i)))
		const operations = new Array(k).fill(0).map(_ => data[cur++].split(" ").map(i => parseInt(i)))
		const answer = parseInt(data[cur++])
		console.log(answer, solve(matrix, operations))
	}

})()