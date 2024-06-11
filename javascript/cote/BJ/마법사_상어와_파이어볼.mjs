import {readFileSync} from 'fs'

const [N, K] = [50, 1000]
const M = Math.pow(N, 2)
const MESS = 1000
const S = 1000


class Magician {
	constructor(n, fireballs) {
		this.n = n
		this.fireballs = fireballs.map(([r, c, ...args]) => new Fireball(r-1, c-1,...args, n))
	}

	spell() {
		this.fireballs = this.#move().haveChemicalReaction()
	}

	#move() {
		const ret = new Grid(this.n)
		
		for (let fireball of this.fireballs) {
			fireball.move()
			ret.add(fireball)
		}

		return ret
	}
	
	getTotalFireballMess() {
		return this.fireballs.map(fireball => fireball.m).reduce((acc, m) => acc + m, 0)
	}
}

class Fireball {

	static Directions = [[-1, 0], [-1, 1], [0, 1], [1, 1], [1, 0], [1, -1], [0, -1], [-1, -1]]

	constructor(r, c, m, s, d, n) {
		this.r = r
		this.c = c
		this.m = m
		this.s = s
		this.d = d
		this.n = n
	}

	move() {
		let [dy, dx] = Fireball.Directions[this.d].map(i => i * this.s)
		this.r = (this.n + this.r + dy) % this.n
		this.c = (this.n + this.c + dx) % this.n
	}

	get position() {
		return [this.r, this.c]
	}
}

class Grid {
	constructor(n) {
		this.n = n 
		this.data = new Array(n).fill(0).map(_ => new Array(n).fill(0).map(_ => []))
	}

	static isAllOddOrEven(array){
		let cur = array[0] % 2 

		for (let elem of array.slice(1)) {
			if (elem % 2 !== cur) {
				return false
			}
		}

		return true
	}

	add(fireball) {
		const [r, c] = fireball.position
		this.data[r][c].push(fireball)
	}

	haveChemicalReaction() {
		const ret = []

		for (let i = 0; i < this.n; i++){
			for (let j = 0; j < this.n; j++) {

				if (this.data[i][j].length == 1) {
					ret.push(...this.data[i][j])
					continue
				}

				const mess = Math.floor(this.data[i][j].map(f => f.m).reduce((acc, m) => acc + m, 0) / 5)
				
				if (mess === 0) {
					continue
				}

				const speed =  Math.floor(this.data[i][j].map(f => f.s).reduce((acc, s) => acc + s, 0) / this.data[i][j].length) 
				const directions = Grid.isAllOddOrEven(this.data[i][j].map(f => f.d)) ? [0, 2, 4, 6] : [1, 3, 5, 7]

				for (let d of directions) {
					ret.push(new Fireball(i, j, mess, speed, d, this.n))
				}
			}
		}

		return ret
	}
}

function solve(n, fireballs, k) {
	const magician = new Magician(n, fireballs)

	for (let i = 0; i < k; i++) {
		magician.spell()
	}

	return magician.getTotalFireballMess()
}

(function main() {

	const [tc, ...data] = readFileSync('./data/마법사_상어와_파이어볼.txt', {encoding : 'utf-8'}).split("\n").map(l => l.trim())

	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		let [n, m, k] = data[cur++].split(" ").map(i => parseInt(i)).slice(0,3)
		const fireballs = new Array(m).fill(0).map(_ => data[cur++].split(" ").map(i => parseInt(i)).slice(0, 5))
		const answer = parseInt(data[cur++])
		console.log(answer, solve(n, fireballs, k))
	}

})()