import {readFileSync} from 'fs'

class Ladder {
	
	static MEMBERS = new Array(26).fill('A').map((v, i) => String.fromCharCode(v.charCodeAt(0) + i)).join("")

	constructor(data, start, end) {
		this.index = Ladder.findEmptyRow(data)
		this.data = Ladder.calculate(data, start, end, this.index)
	}

	static findEmptyRow(data) {
		return data.findIndex(l => l.trim().split("").every(i => i =='?'))
	}

	static calculate(data, start, end, index) {
		const n = data.length
		const ret = new Array(data.length)

		let cur = start
		for (let i = 0; i < index; i++) {
			ret[i] = LadderRow.ofBegin(data[i], cur)
			cur = ret[i].end
		}

		cur = end 

		for (let i = n - 1; i > index; i--) {
			ret[i] = LadderRow.ofEnd(data[i], cur)
			cur = ret[i].begin
		}

		let a = (index === 0) ? start : ret[index - 1].end
		let b = (index === n - 1) ? end : ret[index + 1].begin
		
		ret[index] = LadderRow.of(a, b)

		return ret 
	}

	get filled() {
		return this.data[this.index].data
	}
}

class LadderRow {
	constructor(data, begin='', end=''){
		this.data = data
		this.begin = begin
		this.end = end
	}

	static ofBegin(data, begin) {
		return new LadderRow(data, begin, LadderRow.calculate(data, begin))
	}

	static ofEnd(data, end) {
		let begin = ''
		return new LadderRow(data, LadderRow.calculate(data, end), end)
	}

	static of(begin, end) {
		const n = begin.length
		const data = new Array(n - 1).fill('*')
		const map = new Map()

		let cur = 0
		while (cur < n) {
			if (begin.charAt(cur) == end.charAt(cur)) {
				data[cur] = "*"
				cur++
				continue
			}
			if (cur < n - 1 &&  begin.charAt(cur) == end.charAt(cur + 1) && begin.charAt(cur + 1) == end.charAt(cur)) {
				data[cur] = "-"
				cur += 2
				continue
			} else {
				return new LadderRow(new Array(n - 1).fill('x').join(""), begin, end)
			}

		}

		return new LadderRow(data.join(""), begin, end)
	}

	static calculate(data, target) {
		const ret = target.split("")

		for (let i = 0; i < data.length ; i++) {
			if (data.charAt(i) === '-') {
				[ret[i], ret[i + 1]] = [ret[i + 1], ret[i]]
			}
		}

		return ret.join("")
	}
}

function solve(target, ladder) {
	const myLadder = new Ladder(ladder, Ladder.MEMBERS.slice(0, target.length),target)

	return myLadder.filled
}

(function main(){
	const [tc, ...data] = readFileSync('./data/사다리_타기.txt', {encoding : 'utf-8'}).split("\n").map(l => l)

	let testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		const n = parseInt(data[cur ++])
		const h = parseInt(data[cur++])
		const target = data[cur++]
		let ladder = new Array(h).fill(0).map( _ => data[cur++].trim())
		let answer = data[cur++]
		console.log(answer, solve(target, ladder))
	}

})()