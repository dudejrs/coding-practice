import {readFileSync} from 'fs'

const N = 10

class Cell {

	static quality =  {
		R : 7,
		B : 5,
		G : 3,
		Y : 2,
		W : 0
	}

	constructor(effect = 0, color = 'W') {
		this.effect = effect
		this.color = color
	}

	applyEffect(effect) {
		const tmp = this.effect + effect 

		if (tmp <= 0) {
			this.effect = 0
		} else if (tmp  >= 9) {
			this.effect = 9
		} else {
			this.effect = tmp
		}
	} 

	apply(other) {
		this.applyEffect(other.effect)
		this.color = other.color == "W" ? this.color : other.color
	}

	toString() {
		return `${this.effect}${this.color}`
	}

	get quality() {
		return Cell.quality[this.color] * this.effect
	}

	set value(cell) {
		this.effect = cell.effect
		this.color = cell.color
	}
}

class Gama {

	static ROW = 5
	static COL = 5

	constructor(){
		this.cells = Gama.defaultCells
	}

	static copyOf(gama) {
		const ret = new Gama()

		for (let i = 0; i < Gama.ROW; i++) {
			for (let j = 0; j < Gama.COL; j++) {
				ret.cells[i][j].value = gama.cells[i][j]
			}
		}

		return ret
	}

	apply(item, a, b) {
		const ret = Gama.copyOf(this)

		for (let i = 0; i < Item.ROW; i++) {
			let y = a + i

			for (let j = 0; j< Item.COL; j++) {
				let x = b + j

				ret.cells[y][x].apply(item.cells[i][j])
			}
		}

		return ret
	}

	static get defaultCells() {
		return new Array(Gama.ROW).fill(0)
			.map(_ => new Array(Gama.COL).fill(0).map(_ => new Cell()))
	}

	get quality() {
		let cost = 0;

		for (let i = 0; i < Gama.ROW; i++) {
			for (let j = 0; j < Gama.COL; j++) {
				cost += this.cells[i][j].quality
			}
		}

		return cost
	}

	print() {
		for (let i = 0; i < Gama.ROW; i++) {
			console.log(this.cells[i].map(c => c.toString()).join(" "))
		}
		console.log(this.quality)
		console.log()
	}
}

class Item{

	static ROW = 4
	static COL = 4
	
	constructor(effect = Item.defaultEffect, color = Item.defaultColor) {
		this.cells = new Array(Item.ROW).fill(0)
			.map((_, i) => 
				new Array(Item.COL).fill(0)
					.map((_ ,j) => new Cell(effect[i][j], color[i][j]))
			)
	}

	static rotate(origin) {
		const ret = new Item()

		for (let i = 0; i < Item.ROW; i++) {
			for (let j = 0; j < Item.COL; j++) {
				ret.cells[j][Item.ROW - 1 - i] = origin.cells[i][j]
			}
		}

		return ret
	}

	static copyOf(origin) {
		const ret = new Item()

		for (let i = 0; i < Item.ROW; i++) {
			for (let j = 0; j < Item.COL; j++) {
				ret.cells[i][j] = origin.cells[i][j]
			}
		}

		return ret
	}

	print() {
		for (let i = 0; i < Item.ROW; i++) {
			console.log(this.cells[i].map(c => c.toString()).join(" "))
		}
		console.log()
	}

	static get defaultEffect() {
		return new Array(Item.ROW).fill(0).map(_ => new Array(Item.COL).fill(0)) 
	}

	static get defaultColor() {
		return new Array(Item.ROW).fill(0).map(_ => new Array(Item.COL).fill('W')) 
	}
	
}

function solve(data) {

	const gama = new Gama()
	const items = data.map((v, i) => new Item(...v))

	let ret = 0
	const visited = new Array(items.length).fill(false)

	function search(gama, count) {
		if (count === 3) {
			ret = Math.max(ret, gama.quality)

			return
		}

		for (let i = 0; i < items.length; i++) {
			if (visited[i]) {
				continue
			}

			visited[i] = true

			let item = Item.copyOf(items[i]) 
			
			for (let r = 0; r < 4; r++) {
				item = Item.rotate(item)

				for (let a = 0; a < 2; a++) {
					for (let b = 0; b < 2; b++) {
						search(gama.apply(item, a, b), count + 1)
					}
				} 
			}
			visited[i] = false
		}
	}

	search(gama, 0)

	return ret
}

function main() {
	const [t, ...data] = readFileSync('./data/피아의_아틀리에_~신비한_대회의_연금술사~.txt', {encoding : 'utf-8'})
		.split("\n")

	const testCases = parseInt(t)

	let cur = 0;
	for (let it = 0; it < testCases; it++) {
		const n = parseInt(data[cur++])
		const items = new Array(n).fill(0)
			.map(_ => [new Array(4).fill(0).map(_ => data[cur++].split(" ").map(i => parseInt(i))),
				new Array(4).fill(0).map(_ => data[cur++].split(" "))])
		console.log(solve(items))
	}
}

main()