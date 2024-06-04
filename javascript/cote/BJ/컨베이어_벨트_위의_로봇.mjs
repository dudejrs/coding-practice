import {readFileSync} from 'fs'

class Robot {
	constructor(position) {
		this.position = position
	}
}

class ConveyerBelt  {
	constructor(n, k, durability) {
		this.k = k
		this.n = n
		this.durability = durability
		this._current = 0
		this.robots = []
	}

	exec() {
		this.#moveBelt()
		this.#unload()
		this.#moveRobots()
		this.#unload()
		this.#load()
	}

	#moveBelt() {
		this._current = (2 * this.n + this._current - 1) % (2 * this.n)
	}

	#moveRobots() {
		let before;
		for (let robot of this.robots) {
			let next = (robot.position + 1) % (2 * this.n)
			if (next === before || this.durability[next] == 0)  {
				before = robot.position
				continue
			}
			robot.position = next
			this.durability[next] -= 1
		}
	}

	#load() {
		if (this.current == 0) {
			return
		}
		this.robots.push(new Robot(this._current))
		this.current =  this.current - 1
	}

	#unload() {
		while(this.robots.length != 0 && this.robots[0].position === this._last) {
			const p = this.robots.shift()
		}
	}

	get isRunnable() {
		return this.durability.filter(d => d === 0).length < this.k
	}

	get current() {
		return this.durability[this._current]
	}
	set current(val) {
		this.durability[this._current] = val
	}

	get _last() {
		return (this._current + this.n - 1) % (2 * this.n)
	}

	get last() {
		return this.durability[this._last]
	}

	get state() {
		return this.durability.concat(this.durability).slice(this._current, (this._current + this.n * 2))
	}
}

function solve(n, k, durability) {
	const conveyerBelt = new ConveyerBelt(n, k, durability)
	let count = 0
	
	while (conveyerBelt.isRunnable) {
		conveyerBelt.exec()
		count++
	}
	return count
}

(function main(){
	const [tc, ...data] = readFileSync('./data/컨베이어_벨트_위의_로봇.txt', {encoding : 'utf-8'}).split("\n").map(l => l.trim())

	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const [n, k] = data[cur++].split(" ").map(i => parseInt(i))
		const durability = data[cur++].split(" ").map(i => parseInt(i))
		const answer = parseInt(data[cur++])

		console.log(answer, solve(n, k,  durability))
	}
})()