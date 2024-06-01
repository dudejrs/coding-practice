import {readFileSync} from 'fs'

function key(y, x) {
	return [y, x].join(" ")
}

class Grid {
	static Diagonals = [[-1, -1],[-1, 1], [1, -1], [1, 1]]

	constructor(data) {
		this.n = data.length
		this.data = data
	}

	static check(y, x, n) {
		if (y < 0 || y >= n || x < 0 || x >= n) {
			return false
		}
		return true		
	}

	fill(y, x , amount) {
		this.data[y][x] += amount
	}

	getNumberOfDiagonal(y, x) {
		let count = 0

		for (let [dy, dx] of Grid.Diagonals) {
			const [ny, nx] = [y + dy, x + dx]

			if (Grid.check(ny, nx, this.n) && this.data[ny][nx] > 0) {
				count++
			}
		}

		return count
	}

	isCreatable(y, x) {
		return this.data[y][x] >= 2
	}

	get total() {
		return this.data.map(row => row.reduce((a, b) => a + b, 0))
			.reduce((a,b) => a + b, 0)
	}
}

class Cloud {
	constructor(y, x) {
		this.y = y
		this.x = x
	}
}

class CloudMap {
	static Directions = Object.freeze([[0, -1],[-1, -1], [-1, 0], [-1, 1], [0, 1], [1, 1], [1, 0], [1, -1]])
	
	constructor(n, data) {
		this.n = n
		this.data = new Map() 
	}

	static DEFAULT(n){
		const ret =  new CloudMap(n)

		const a = [new Cloud(n - 2, 0), new Cloud(n-2, 1), new Cloud(n-1, 0), new Cloud(n-1, 1)]

		a.forEach(v => ret.data.set(key(v.y, v.x), v))

		return ret
	}

	move(d, s) {
		const next = new Map()

		const [dy, dx] = CloudMap.Directions[d - 1]

		for (let cloud of this.data.values()) {
			const {y, x} = cloud
			const ny = (this.n * 51 + y + dy * s) % this.n
			const nx = (this.n * 51 + x + dx * s) % this.n
			cloud.y = ny
			cloud.x = nx
			next.set(key(ny, nx), cloud)
		}	

		this.data = next
	}

	rainOn(grid) {
		const ret = []

		for (let {y, x} of this.data.values()) {	
			grid.fill(y, x, 1)
			ret.push([y, x])
		}

		return ret
	}

	createFrom(grid, spots) {
		const prev = this.data
		this.data = new Map()

		for (let y = 0; y < this.n; y++) {
			for (let x = 0; x < this.n; x++) {
				if (prev.has(key(y, x))) {
					continue
				}

				if (grid.isCreatable(y, x)) {
					this.data.set(key(y,x), new Cloud(y, x))
					grid.fill(y, x, -2)
				}
			}
		}
	}
}

class Magician {
	constructor(grid) {
		this.grid = new Grid(grid)
		this.clouds = CloudMap.DEFAULT(this.grid.n)
	}

	enchant(d, s) {
		this.clouds.move(d, s)
		const spots = this.clouds.rainOn(this.grid)

		for (let [y, x] of spots) {
			const amount = this.grid.getNumberOfDiagonal(y, x)
			this.grid.fill(y, x, amount)
		}

		this.clouds.createFrom(this.grid, spots)
	}

	getTotalSumOfWater() {
		return this.grid.total
	}
}

function solve(grid, moves) {
	const magician = new Magician(grid)

	for (let [d, s] of moves) {
		magician.enchant(d, s)
	}

	return magician.getTotalSumOfWater()
}

(function main() {
	const [tc, ...data] = readFileSync('./data/마법사_상어와_비바라기.txt', {encoding : 'utf-8'}).split("\n").map(l => l.trim())

	const testCases = parseInt(tc)
	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const [n, m] = data[cur++].split(" ").map(i => parseInt(i))	
		const grid = new Array(n).fill(0)
			.map(_ => data[cur++].split(" ").map(i => parseInt(i)))
		const moves = new Array(m).fill(0)
			.map(_ => data[cur++].split(" ").map(i => parseInt(i)))
		const answer =  parseInt(data[cur++])
		console.log(answer, solve(grid, moves))
	}
}) ()