import {readFileSync} from 'fs'

const [N, M] = [300, 300];
const R = Math.pow(10, 9);

class Position {
	constructor(y, x) {
		this. y = y
		this. x = x
	}
}

class Matrix {
	static Directions = [[0, 1], [1, 0], [0, -1], [-1, 0]]

	constructor(matrix) {
		this.n = matrix.length
		this.m = matrix[0].length
		this.nums = Matrix.extractNums(matrix)
		this.child = Matrix.extractChild(matrix)
	}

	static extractNums(matrix) {
		const ret = []
		let [n, m] = [matrix.length, matrix[0].length]

		if (Math.min(n, m) == 1) {
			return matrix.flat()
		}
		
		let cur = new Position(0, 0)
		for (let [dy, dx] of Matrix.Directions) {
			if (dy == 0) {
				const target = dx > 0 ? m - 1 : 0;
				while(cur.x != target) {
					ret.push(matrix[cur.y][cur.x])
					cur.x += dx
				}

			} else {
				const target = dy > 0 ? n - 1 : 0;
				while(cur.y != target) {
					ret.push(matrix[cur.y][cur.x])
					cur.y += dy
				}
			}
		}		

		return ret
	}

	static extractChild(matrix) {
		const [n, m] = [matrix.length, matrix[0].length]
		if (Math.min(n, m) <= 2) {
			return null
		}
		const childMatrix = matrix.slice(1, n -1).map(row => row.slice(1, m - 1))
		

		return new Matrix(childMatrix)
	}

	static rotateNums(nums, r) {
		return nums.concat(nums).slice(r % nums.length, r % nums.length + nums.length)
	}

	rotate(r) {
		const nums = Matrix.rotateNums(this.nums, r)

		if (this.n === 1) {
			return [nums]
		} 
		if (this.m === 1) {
			return nums.map(num => [num])
		}

		const ret = new Array(this.n).fill(0).map(_ => new Array(this.m).fill(0))

		let cur = new Position(0, 0)

		for (let [dy, dx] of Matrix.Directions) {

			if (dy == 0) {
				const target = dx > 0 ? this.m - 1 : 0;
				while(cur.x != target) {
					ret[cur.y][cur.x] = nums.shift()
					cur.x += dx
				}

			} else {
				const target = dy > 0 ? this.n - 1 : 0;
				while(cur.y != target) {
					ret[cur.y][cur.x] = nums.shift()
					cur.y += dy
				}
			}
		}

		if (!this.child) {
			return ret
		}

		const childMatrix = this.child.rotate(r)

		for (let i = 1, a = 0; i < this.n - 1; i++, a++) {
			for (let j = 1, b = 0; j < this.m - 1; j++, b++) {
				ret[i][j] = childMatrix[a][b]
			}
		}

		return ret
	}
}


function solve(matrix, r) {
	const m = new Matrix(matrix)

	return m.rotate(r)
}

(function main() {
	const [tc, ...data] = readFileSync('./data/배열_돌리기2.txt', {encoding : 'utf-8'}).split("\n").map(l => l.trim())

	const testCases = parseInt(tc) 

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const [n, m, r] = data[cur++].split(" ").map(i => parseInt(i))
		const matrix = new Array(n).fill(0).map(_ => data[cur++].split(" ").map(i => parseInt(i)))
		const answer = new Array(n).fill(0).map(_ => data[cur++].split(" ").map(i => parseInt(i)))

		let ret = solve(matrix, r)
		console.log(ret.map(i=> i.join(" ")).join("\n"))
	}
})()