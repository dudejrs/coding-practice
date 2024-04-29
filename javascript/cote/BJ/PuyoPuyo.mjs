import {readFileSync} from 'fs'

class Map {

	static directions = [[-1, 0],[1, 0],[0, 1],[0, -1]]

	constructor(map) {
		this.map = map.map(
			line => line.split(""))
		this.ylim = map.length
		this.xlim = map[0].length
	}

	burst(){
		let combo = 0;
		let triggers = this.#find(); 
		while (triggers.length !== 0) {
			for (let [y, x] of triggers) {
				this.#reset(y, x)
			}

			this.#moveDown()
			triggers = this.#find()
			combo++
		}

		return combo
	}

	#find() {
		const ret = []
		const visited = new Array(this.ylim).fill(0)
		.map(_ => new Array(this.xlim).fill(false));

		for (let i = 0; i < this.ylim; i++) {
			for (let j = 0; j < this.xlim; j++) {
				if (this.map[i][j] !== "." && !visited[i][j] && this.#count(i, j, visited) >= 4) {
					ret.push([i, j])
				}
			}
		}

		return ret
	}

	#count(y, x, visited) {
		const queue = []
		queue.push([y, x, this.map[y][x]])
		
		let count = 0;
		while(queue.length !== 0) {
			const [y, x, color] = queue.shift()
			visited[y][x] = true
			count++


			for (const [dy, dx] of Map.directions) {
				const [ny, nx] = [y + dy, x + dx];
				
				if (ny < 0 || ny >= this.ylim || nx < 0 || nx >= this.xlim) {
					continue
				}

				if (!visited[ny][nx] && this.map[ny][nx] === color) {
					queue.push([ny, nx, this.map[ny][nx]])
				}
			}

		}

		return count;
	}

	#reset(y, x) {
		const queue = []
		queue.push([y, x, this.map[y][x]])
		
		while(queue.length !== 0) {
			const [y, x, color] = queue.shift()
			this.map[y][x] = "."

			for (const [dy, dx] of Map.directions) {
				const [ny, nx] = [y + dy, x + dx];
				
				if (ny < 0 || ny >= this.ylim || nx < 0 || nx >= this.xlim) {
					continue
				}

				if (this.map[ny][nx] === color) {
					queue.push([ny, nx, this.map[ny][nx]])
				}
			}
		}		
	}

	#moveDown() {
		for (let col = 0; col < this.xlim; col++) {
			const stack =[]

			for (let row = 0; row < this.ylim; row++) {
				if (this.map[row][col] !== ".") {
					stack.push(this.map[row][col])
				}
			}

			for (let i = this.ylim - 1; i >= 0; i--) {
				if (stack.length != 0) {
					this.map[i][col] = stack.pop();
				} else {
					this.map[i][col] = "."
				}
			}
		}
	}
}

function solve(map) {
	const m = new Map(map);

	return m.burst();
}

function main() {
	const data = readFileSync('data/PuyoPuyo.txt', {encoding : 'utf-8'})
		.split("\n");
	let cur = 0;
	const testCases = parseInt(data[cur++]);

	for (let it = 0; it < testCases; it++) {
		const [row, col] = data[cur++].split(" ")
			.map(i => parseInt(i))

		const map = new Array(row).fill()
			.map(_ => data[cur++])

		const answer = parseInt(data[cur++])
		console.log(answer, solve(map))
	}
}

main()