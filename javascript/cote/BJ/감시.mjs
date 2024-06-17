import {readFileSync} from 'fs'

class CCTV {
	static LEFT = [0, -1]
	static RIGHT = [0, 1]
	static TOP = [-1, 0]
	static BOTTOM = [1, 0]

	constructor(directions, position){
		this.directions = directions
		this.position = position
	}

	static typeOf(index, position) {
		switch(index) {
			case 1 : 
				return new CCTV([CCTV.RIGHT], position)
			case 2 :
				return new CCTV([CCTV.LEFT, CCTV.RIGHT], position)
			case 3 : 
				return new CCTV([CCTV.TOP, CCTV.RIGHT], position)
			case 4 : 
				return new CCTV([CCTV.LEFT, CCTV.TOP, CCTV.RIGHT], position)
			case 5 : 
				return new CCTV([CCTV.LEFT, CCTV.TOP, CCTV.RIGHT, CCTV.BOTTOM], position)
		}
		throw new Error("UnSupported")
	}

	rotate() {
		for (let i = 0; i < this.directions.length; i++) {
			let d = this.directions[i]
			switch(d) {
				case CCTV.LEFT :  {
					this.directions[i] = CCTV.TOP
					break
				}
				case CCTV.TOP : {
					this.directions[i] = CCTV.RIGHT
					break
				}
				case CCTV.RIGHT : {
					this.directions[i] = CCTV.BOTTOM
					break
				}
				case CCTV.BOTTOM : {
					this.directions[i] = CCTV.LEFT
					break
				}
			}
		}
	}
}

class Room {
	constructor(data) {
		this.data = data 
		this.CCTVs = Room.getCCTVs(data)
	}

	static getCCTVs(data) {

		const ret = []

		for (let i = 0; i < data.length; i++) {
			for (let j = 0; j< data[0].length ; j++) {
				const m = data[i][j]
				if (m == 0 || m == 6) {
					continue
				}
				ret.push(CCTV.typeOf(m, [i, j]))
			}
		}

		return ret
	}

	static numberOfBlindSpots(data){
		return data.map(l => l.filter(i => i == 0).length).reduce((acc, count) => acc + count, 0)
	}


	*next() {
		function* search(i) {
			if (i == this.CCTVs.length) {

				const data = new Array(this.height).fill(0).map((_, i) => new Array(this.width).fill(0).map((_, j) => this.data[i][j]))
				for (let cctv of this.CCTVs) {
					const [y, x] = cctv.position
					for (let [dy, dx] of cctv.directions)  {
						let cur = {y, x}
						while (true) {
							const [ny, nx] = [cur.y + dy, cur.x + dx]
							if (ny < 0 || ny >= this.height || nx < 0 || nx >= this.width || this.data[ny][nx] == 6) {
								break
							}

							if (this.data[ny][nx] != 0) {
								cur.y += dy, cur.x += dx
								continue
							}

							data[ny][nx] = "#"
							cur.y += dy, cur.x += dx
						}
					}
				}

				yield Room.numberOfBlindSpots(data)
				return
			}

			const cctv = this.CCTVs[i]
			const [y, x] = cctv.position

			for (let it = 0; it < 4; it ++) {
				for (let state of search.call(this, i + 1)) {
					yield state
				}
				cctv.rotate()
			}
			return
		}

		for (let state of search.call(this, 0)) {
			yield state
		}

		return
	}
	
	get width() {
		return this.data[0].length
	}

	get height() {
		return this.data.length
	}
}

function solve(map) {
	const m = new Room(map)
	let ret = Number.MAX_VALUE

	for (let numberOfBlindSpots of m.next()) {
		ret = Math.min(ret, numberOfBlindSpots)
	}

	return ret
}

(function main() {
	const [tc, ...data] = readFileSync('./data/감시.txt', {encoding : 'utf-8'}).split("\n").map(l => l.trim())
	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const [n, m] = data[cur++].split(" ").map(i => parseInt(i)) 
		const map = new Array(n).fill(0).map(_ => data[cur++].split(" ").map(i => parseInt(i)))
		const answer = parseInt(data[cur++])
		console.log(answer ,solve(map))
	}
})()