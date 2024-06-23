import {readFileSync} from 'fs'

class Trial {
	static EMPTY = "-"
	static STRIKE = "S"
	static SPAIR = "P"

	constructor(result, prev= null, next = null) {
		this.result = result
		this._prev = prev
		this._next = next
	}

	get score() {
		if (parseInt(this.result)) {
			return parseInt(this.result)
		}

		if (this.result === Trial.STRIKE) {
			return 10
		}

		if (this.result === Trial.SPAIR) {
			if (!this.prev) {
				throw new Error("Unreachable State")
			}

			return 10 - this.prev.score
		}

		return 0
	}

	get prev() {
		return this._prev
	}
	
	set prev(p) {
		this._prev = p
		p._next = this
	}

	get next() {
		return this._next
	}

	set next(n) {
		this._next = n
		n._prev = this
	}

	get isStrike() {
		return this.result === Trial.STRIKE
	}
}

class Frame {
	static STRIKE = Symbol.for("strike")
	static SPAIR = Symbol.for("spair")

	constructor(trials = [], next = null) {
		this.trials = trials
		this.next = next
	}

	add(trial) {
		this.trials.push(trial)
	}

	get lastTrial() {
		return this.trials[this.trials.length - 1]
	}

	get score() {
		let acc = this.trials.map(trial => trial.score).reduce((acc, score) => acc + score)

		if (!this.flags) {
			return acc
		}

		if (this.flags === Frame.SPAIR) {
			return acc + this.lastTrial.next.score
		}
		
		return acc + this.lastTrial.next.score + this.lastTrial.next.next.score
	}

	get flags() {
		const results = this.trials.map(trial => trial.result)
		if (results.includes(Trial.SPAIR)) {
			return Frame.SPAIR
		}

		if (results.includes(Trial.STRIKE)) {
			return Frame.STRIKE
		}

		return null
	}
}


class Game {
	static MAX_FRAMES_LENGTH = 10

	constructor(frames = []){
		this.frames = frames
	}

	static ofTrials(scores) {
		const trials = []

		let prev = new Trial(scores.shift())
		trials.push(prev)

		while(scores.length > 0) {
			const cur = new Trial(scores.shift())
			cur.prev = prev
			prev = cur
			trials.push(cur)
		}

		const game = new Game()

		prev = undefined
		for (let it = 0; it < 10; it++) {
			const frame = new Frame()

			for (let f = 0; f < 2; f++) {
				const t = trials.shift()
				frame.add(t)
				if (t.isStrike) {
					break
				}
			} 
			
			if (prev) {
				prev.next = frame
			}
			prev = frame
			game.add(frame)
		}

		return game
	}

	add(frame) {
		if(this.frames.length > Game.MAX_FRAMES_LENGTH) {
			throw new Error("Game can't have more than 10 frames")
		}

		this.frames.push(frame)
	}

	get score() {
		return this.frames.map(frame => frame.score).reduce((acc, score) => acc + score)
	}
}


function solve(scores){
	const game = Game.ofTrials(scores)

	return game.score
}

(function main() {
	const [tc, ...data] = readFileSync('./data/볼링_점수_계산.txt', {encoding : 'utf-8'}).split("\n").map(l => l.trim());

	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const trials = data[cur++].split("")
		const answer = parseInt(data[cur++])
		console.log(answer, solve(trials))
	}
})()