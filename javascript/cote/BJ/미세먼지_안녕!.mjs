import {readFileSync} from 'fs'

const [N, M, T] = [50, 50, 1000]

class Position {
	constructor(y, x) {
		this.y = y
		this.x = x
	}
}

class AirPurifier {

	static CLOCK_WISE = Object.freeze([[0, 1], [1, 0], [0, -1], [-1, 0]])
	static COUNTER_CLOCK_WISE = Object.freeze([[0, 1], [-1, 0], [0, -1], [1, 0]])

	constructor(room, position, direction) {
		this.room = room
		this.position = position
		this.direction = direction
	}

	purify() {
		let cur = {y : this.position.y, x : this.position.x}
		let tmp = 0
		for (let [dy, dx] of this.direction) {
			const lim = (dy == 0) ? this.width : this.height
			for (let i = 0; i < lim - 1 ; i++) {
				let next = this.room.get(cur.y + dy, cur.x + dx)
				this.room.set(cur.y + dy, cur.x + dx, tmp)
				tmp = next
				cur.x += dx
				cur.y += dy
			}
		}
		this.room.clean(cur.y, cur.x)

	}
	get width() {
		return this.room.width
	}

	get height() {
		return (this.direction == AirPurifier.COUNTER_CLOCK_WISE) ? this.position.y + 1 : this.room.height - this.position.y 
	}
}

class Room {

	static Direction = [[-1, 0], [1, 0], [0, -1], [0, 1]]

	constructor(data){
		this.data = data
		this.height = data.length
		this.width = data[0].length
	}
	
	next(){
		const ret = new Array(this.height).fill(0).map(_ => new Array(this.width).fill(0))

		for (let i = 0; i < this.height; i++) {
			for (let j = 0; j < this.width; j++) {
				
				if (this.data[i][j] === -1) {
					ret[i][j] = -1
					continue
				}
				
				if (this.data[i][j] === 0) {
					continue
				}

				const unit = Math.floor(this.data[i][j] / 5)
				let rest = this.data[i][j]

				for (let [dy, dx] of Room.Direction) {
					const [ny, nx] = [i + dy, j + dx]
					if (ny < 0 || ny >= this.height || nx < 0 || nx >= this.width || this.data[ny][nx] === -1) {
						continue
					}
					ret[ny][nx] += unit
					rest -= unit
				}
				ret[i][j] += rest
			}
		}
		this.data = ret
	}

	get(y, x) {
		return this.data[y][x]
	}

	set(y, x, dust) {
		this.data[y][x] = dust
	}

	flow(y, x, dy, dx) {
		this.data[y + dy][x + dx] = this.data[y][x] 
	}

	clean(y, x)  {
		this.data[y][x] = -1
	}

	print() {
		console.log(this.data.map(l => l.join("")).join("\n"), "\n")
	}

	get totalAmountOfDust() {
		return this.data.map(l => l.filter(i => i > 0).reduce((acc, d) => acc + d, 0)).reduce((acc, l) => acc + l, 0)
	}
}


function refineData(data) {
	const p = data.findIndex(r => r[0] === -1)
	const room = new Room(data)
	const ap1 = new AirPurifier(room, new Position(p, 0), AirPurifier.COUNTER_CLOCK_WISE)
	const ap2 = new AirPurifier(room, new Position(p + 1, 0), AirPurifier.CLOCK_WISE)

	return [room, ap1, ap2]
}

function solve(map, t) {
	const [room, ap1, ap2] = refineData(map)

	for (let i = 0; i < t; i++) {
		room.next()
		ap1.purify()
		ap2.purify()
	}

	return room.totalAmountOfDust
}

(function main() {
	const [tc, ...data] = readFileSync('./data/미세먼지_안녕!.txt', {encoding : 'utf-8'}).split("\n").map(l => l.trim())

	const testCases = parseInt(tc)

	let cur = 0
	for (let i = 0; i < testCases; i++) {
		const [n, m, t] = data[cur++].split(" ").map(i => parseInt(i))
		const map = new Array(n).fill(0).map(_ => data[cur++].split(" ").map(i => parseInt(i)))
		const answer = parseInt(data[cur++])
		console.log(answer, solve(map, t))
	}
})()