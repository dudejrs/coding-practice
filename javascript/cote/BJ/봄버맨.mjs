import {readFileSync} from 'fs'

const [R, C, N] = [200, 200, Math.pow(10, 9)]

function compareResults(data1, data2) {
	return data1.map((row, i) => `${row.join("")}  ${data2[i].join("")}`).join("\n")
}

class Bomb {
	constructor(time = 3) {
		this.time = time
	}
}

class Grid {
	static BOMB = "O"
	static EMPTY = "."
	static Dircetions = [[-1, 0], [0, -1], [1, 0], [0, 1]]

	constructor(state, flag = false) {
		this.state = state
		this.flag = flag
	}

	static of(snapshot) {
		const state = snapshot.map(row => row.map(cell => cell === Grid.BOMB ? new Bomb() : null))
		return new Grid(state)
	}

	next() {
		this.#countDown()
		if (this.flag) {
			this.#plantBombs()
		}
		this.#explodeBombs()
		this.flag ^= true
	}

	#countDown() {
		this.state.forEach(row => row.map(cell => {
			if (cell) {
				cell.time--
			}
		}))
	}

	#plantBombs() {
		this.state = this.state.map(row => row.map(cell => cell ? cell : new Bomb()))
	}

	#explodeBombs() {
		const visited = new Array(this.height).fill(0).map(_ => new Array(this.width).fill(false))

		const dfs = (y, x) => {
			visited[y][x] = true
			if (this.state[y][x] && this.state[y][x].time != 0) {
				this.state[y][x] = null
				return
			}
			this.state[y][x] = null

			for (let [dy, dx] of Grid.Dircetions) {
				const [ny, nx] = [y + dy, x + dx]

				if (ny < 0 || ny >= this.height || nx < 0 || nx >= this.width) {
					continue
				}

				if (!visited[ny][nx] && this.state[ny][nx]) {
					dfs(ny, nx)
				}
			}
		}

		for (let i = 0; i < this.height; i++) {
			for (let j = 0; j < this.width; j++) {
				if (!visited[i][j] && this.state[i][j] && this.state[i][j].time === 0) {
					dfs(i, j)
				}
			}
		}
	}

	get width() {
		return this.state[0].length
	}

	get height() {
		return this.state.length
	}

	get snapshot() {
		return this.state.map(row => row.map(cell => cell ? Grid.BOMB : Grid.EMPTY))
	}
}

function solve(initialState, n) {
	const grid = Grid.of(initialState)

	for (let i = 0; i < n; i++) {
		grid.next()
	}

	return grid.snapshot
}

(function main() {
	const [tc, ...data] = readFileSync('./data/봄버맨.txt', {encoding : 'utf-8'}).split("\n").map(l => l.trim())

	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const [r, c, n] = data[cur++].split(" ").map(i => parseInt(i))
		const initialState = new Array(r).fill(0).map(_ => data[cur++].split(""))
		const answer = new Array(r).fill(0).map(_ => data[cur++].split(""))
		console.log(compareResults(answer, solve(initialState, n)), "\n")
	}
})()