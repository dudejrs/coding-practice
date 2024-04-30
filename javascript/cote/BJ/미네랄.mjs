import {readFileSync} from 'fs'

const [R, C] = [100, 100]
const N = 100

class Game {
	constructor(map) {
		this._map = map.map(row => row.split(""))
		this.ylim = map.length
		this.xlim = map[0].length
	}

	static directions = [[-1, 0], [0, -1], [1, 0], [0, 1]]

	takeTurn(direction, height) {

		this.#throwStick(direction, height)
		const point = this.#clusterInAir()

		if (point.join("") !== [-1, -1].join("")) {
			this.#gravity(...point)
		}
	}

	#throwStick(direction, height) {
		const point = this.#find(direction, this.ylim - height)

		if (point.join("") !== [-1, -1].join("")){
			const [y, x] = point
			this._map[y][x] = "."
		}
	}

	#find(direction, height) {
		if (direction) {
			for (let i = 0; i < this.xlim; i++) {
				if (this._map[height][i] === "x") {
					return [height, i]
				}
			}
		} else {
			for (let i = this.xlim - 1; i >=0; i--) {
				if(this._map[height][i] === "x") {
					return [height, i]
				}
			}
		}

		return [-1, -1]
	}

	#clusterInAir() {
		const visited = new Array(this.ylim).fill(0)
			.map(_ => new Array(this.xlim).fill(false))

		for (let i = this.ylim - 1; i >= 0; i--) {
			for (let j = this.xlim - 1; j >= 0; j--) {
				if (!visited[i][j] && this._map[i][j] === "x" ) {
					if (i < this.ylim - 1) {
						this.#bfs(i, j, visited, true)
						return [i, j]
					}
					this.#bfs(i, j, visited)
				}
			}
		}

		return [-1, -1]
	}

	#bfs(oy, ox, visited, mark = false){
		const queue = []
		queue.push([oy, ox])

		while(queue.length !== 0) {
			const [y, x] = queue.shift()
			
			if (visited[y][x]) {
				continue
			}

			visited[y][x] = true


			if (mark) {
				this._map[y][x] = "o"
			}
		
			for (let [dy, dx] of Game.directions) {
				let [ny, nx] = [y + dy, x + dx]

				if (ny < 0 || ny >= this.ylim || nx < 0 || nx >= this.xlim) {
					continue
				}

				if (this._map[ny][nx] === "x" && !visited[ny][nx]) {
					queue.push([ny, nx])
				}
			}
		}
	}

	#gravity(y, x) {
		const d = this.#distance()
		const visited = new Array(this.ylim).fill(0)
			.map(_ => new Array(this.xlim).fill(false))

		const queue = []
		queue.push([y, x])

		while (queue.length !== 0) {
			const [y, x] = queue.shift()

			if (visited[y][x]) {
				continue
			}

			this._map[y][x] = "."
			this._map[y + d][x] = "x"
			visited[y][x] = true

			for (let [dy, dx] of Game.directions) {
				let [ny, nx] = [y + dy, x + dx]

				if (ny < 0 || ny >= this.ylim || nx < 0 || nx >= this.xlim) {
					continue
				}

				if (this._map[ny][nx] === "o" && !visited[ny][nx]) {
					queue.push([ny, nx])
				}
			}
		}

	}

	#distance() {
		let ret  = this.ylim
		
		for (let y = 0; y < this.ylim; y++) {
			for (let x = 0; x < this.xlim; x++) {
				if (this._map[y][x] === "o") {
					ret = Math.min(ret, this.ylim - y - 1)

					for (let k = y + 1; k < this.ylim; k++) {
						if (this._map[k][x] === "x") {
							ret = Math.min(ret, k - y - 1)
							continue
						}
					}
				}
			}
		}

		return ret
	}

	print() {
		for (let row of this.map) {
			console.log(row)
		}
		console.log()		
	}


	get map() {
		return this._map.map(row => row.join("")).join("\n")
	}
}

function print(answer, solved) {
	solved = solved.split("\n")
	for (let i = 0; i < answer.length; i++) {
		console.log(answer[i], solved[i])
	}
	console.log()
}

function solve(map, heights) {
	const game = new Game(map)

	let direction = 1;

	for (let height of heights) {
		game.takeTurn(direction, height)

		direction ^= 1
	}

	return game.map
}

function main() {
	const data = readFileSync('data/미네랄.txt', {encoding : 'utf-8'})
		.split("\n")

	let cur = 0
	const testCases = parseInt(data[cur++])


	for (let it = 0; it < testCases; it++) {
		const [row, col] = data[cur++].split(" ").map(i => parseInt(i))
		const map = new Array(row).fill(0)
			.map(_ => data[cur++])

		const n = parseInt(data[cur++])
		const heights = data[cur++].split(" ")
			.map(i => parseInt(i))
		const answer = new Array(row).fill(0)
			.map(_ => data[cur++])

		const solved = solve(map, heights)
		print(answer, solved)
	}
}

main()