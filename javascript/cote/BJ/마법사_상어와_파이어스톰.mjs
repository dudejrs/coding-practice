import {readFileSync} from 'fs'

const [N, Q] = [6, 1000]
const MAX_ICE = 100

class Magician {
	constructor(grid) {
		this.grid = grid
	}

	spell(level) {
		this.#rotate(level)
		this.#iceMelts()
	}

	#rotate(level) {
		const grides = this.grid.subgridOf(level)
		const rotated = grides.map(row => row.map(grid => grid.rotate()))
		this.grid = Grid.of(rotated)
	}

	#iceMelts(){
		this.grid = this.grid.melts()
	}
}

class Grid {

	static Directions = [[-1, 0], [1, 0], [0, -1], [0, 1]]

	constructor(data) {
		this.data = data
		this.n = data.length
	}

	static of(subgrides) {
		const m = subgrides[0][0].n
		const k = subgrides.length
		const n = k * m
		const ret = new Array(n).fill(0).map(_ => new Array(n).fill(0))

		for (let i = 0; i < k; i++) {
			for (let j = 0; j < k; j++) {
				for (let a = 0; a < m; a++) {
					for (let b = 0; b < m; b++){
						const [y, x] = [i * m + a, j * m + b]
						ret[y][x] = subgrides[i][j].data[a][b]
					}
				}
			}
		}

		return new Grid(ret)
	}

	subgridOf(level) {
		const m = Math.pow(2, level)
		const k =  Math.floor(this.n / m)

		const ret = new Array(k).fill(0).map(_ => new Array(k))

		for (let i = 0; i < k; i++) {
			for (let j = 0; j < k; j++) {
				const data = new Array(m).fill(0).map((_, a) => new Array(m).fill(0).map((_, b) => this.data[i * m + a][j * m + b]))
				ret[i][j] = new SubGrid(data)
			}
		}


		return ret
	}

	melts() {
		const ret = new Array(this.n).fill(0).map((_, i) => new Array(this.n).fill(0).map((_, j) => this.data[i][j]))

		for (let y = 0; y < this.n; y++){ 
			for (let x = 0; x < this.n; x++) {
				if (this.data[y][x] == 0) {
					continue
				}

				let count = 0

				for (let [dy, dx] of Grid.Directions) {
					const [ny, nx] = [y + dy, x + dx]

					if (ny < 0 || ny >= this.n || nx < 0 || nx >= this.n || this.data[ny][nx] == 0){
						continue
					}

					count++
				}

				if (count < 3) {
					ret[y][x]--
				}
			}
		}

		return new Grid(ret)
	}

	get snapshot() {
		return this.data.map(row => row.join(" ")).join("\n")
	}

	get sum() {
		return this.data.map(row => row.reduce((acc, v) => acc + v, 0)).reduce((acc, v) => acc + v, 0)
	}

	get maxArea() {
		const visited = new Array(this.n).fill(0).map(_ => new Array(this.n).fill(false))
		let ret = 0 

		const count = (y, x) => {
			visited[y][x] = true
			
			if (this.data[y][x] == 0) {
				return 0
			}

			let ret = 1

			for (let [dy, dx] of Grid.Directions) {
				const [ny, nx] = [y + dy, x + dx]

				if (ny < 0 || ny >= this.n || nx < 0 || nx >= this.n || visited[ny][nx]) {
					continue
				}

				ret += count(ny, nx)	
			}

			return ret
		}

		for (let y = 0; y < this.n; y++) {
			for (let x = 0; x < this.n; x++) {
				if (!visited[y][x] && this.data[y][x] > 0){
					ret = Math.max(ret, count(y, x))
				}
			}
		}

		return ret
	}
}

class SubGrid {
	constructor(data) {
		this.data = data
		this.n = data.length
	}

	rotate(){
		const ret = new Array(this.n).fill(0).map(_ => new Array(this.n).fill(0))

		for (let y = 0; y < this.n; y++) {
			for (let x = 0; x < this.n; x++) {
				const [ny, nx] = [x, this.n - 1 - y]
				ret[ny][nx] = this.data[y][x]	
			}
		}

		return new SubGrid(ret)
	}
}

function solve(map, queries) {
	const grid = new Grid(map)
	const magician = new Magician(grid)

	for (const level of queries) {
		magician.spell(level)
	}
	
	return [magician.grid.sum, magician.grid.maxArea]
}

(function() {
	const [tc, ...data] = readFileSync('./data/마법사_상어와_파이어스톰.txt', {encoding : 'utf-8'}).split("\n").map(l => l.trim())

	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const [n, q] = data[cur++].split(" ").map(i => parseInt(i))
		const map = new Array(Math.pow(2, n)).fill(0).map(_ => data[cur++].split(" ").map(i => parseInt(i)))
		const queries = data[cur++].split(" ").map(i => parseInt(i))
		const answer = new Array(2).fill(0).map(_ => parseInt(data[cur++]))
		const [sumOfIce, maxAreaOfIce] = solve(map, queries)
		console.log(answer, [sumOfIce, maxAreaOfIce])
	}

})()