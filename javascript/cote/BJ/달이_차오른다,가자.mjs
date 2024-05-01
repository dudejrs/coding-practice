import {readFileSync} from 'fs'

const [N, M] = [50, 50]

class User {
	constructor(y, x, count = 0, item = null) {
		this.y = y
		this.x = x
		this.item = item ? new Set(item) : new Set()
		this.count = count
	}

	static convert(key) {
		return key.charCodeAt(0) - 'a'.charCodeAt(0)
	}

	acquires(key){
		if (key) {
			this.item.add(User.convert(key))
		}
	}

	owns(key) {
		return this.item.has(User.convert(key))
	}

	move(dy, dx, item) {
		const items = new Set(this.item)
		if (item) {
			items.add(User.convert(item))
		}

		return new User(this.y + dy, this.x + dx, this.count + 1, items)
	}

	toString() {
		let s = 0
		for (let v of this.item) {
			s |= (1 << v)
		}

		return `${this.y} ${this.x} ${s}`
	}
}

class Maze {
	constructor(map) {
		this.map  = map.map(l => l.split(""))
		this.ylim = map.length
		this.xlim = map[0].length
	}

	static directions = [[1,0], [0,1], [-1,0], [0, -1]]
	static doors = ['A','B','C','D','E','F']
	static items = ['a','b','c','d','e','f']

	findUser() {
		for (let i = 0; i < this.ylim; i++) {
			for (let j = 0; j < this.xlim; j++) {
				if (this.map[i][j] === "0") {
					this.map[i][j] == "."
					return new User(i, j, 0)
				}
			}
		}

		return new User(-1, -1, 0)
	}

	canExit(user) {
		const [y, x] = [user.y, user.x]
		return this.map[y][x] === "1"
	}

	*next(user) {
		const [y, x] = [user.y, user.x]

		for (const [dy, dx] of Maze.directions) {
			const [ny, nx] = [y + dy, x + dx]

			if (ny < 0 || ny >= this.ylim || nx < 0 || nx >= this.xlim) {
				continue
			}

			if (this.map[ny][nx] === "#") {
				continue
			}

			if (Maze.doors.includes(this.map[ny][nx]) && !user.owns(this.map[ny][nx].toLowerCase())) {
				continue
			}

			var item = Maze.items.includes(this.map[ny][nx]) ? this.map[ny][nx] : null

			yield user.move(dy, dx, item)
		}
	}
}


function solve(data) {
	const visited = new Map()
	const maze = new Maze(data)
	const q = []
	q.push(maze.findUser())

	while(q.length !== 0) {
		const cur = q.shift()

		if (visited.has(cur.toString())) {
			continue
		}

		visited.set(cur.toString(), true) 
	
		for (let next of maze.next(cur)) {
			if (maze.canExit(next)) {
				return next.count
			}

			q.push(next)
		}
	}

	return -1
}

function main() {

	const [t ,...data] = readFileSync('data/달이_차오른다,가자.txt', {encoding : 'utf-8'}).split("\n")

	const testCases = parseInt(t)

	let cur = 0;
	for (let it = 0; it < testCases; it++) {
		console.log(`testCases[${it}]`)
		const [n, m] = data[cur++].split(" ").map(i => parseInt(i))
		const map = new Array(n).fill(0)
			.map(_ => data[cur++])
		const answer = parseInt(data[cur++])
		console.log(answer, solve(map) )
	}
}

main()
