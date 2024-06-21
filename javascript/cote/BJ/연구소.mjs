import {readFileSync} from 'fs'

class Map_ {
	static NONE = 0
	static WALL = 1
	static VIRUS = 2

	constructor(data) {
		this.data = data
	}

	position(i) {
		const y = Math.floor(i / this.width)
		const x = i % this.width
		return [y, x]
	}

	cellNumber(y, x) {
		return y * this.width + x
	}

	*next() {
		const maximumCellNumber = this.cellNumber(this.height - 1, this.width - 1)
		
		for (let wall1 = 0; wall1 < maximumCellNumber - 1; wall1++) {
			const [y1, x1] = this.position(wall1)
			if (this.data[y1][x1] !== Map_.NONE) {
				continue
			}
			this.data[y1][x1] = Map_.WALL

			for (let wall2 = wall1 + 1; wall2 < maximumCellNumber; wall2++) {
				const [y2, x2] = this.position(wall2)
				if (this.data[y2][x2] !== Map_.NONE) {
					continue
				}
				this.data[y2][x2] = Map_.WALL

				for (let wall3 = wall2 + 1; wall3 <= maximumCellNumber; wall3++) {
					const [y3, x3] = this.position(wall3)
					if (this.data[y3][x3] !== Map_.NONE) {
						continue
					}
					this.data[y3][x3] = Map_.WALL

					yield this

					this.data[y3][x3] = Map_.NONE
				}
				this.data[y2][x2] = Map_.NONE
			}
			this.data[y1][x1] = Map_.NONE
		}


		return
	}

	get height() {
		return this.data.length
	}

	get width() {
		return this.data[0].length
	}

	get areaOfSafeZone() {
		const visited = new Array(this.height).fill(0).map(_ => new Array(this.width).fill(false))
		let area = 0
		let status = Map_.NONE

		const directions = [[-1, 0], [1, 0], [0, 1], [0, -1]]

		function dfs(y, x) {
			
			if (this.data[y][x] === Map_.WALL) {
				return 0
			}
			
			if (this.data[y][x] === Map_.VIRUS) {
				status = Map_.VIRUS
			}
			visited[y][x] = true
			let count = 1

			for (let [dy, dx] of directions) {
				const [ny, nx] = [y + dy, x + dx]

				if (ny < 0 || ny >= this.height || nx < 0 || nx >= this.width || visited[ny][nx]) {
					continue
				}

				count += dfs.call(this, ny, nx)
			}

			return count
		}

		for (let i = 0; i < this.height; i++) {
			for (let j = 0; j < this.width; j++) {
				if (!visited[i][j] && this.data[i][j] === Map_.NONE) {
					status = Map_.NONE
					let count = dfs.call(this, i, j)
					if (status != Map_.VIRUS) {
						area += count
					}
				}
			}
		}

		return area
	}
}


function solve(map) {
	const m = new Map_(map)
	let ret = 0

	for (let state of m.next()) {
		ret = Math.max(ret, state.areaOfSafeZone)
	}

	return ret
}

(function main() {

	const [tc, ...data] = readFileSync('./data/연구소.txt', {encoding : 'utf-8'}).split("\n").map(l => l.trim())

	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const [n, m] = data[cur++].split(" ").map(i => parseInt(i))
		const map = new Array(n).fill(0).map(_ => data[cur++].split(" ").map(i => parseInt(i)))
		const answer = parseInt(data[cur++])
		console.log(answer, solve(map))
	}

})()