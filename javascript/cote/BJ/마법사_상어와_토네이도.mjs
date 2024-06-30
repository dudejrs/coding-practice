import {readFileSync} from 'fs'

class Grid {

	static MOVED_SAND_RATIO = Object.freeze([[0, 0, 0.02, 0, 0],
	 	[0, 0.1, 0.07, 0.01, 0], 
	 	[0.05, 0, 0, 0 ,0], 
	 	[0, 0.1, 0.07, 0.01, 0], 
	 	[0, 0, 0.02, 0, 0]])

	constructor(data){
		this.data = data
	}

	static rotate(matrix) {
		const n = matrix.length
		const ret = new Array(n).fill(0).map(_ => new Array(n).fill(0))

		for (let y = 0; y < n; y++) {
			for (let x = 0; x < n; x++) {
				const [ny, nx] = [n - 1 - x, y]
				ret[ny][nx] = matrix[y][x]
			}
		}

		return ret
	}

	moveSand(ny, nx, d, dy, dx) {
		if (ny < 0 || ny >= this.length || nx < 0 || nx >= this.length) {
			return
		}

		const n = Grid.MOVED_SAND_RATIO.length
		const before = this.data[ny][nx]
		
		let ratio = Grid.MOVED_SAND_RATIO
		while (d > 0) {
			ratio = Grid.rotate(ratio)
			d--
		}

		let total = 0
		for (let i = 0; i < n; i++) {
			for (let j = 0; j < n; j++) {
				const [y, x] = [ny + i - 2, nx + j -2]
				const moved = Math.floor(this.data[ny][nx] * ratio[i][j])

				if (moved == 0) {
					continue
				}

				total += moved
				
				if (y < 0 || y >= this.length || x < 0 || x >= this.length) {
					continue
				}

				this.data[y][x] += moved
			}
		}
		this.data[ny][nx] = 0
		const [y, x] = [ny + dy, nx + dx]
		if (y < 0 || y >= this.length || x < 0 || x >= this.length) {
			return
		}
		this.data[y][x] += before - total
		return
	}

	get sum() {
		return this.data.map(row => row.reduce((acc, sand) => acc + sand), 0).reduce((acc, sand) => acc + sand, 0)
	}

	get length() {
		return this.data.length
	}
}

class Tornado {
	static Directions = [[0, -1], [1, 0], [0, 1], [-1, 0]]

	constructor(grid, y, x, d = 0, speed = 2) {
		this.grid = grid
		this.y = y
		this.x = x
		this.d = d
		this.speed = speed
	}

	static of(grid) {
		const mid = Math.floor((grid.length - 1) / 2) 
		const [y, x] = [mid, mid]

		return new Tornado(grid, y, x)
	}

	static nextDirection(d) {
		return (d + 1) % Tornado.Directions.length
	}

	static nextPosition(p, dp, speed) {
		return p + dp
	}

	*next() {
		while(!this.finished) {
			for (let i = 0; i < Math.floor(this.speed / 2); i++) {
				this.#move()
				this.grid.moveSand(this.y, this.x, this.d, ...Tornado.Directions[this.d])
				if (!this.finished) {
					yield this
				}
			}
			this.#increment()
		}

		return
	}

	#move() {
		const [dy, dx] = Tornado.Directions[this.d]
		this.y = Tornado.nextPosition(this.y, dy, this.speed)
		this.x = Tornado.nextPosition(this.x, dx, this.speed)
	}	

	#increment() {
		this.d = Tornado.nextDirection(this.d)
		this.speed++
	}

	get finished() {
		return this.y < 0 || this.y >= this.grid.length || this.x < 0 || this.x >= this.grid.length
	}
}

function solve(data) {
	const grid = new Grid(data) 
	const start = grid.sum
	const tornado = Tornado.of(grid)

	for (const state of tornado.next()) {
		//do nothing
	}
	return start - grid.sum
}

(function main() {
	const [tc, ...data] = readFileSync('./data/마법사_상어와_토네이도.txt', { encoding : 'utf-8'}).split("\n").map(l => l.trim())

	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const n = parseInt(data[cur++])
		const grid = new Array(n).fill(0).map(_ => data[cur++].split(" ").map(i => parseInt(i)))
		const answer = parseInt(data[cur++])
		console.log(answer, solve(grid))
	}
})()