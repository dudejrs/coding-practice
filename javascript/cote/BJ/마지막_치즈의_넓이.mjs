import {readFileSync} from 'fs'

class Cheese {

	static Directions = Object.freeze([[0, 1], [1, 0], [0, -1], [-1, 0]])

	constructor(data) {
		this.data = data
	}	

	melt() {
		const visited = new Array(this.height).fill(0).map(_ => new Array(this.width).fill(false))

		function visit(y, x) {
			visited[y][x] = true

			for (const [dy, dx] of Cheese.Directions) {
				const [ny, nx] = [y + dy, x + dx]
				
				if (ny < 0 || ny >= this.height || nx < 0 || nx >= this.width) {
					continue
				}

				if (visited[ny][nx]) {
					continue
				}

				visited[ny][nx] = true
				if (this.data[ny][nx] === 1) {
					visited[ny][nx] = true
					this.data[ny][nx] = 0
				} else {
					visit.call(this, ny, nx)
				}
			}
		}

		let cur = {x : 0, y : 0}
		for (let [dy, dx] of Cheese.Directions) {
			
			if (dy ===  0) {
				for (let i = 0 ; i < this.width - 1; i++) {
					if (!visited[cur.y][cur.x] && this.data[cur.y][cur.x] == 0) {
						visit.call(this, cur.y, cur.x)
					}
					cur.x += dx
				}
			} else if (dx === 0) {
				for (let i = 0; i < this.height - 1; i++) {
					if (!visited[cur.y][cur.x] && this.data[cur.y][cur.x] == 0) {
						visit.call(this, cur.y, cur.x)
					}
					cur.y += dy
				}
			}
		}
	}

	get area() {
		return this.data.map(row => row.filter(i => i === 1).length).reduce((acc, count) => acc + count, 0)
	}

	get height() {
		return this.data.length
	}

	get width() {
		return this.data[0].length
	}
}


function solve(cheese) {	
	const myCheese = new Cheese(cheese)
	let currentArea = 0
	let time = 0

	while (myCheese.area != 0) {
		currentArea = myCheese.area  
		myCheese.melt()
		time++
	}

	return [time, currentArea]
}


(function main(){
	const [tc, ...data] = readFileSync('./data/마지막_치즈의_넓이.txt', {encoding : 'utf-8'}).split("\n").map(l => l.trim())

	const testCases = parseInt(tc)
	let cur = 0 
	for (let it = 0; it < testCases; it++) {
		const [h, w] = data[cur++].split(" ").map(i => parseInt(i))
		const cheese = new Array(h).fill(0).map(_ => data[cur++].split(" ").map(i => parseInt(i)))
		const completedMeltedTime = parseInt(data[cur++])
		const finalArea = parseInt(data[cur++])
		console.log([completedMeltedTime, finalArea], solve(cheese) )
	}
})()