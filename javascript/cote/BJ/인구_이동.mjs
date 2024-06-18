import {readFileSync} from 'fs'

class World {

	static Directions = Object.freeze([[-1, 0], [0, -1], [0, 1], [1, 0]])

	constructor(data, l, r) {
		this.data = data
		this.n = data.length
		this.l = l
		this.r = r
	}

	next() {
		const visited = new Array(this.n).fill(0).map(_ => new Array(this.n).fill(-1))
		let group = 0
		const total = []
		const counts = []

		function visit(y, x) {
			visited[y][x] = group
			total[group] += this.data[y][x]
			counts[group] ++

			for (let [dy, dx] of World.Directions) {
				const [ny, nx] = [y + dy, x + dx]

				if (ny < 0 || ny >= this.n || nx < 0 || nx >= this.n || visited[ny][nx] != -1) {
					continue
				}

				const gap = Math.abs(this.data[y][x] - this.data[ny][nx]) 

				if (gap < this.l || gap > this.r) {
					continue
				}

				visit.call(this, ny, nx)
			}
		}

		for (let i = 0; i < this.n; i++) {
			for (let j =0; j < this.n; j++) {
				if (visited[i][j] == -1) {
					total.push(0)
					counts.push(0)
					visit.call(this, i, j)
					group++
				}
			}
		}


		for (let i = 0; i < this.n; i++) {
			for (let j = 0; j < this.n; j++) {
				const g = visited[i][j] 
				this.data[i][j] = Math.floor(total[g] / counts[g])
			}
		}
	}

	get numberOfUnion() {
			const visited = new Array(this.n).fill(0).map(_ => new Array(this.n).fill(-1))
		let group = 0
		const counts = []

		function visit(y, x) {
			visited[y][x] = group
			counts[group] ++

			for (let [dy, dx] of World.Directions) {
				const [ny, nx] = [y + dy, x + dx]

				if (ny < 0 || ny >= this.n || nx < 0 || nx >= this.n || visited[ny][nx] != -1) {
					continue
				}

				const gap = Math.abs(this.data[y][x] - this.data[ny][nx]) 

				if (gap < this.l || gap > this.r) {
					continue
				}

				visit.call(this, ny, nx)
			}
		}

		for (let i = 0; i < this.n; i++) {
			for (let j =0; j < this.n; j++) {
				if (visited[i][j] == -1) {
					counts.push(0)
					visit.call(this, i, j)
					group++
				}
			}
		}

		return counts.filter(i => i > 1).length
	}
}

// 이웃한 두 나라의 인구 차가 l이상 r 이하일 때의 인구이동이 발생할떄, 인구이동이 더이상 안발생하는 시점
function solve(l, r, populations) {
	const world = new World(populations, l, r)
	let count = 0

	while (world.numberOfUnion > 0) {
		world.next(l, r)
		count++
	}

	return count
}

(function main() {

	const [tc, ...data] = readFileSync('./data/인구_이동.txt', {encoding: 'utf-8'}).split("\n").map(l => l.trim())

	const testCass = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCass; it++) {
		const [n, l, r] = data[cur++].split(" ").map(i => parseInt(i))
		const populations = new Array(n).fill(0).map(_ => data[cur++].split(" ").map(i => parseInt(i)))
		const answer = parseInt(data[cur++])
		console.log(answer, solve(l, r, populations))
	}

})()