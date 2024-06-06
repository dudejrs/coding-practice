import {readFileSync} from 'fs'

class SawToothedWheel {
	
	static CLOCK_WISE = 1
	static COUNTER_CLOCK_WISE = -1
	static N_POLE = 0
	static S_POLE = 1

	constructor(data, index, left = null, right = null) {
		this.data = data
		this.index = index
		this.cur = 0
		this._left = left
		this._right = right
	}

	rotate(r) {	

		if (this.canRotateLeft) {
			this.left.#rotateLeft(r *  -1)
		}
		if (this.canRotateRight) {
			this.right.#rotateRight(r * -1)			
		}

		if (r === SawToothedWheel.CLOCK_WISE) {
			this.#rotateClockWise()
		} else {
			this.#rotateCounterClockWise()
		}
	}

	#rotateLeft(r) {
		if (this.canRotateLeft) {
			this.left.#rotateLeft(r * -1)
		}

		if (r === SawToothedWheel.CLOCK_WISE) {
			this.#rotateClockWise()
		} else {
			this.#rotateCounterClockWise()
		}
	}

	#rotateRight(r) {
		if (this.canRotateRight) {
			this.right.#rotateRight(r * -1)
		}

		if (r === SawToothedWheel.CLOCK_WISE) {
			this.#rotateClockWise()
		} else {
			this.#rotateCounterClockWise()
		}
	}

	#rotateClockWise() {
		this.cur = (8 + this.cur - 1) % 8
	}

	#rotateCounterClockWise() {
		this.cur = (this.cur + 1) % 8
	}

	get canRotateLeft() {
		return this.left && this.leftTooth ^ this.left.rightTooth
	}

	get canRotateRight() {
		return this.right && this.rightTooth ^ this.right.leftTooth	
	}

	get leftTooth() {
		return this.data[(this.cur + 6) % 8]
	}

	get rightTooth() {
		return this.data[(this.cur + 2) % 8]
	}

	get left() {
		return this._left
	}

	set left(l) {
		if (this._left === l){
			return
		}
		this._left = l
		l.right = this
	}

	get right() {
		return this._right
	}

	set right(r) {
		if (this._right === r) {
			return 
		}
		this._right = r
		r.left = this
	}

	get topTooth() {
		return this.data[this.cur] 
	}

	get score() {
		if (this.topTooth === SawToothedWheel.N_POLE) {
			return 0
		}
		return 1 << this.index
	}
}

function solve(sawToothedWheels, moves) {

	const wheels = sawToothedWheels.map((d, i) => new SawToothedWheel(d, i))

	for (let i = 1; i < 4; i++) {
		wheels[i].left = wheels[i - 1]
	}

	for (let [i, move] of moves) {
		wheels[i - 1].rotate(move)		
	}

	return wheels.reduce((acc, r) => acc + r.score, 0)
}

(function main() {
	const [tc, ...data] = readFileSync('./data/톱니바퀴.txt', {encoding : 'utf-8'}).split("\n").map(l => l.trim())

	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const sawToothedWheels = new Array(4).fill(0).map(_ => data[cur++].split("").map(i => parseInt(i)))
		const n = parseInt(data[cur++])
		const moves = new Array(n).fill(0).map(_ => data[cur++].split(" ").map(i => parseInt(i)))
		const answer = parseInt(data[cur++])
		console.log(answer, solve(sawToothedWheels, moves))
		// break
	}

})()