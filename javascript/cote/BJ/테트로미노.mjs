import {readFileSync} from 'fs'


class Tetromino {
	constructor(type, data) {
		this.type = type
		this.data = data
	}
	covers(y, x, map) {
		const [n, m] = [map.length, map[0].length]
		let acc = 0
		
		for (let [dy, dx] of this.data) {

			const [ny, nx] = [y + dy, x + dx]
			if (ny < 0 || ny >= n || nx < 0 || nx >= m) {
				return -1
			}

			acc += map[ny][nx]
		}
		return acc
	}
}

class TetrominoFactory {
	constructor() {}
	*generate() {
		throw new Error("UnSupported")
	}
}

class Type1Factory extends TetrominoFactory{
	constructor() {
		super()
	}
	*generate() {
		yield new Tetromino(0, [[0,0], [0,1], [0,2], [0,3]])
		yield new Tetromino(0, [[0,0], [1,0], [2,0], [3,0]])
		return 
	}
}

class Type2Factory extends TetrominoFactory{
	constructor() {
		super()
	}
	*generate() {
		yield new Tetromino(1, [[0,0], [0,1], [1,0], [1,1]])
		return
	}
}
class Type3Factory extends TetrominoFactory{
	constructor() {
		super()
	}
	*generate() {
		yield new Tetromino(2, [[0,0], [1,0], [0,1], [0,2]])
		yield new Tetromino(2, [[0,0], [0,1], [0,2], [1,2]])
		
		yield new Tetromino(2, [[0,0], [1,0], [1, -1], [1, -2]])
		yield new Tetromino(2, [[0,0], [1,0], [1,1], [1,2]])

		yield new Tetromino(2, [[0,0], [0,1], [1,0], [2,0]])
		yield new Tetromino(2, [[0,0], [0,1], [1,1], [2,1]])
		
		yield new Tetromino(2, [[0,0], [1,0], [2,0], [2,-1]])
		yield new Tetromino(2, [[0,0], [1,0], [2,0], [2,1]])
		return 
	}	
}
class Type4Factory extends TetrominoFactory{
	constructor() {
		super()
	}
	*generate() {
		yield new Tetromino(3, [[0,0], [0,1], [1,1], [1,2]])
		yield new Tetromino(3, [[0,0], [0,1], [1,0], [1, -1]])
		yield new Tetromino(3, [[0,0], [1,0], [1,-1], [2, -1]])
		yield new Tetromino(3, [[0,0], [1,0], [1,1], [2, 1]])

		return 
	}
}
class Type5Factory extends TetrominoFactory{
	constructor() {
		super()
	}
	*generate() {
		yield new Tetromino(4, [[0,0], [0,1], [0,2], [1,1]])
		yield new Tetromino(4, [[0,0], [1,0], [2,0], [1,-1]])
		yield new Tetromino(4, [[0,0], [1,0], [2,0], [1,1]])
		yield new Tetromino(4, [[1,-1], [1,0], [1,1], [0,0]])

		return 
	}
}

const factories = Object.freeze([
	new Type1Factory(),
	new Type2Factory(),
	new Type3Factory(),
	new Type4Factory(),
	new Type5Factory(),
	])

function solve(map) {
	let ret = 0

	for (let i = 0;  i < map.length; i++) {
		for (let j = 0; j < map[0].length; j++) {
			for (let type = 0; type < 5; type++) {
				for (let tetromino of factories[type].generate()) {
					ret = Math.max(ret, tetromino.covers(i, j, map))
				}
			}
		}
	}

	return ret
}

(function main() {
	const [tc, ...data] = readFileSync('./data/테트로미노.txt', {encoding : "utf-8"}).split("\n").map(l => l.trim())

	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0 ; it < testCases; it++) {
		const [n, m] = data[cur++].split(" ").map(i => parseInt(i))
		const map = new Array(n).fill(0).map(_ => data[cur++].split(" ").map(i => parseInt(i)))
		const answer = parseInt(data[cur++])
		console.log(answer, solve(map))
	}
})()