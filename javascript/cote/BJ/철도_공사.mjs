import {readFileSync} from 'fs'

const [N, M] = [500_000, 1_500_000];
const ID = 1_000_000


class Station {
	constructor(id, prev=null, next=null) {
		this.id = id
		this._prev = prev
		this._next = next 
	}

	get prev(){
		return this._prev
	}

	set prev(other){
		this._prev = other
		other._next = this 
	}

	get next(){
		return this._next
	}

	set next(other){
		this._next = other
		other._prev = this
	}
}

class Line {
	constructor(){
		this.stations = new Map()
		this.n = 0
	}

	static of(stations) {
		const ret = new Line()
		const head = new Station(stations[0])
		ret.n = stations.length
		ret.stations.set(stations[0], head)
		
		let cur = head
		for (let id of stations.slice(1)) {
			cur.next = new Station(id)
			cur = cur.next
			ret.stations.set(id, cur)
		}
		cur.next = head

		return ret
	}

	#find(id) {
		if (this.stations.has(id)) {
			return this.stations.get(id)
		}

		throw new Error("Unexpected")
	}

	insertNext(targetId, id) {
		const cur = this.#find(targetId)
		const ret = cur.next.id
		this.#insertBetween(cur, cur.next, id)
		
		return ret
	}

	insertPrev(targetId, id) {
		const cur = this.#find(targetId)
		const ret = cur.prev.id
		this.#insertBetween(cur.prev, cur, id)	

		return ret
	}

	#insertBetween(s1, s2, id) {
		const newStation = new Station(id)

		s1.next = newStation
		s2.prev = newStation

		this.n++
	}

	deleteNext(targetId) {
		const cur = this.#find(targetId)
		const ret = cur.next.id
		this.#deleteBetween(cur, cur.next)

		return ret
	}

	deletePrev(targetId) {
		const cur = this.#find(targetId)
		const ret = cur.prev.id
		this.#deleteBetween(cur.prev, cur)

		return ret
	}

	#deleteBetween(s1, s2) {
		s1.next = s2
		this.n--
	}

	get length() {
		return this.n
	}
}

function solve(line, construction) {
	const [type, ...rest] = construction

	if (type === "BN") {
		return line.insertNext(...rest)
	}

	if (type === "BP") {
		return line.insertPrev(...rest)
	}

	if (type === "CN") {
		return line.deleteNext(...rest)
	}

	if (type === "CP") {
		return line.deletePrev(...rest)
	}

	throw new Error("Unexpected")
}

(function main() {
	const [tc, ...data] = readFileSync('./data/철도_공사.txt', {encoding : 'utf-8'}).split("\n").map(l => l.trim())

	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const [n, m] = data[cur++].split(" ").map(i => parseInt(i))
		const line = Line.of(data[cur++].split(" ").map(i => parseInt(i)))
		
		const solved = []

		for (let c = 0; c < m ; c++) {
			const [type, ...rest ] = data[cur++].split(" ")
			const construction = [type, ...rest.map(i => parseInt(i))]
			solved.push(solve(line, construction))
		}		
		const answer = data[cur++].split(" ").map(i => parseInt(i))

		console.log(answer, solved)
	}
})()