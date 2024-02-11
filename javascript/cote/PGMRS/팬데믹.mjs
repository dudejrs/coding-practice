import {readFile} from 'fs/promises'

class Cell {
	constructor(y, x) {
		this.y = y
		this.x = x
	}
}

function solve(row, col, maxVarius, queries) {
	const answer = new Array(row).fill(0)
		.map(_ => new Array(col).fill(0))
	const queue = []

	for (let [ny, nx] of queries) {
		const visited = new Array(row).fill(0)
			.map(_ => new Array(col).fill(false))

		queue.push(new Cell(ny-1, nx-1))

		while (queue.length) {
			const {y, x} = queue.shift()

			if (y < 0 || y >= row || x < 0 || x >= col) continue
			if (visited[y][x]) continue;
		
			visited[y][x] = true

			if (answer[y][x] < maxVarius) {
				answer[y][x] += 1
				continue
			}

			queue.push(new Cell(y-1, x))
			queue.push(new Cell(y, x-1))
			queue.push(new Cell(y, x+1))
			queue.push(new Cell(y+1, x))
		}
	}
	return answer
}

const lines = await readFile('data/팬데믹.txt', {encoding : 'UTF-8'})
	.then(lines => lines.split("\n").map(line => line.trim()))

let testcases = parseInt(lines[0])

let cur = 1
while (testcases > 0) {
	const [row, col, ...other] = lines[cur++].split(" ").map(i => parseInt(i))
	const maxVarius = parseInt(lines[cur++])
	const queries = new Array(parseInt(lines[cur++]))
		.fill(0)
		.map(_ => lines[cur++].split(" ")
			.map(i => parseInt(i))
			)
	const answer = new Array(row)
		.fill(0)
		.map(_ => lines[cur++]. split(" ")
			.map(i => parseInt(i))
			)

	console.log("answer: ", answer)
	console.log("solved: ", solve(row, col, maxVarius, queries))
	testcases--;
}