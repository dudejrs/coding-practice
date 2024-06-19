import {readFileSync} from 'fs'

class Snake {

	static Direction = Object.freeze([[0, 1], [1, 0], [0, -1], [-1, 0]])
	static Clockwise = "D"
	static CounterClockwise = "L"

	constructor(board) {
		this.board = board
		this.data = [[0,0]]
		this.direction = 0
	}

	rotate(r) {
		if (r === Snake.Clockwise) {
			this.direction = (this.direction + 1) % 4
		} else {
			this.direction = (4 + this.direction - 1) % 4
		}
	}

	next() {
		const [y, x] = this.head
		const [dy, dx] = Snake.Direction[this.direction]
		const [ny, nx] = [y + dy, x + dx]

		this.data.push([ny, nx])

		if (this.isClashed) {
			return false
		}

		if (this.board.hasApple(ny, nx)) {
			this.board.clean(ny, nx)
		} else {
			this.data.shift()
		}

		return true
	}

	print() {
		const ret = new Array(this.board.height).fill(0)
			.map((_, i) => new Array(this.board.width).fill(0).map((_, j) => this.board.data[i][j]))

		for (let [y, x] of this.data) {
			if (!this.board.hits(y, x)) {
				ret[y][x] = 2
			}
		}
		console.log(ret.map(l => l.join("")).join("\n"), "\n")
	}

	get isClashed() {
		return this.data.slice(0, this.length - 1).map(l=>l.join("")).includes(this.head.join("")) || this.board.hits(...this.head)
	}

	get length() {
		return this.data.length
	}

	get head() {
		return this.data[this.length - 1]
	}
}

class Board {
	constructor(n, apples) {
		this.data = Board.apply(n, apples)
	}

	static apply(n, apples) {
		const ret = new Array(n).fill(0).map(_ => new Array(n).fill(0))

		for (let [y, x] of apples) {
			ret[y - 1][x - 1] = 1
		}

		return ret
	}

	hits(y, x) {
		// console.log(y, x)
		return y < 0 || y >= this.height || x < 0 || x >= this.width
	}

	hasApple(y, x) {
		return !this.hits(y,x) && this.data[y][x] === 1
	}

	clean(y, x) {
		this.data[y][x] = 0
	}

	get height() {
		return this.data.length
	}

	get width() {
		return this.data[0].length
	}
}

function solve(n, apples, rotations) {
	const snake = new Snake(new Board(n, apples))
	let time = 1

	while(true) {
		// console.log(time, snake.head, rotations.length)
		// snake.print()

		if (!snake.next()) {
			break
		}
		if (rotations.length > 0 && time == rotations[0][0]) {
			snake.rotate(rotations[0][1])
			rotations.shift()
		} 

		time++
	}

	return time
}

(function main() {
	const [tc, ...data] = readFileSync('./data/뱀.txt', {encoding : 'utf-8'}).split("\n").map(l => l.trim())

	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const n = parseInt(data[cur++])	
		const k = parseInt(data[cur++])
		const apples = new Array(k).fill(0).map(_ => data[cur++].split(" ").map(i => parseInt(i)))
		const l = parseInt(data[cur++])
		const rotations = new Array(l).fill(0).map(_ => data[cur++].split(" ")).map(i => [parseInt(i[0]), i[1]])
		const answer = parseInt(data[cur++])
		
		console.log(answer, solve(n, apples, rotations))
	}
})()

