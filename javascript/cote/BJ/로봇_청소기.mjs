import {readFileSync} from 'fs' 

const [N, M] = [50, 50]

class Robot {

	static Directions = [[-1, 0], [0, 1], [1, 0], [0, -1]]

	constructor(i, j, d, room) {
		this.y = i
		this.x = j
		this.d = d
		this.room = room
	}

	clean() {
		let count = 0
		
		while (true) {
			if(this.room.isDirty(this.y, this.x)) {	
				this.room.clean(this.y, this.x)
				count++
			}

			let cleanableAround = false

			for (let i = 0; i < 4; i++) {
				this.rotate()	
				const [dy, dx] = Robot.Directions[this.d]
				const [ny, nx] = [this.y + dy, this.x + dx]

				if (this.room.isDirty(ny, nx)) {
					this.forward(dy, dx)
					cleanableAround = true
					break
				}
			}

			if (cleanableAround) {
				continue
			}

			const [dy, dx] = Robot.Directions[this.d]
			const [ny, nx] = [this.y - dy, this.x - dx]

			if (!this.room.isMovable(ny, nx)) {
				break
			}

			this.backward(dy, dx)
		}

		return count
	}

	rotate() {
		this. d = (4 + this.d - 1) % 4
	}

	forward(dy, dx) {
		this.y += dy
		this.x += dx 
	}

	backward(dy, dx) {
		this.y -= dy
		this.x -= dx
	}

}

class Room {

	static Dirty = 0
	static Wall = 1
	static Clean = 2

	constructor(data) {
		this.map = data
		this.ylim = data.length
		this.xlim = data[0].length
	}

	isDirty(i, j) {

		return this.map[i][j] == Room.Dirty
	}

	isMovable(i, j) {
		if (i < 0 || i >= this.ylim || j < 0 || j >= this.xlim) {
			return false
		}
		return this.map[i][j] != Room.Wall
	}

	clean(i, j) {
		this.map[i][j] = Room.Clean
	}

	print() {
		console.log(this.map.map(i => i.join("")).join("\n"))
		console.log()
	}
}

function solve(i, j, d, map) {
	const robot = new Robot(i, j, d, new Room(map))

	return robot.clean()
}

function main() {
	const [tc, ...data] = readFileSync('./data/로봇_청소기.txt', {encoding : 'utf-8'})
		.split("\n")

	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const [n, m] = data[cur++].split(" ").map(i => parseInt(i))
		const [i, j, d] = data[cur++].split(" ").map(i => parseInt(i))
		const map = new Array(n).fill(0)
			.map(_ => data[cur++].split(" ").map(i => parseInt(i)))
		const answer = parseInt(data[cur++])	
		console.log(answer, solve(i, j, d, map))
	}
}

main()