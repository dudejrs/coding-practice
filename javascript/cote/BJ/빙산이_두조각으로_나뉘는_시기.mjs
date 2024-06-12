import {readFileSync} from 'fs'

const [N, M] = [300, 300]

class Iceberg {

	static Directions = [[-1, 0], [0, -1], [1, 0], [0, 1]]

	constructor(data) {
		this.data = data
	}

	next() {
		const [n, m] = [this.data.length,  this.data[0].length]
		const ret = new Array(n).fill(0).map((_, i) => new Array(m).fill(0).map((_, j) => this.data[i][j]))

		for (let i = 0; i < n; i++ ){
			for (let j = 0; j < m; j++) {
				let count = 0
				
				for (let [dy, dx] of Iceberg.Directions) {
					const [ny, nx] = [i + dy, j + dx]

					if (ny < 0 || ny >= n || nx < 0 || nx >= m || this.data[ny][nx] > 0) {
						ret[i][j] = this.data[i][j]
						continue
					}
					count++
				}

				ret[i][j] = this.data[i][j] > count ? this.data[i][j] - count : 0
			}
		}

		this.data = ret
	}

	get allMelted() {
		return this.data.map(l => l.every(i => i <= 0)).every(i => i)
	}

	get chunks() {
		let count = 0 
		const [n, m] = [this.data.length,  this.data[0].length]
		const visited = new Array(n).fill(0).map(_ => new Array(m).fill(false))

		function dfs(i, j) {
			visited[i][j] = true

			for (let [dy, dx] of Iceberg.Directions) {
				const [ny, nx] = [i + dy, j + dx] 

				if (ny < 0 || ny >= n || nx < 0 || nx >= m || this.data[i][j] == 0 || visited[ny][nx]) {
					continue
				}

				dfs.call(this, ny, nx)
			}
		}

		for (let i = 0; i < n; i++) {
			for (let j = 0; j < m; j++) {
				if (this.data[i][j] > 0 && !visited[i][j]) {
					dfs.call(this, i, j)
					count ++
				}
			}
		}

		return count 
	}
}

function solve(map) {
	const iceberg = new Iceberg(map)

	let count = 0

	while (!iceberg.allMelted) {
		iceberg.next()
		count++
		
		if (iceberg.chunks > 1) {
			return count 
		}
	}

	 return 0
}

(function main() {
	const [tc, ...data] = readFileSync('./data/빙산이_두조각으로_나뉘는_시기.txt', {encoding : 'utf-8'}).split("\n").map(l => l.trim())

	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const [n, m] = data[cur++].split(" ").map(i => parseInt(i))
		const map = new Array(n).fill(0).map(_ => data[cur++].split(" ").map(i => parseInt(i))) 
		const answer = parseInt(data[cur++])
		console.log(answer, solve(map))
	}
})()