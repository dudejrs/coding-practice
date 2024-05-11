import {readFileSync} from 'fs'

const N = 20

class Match {
	constructor(matched = -1, empty = -1) {
		this.matched = matched
		this.empty = empty
	}

	priorTo(other) {
		if (this.matched > other.matched) {
			return true
		}

		if (this.matched == other.matched && this.empty > other.empty) {
			return true
		}

		return false
	}
}

class Classroom {
	static Adjacent = [[1, 0], [-1, 0], [0, -1], [0, 1]]
	static Satisfaction = [0, 1, 10, 100, 1000]

	constructor(n) {
		this.n = n
		this.room = new Array(n).fill(-1)
			.map(_ => new Array(n).fill(-1))
		this._favorites = new Array(n * n + 1)
	}

	match(y, x, favorite) {
		let matched = 0
		let empty = 0

		for (let [dy, dx] of Classroom.Adjacent) {
			let [ny, nx] = [y + dy, x + dx]

			if (ny < 0 || ny >= this.n || nx < 0 || nx >= this.n) {
				continue
			}

			if (this.room[ny][nx] == -1) {
				empty++
			} else if (favorite.includes(this.room[ny][nx])) {
				matched ++
			} 
		}

		return new Match(matched, empty)
	}

	assign(cur, favorite) {
		let [y, x] = [-1, -1]
		let cur_m = new Match()

		for (let i = 0; i < this.n; i++) {
			for (let j = 0; j < this.n; j++) {
				if (this.room[i][j] != -1) {
					continue
				}
				const m = this.match(i, j, favorite)

				if (m.priorTo(cur_m)) {
					cur_m = m
					y = i
					x = j
				} 
			}
		}

		if (y != -1 && x != -1) {
			this.room[y][x] = cur
		}

		this._favorites[cur] = favorite
	}

	get satisfaction() {
		let acc = 0;

		for (let i = 0; i < this.n;  i++) {
			for (let j = 0; j < this.n; j++) {
				const favorite = this._favorites[this.room[i][j]]
				const m = this.match(i, j, favorite)
				acc += Classroom.Satisfaction[m.matched]
			}
		}

		return acc
	}
}


function solve(n, favorites) {
	const classroom = new Classroom(n)

	for (let [cur, ...favorite] of favorites) {
		classroom.assign(cur, favorite)
	}

	return classroom.satisfaction
}

(function main(){

	const [tc, ...data] = readFileSync('data/상어_초등학교.txt', {encoding : 'utf-8'}).split("\n")

	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const n = parseInt(data[cur++])
		const favorites = new Array(n * n).fill(0)
			.map(_ => data[cur++].split(" ")
				.map(i => parseInt(i)))
		const answer =parseInt(data[cur++])
		console.log(answer, solve(n, favorites))
	}

})();