import {readFileSync} from 'fs'

const N = 1000
const [START, END] = [1, 365]

class PriorityQueue {
	constructor(data = [], compareFunc = (a, b) => a - b){
		this.data = data
		this.compareFunc = compareFunc
	}

	pop() {
		if (this.length == 1) {
			return this.data.pop()
		}

		function bubbleDown(cur) {

			if (cur >= this.length) {
				return
			}

			const [left, right] = [2 * cur + 1, 2 * cur + 2]
			let min = cur

			if (left < this.length) {
				if (this.compareFunc(this.data[left], this.data[min])) {
					min = left
				}
			} else if (right < this.length) {
				if (this.compareFunc(this.data[right], this.data[min])) {
					min =right
				}
			}

			if (min != cur) {
				[this.data[min], this.data[cur]] = [this.data[cur], this.data[min]]
				bubbleDown.call(this, min)
			}
		}

		const ret = this.data[0]
		this.data[0] = this.data.pop()

		bubbleDown.call(this, 0)

		return ret
	}

	push(e) {		
		function bubbleUp(cur) {
			if (cur == 0) {
				return
			}

			const parent = Math.floor((cur + 1) / 2) - 1

			if (cur != 0 &&  this.compareFunc(this.data[cur], this.data[parent])) {
				[this.data[cur], this.data[parent]] = [this.data[parent], this.data[cur]]
				bubbleUp.call(this, parent)
			}
		}

		this.data.push(e)
		bubbleUp.call(this, this.length - 1)
	}

	get length() {
		return this.data.length
	}

	get front() {
		if (this.data.length == 0) {
			return null
		}

		return this.data[0]
	}
}

function solve(schedules) {

	const q = [...schedules]
	q.sort((a, b) => {
		if (a[0] != b[0]) {
			return a[0] - b[0]
		}
		return b[1] - a[1]
	})

	const pq = new PriorityQueue([], (a, b) => a[1] < b[1])
	
	let [acc, cur, start, end, max] = [0, q[0][0], q[0][0], 0, 0]
	
	while (q.length != 0 || pq.length != 0) {
		if (pq.length == 0 && q.length != 0) {
			start = q[0][0]
		}

		while (q.length != 0 && q[0][0] <= cur) {
			pq.push(q.shift())
		}

		while(pq.length != 0 && pq.front[1] < cur){
			const s = pq.pop()
			end = s[1]
		}

		if (pq.length != 0) {
			max = Math.max(max, pq.length)
		}

		if (pq.length == 0) {
			acc += max * (end - start + 1)
			max = 0
		}

		cur ++
	}	

	return acc
}

(function main(){

	const [tc, ...data] = readFileSync('data/달력.txt', {encoding : 'utf-8'})
		.split("\n")

	const testCases = parseInt(tc)

	let cur = 0
	for (let it = 0; it < testCases; it++) {
		console.log(`[${it + 1}]`)
		const n = parseInt(data[cur++])
		const schedules = new Array(n).fill(0)
			.map(_ => data[cur++].split(" ").map(i => parseInt(i)))
		const answer = parseInt(data[cur++])
		cur++
		console.log(answer, solve(schedules))
	}

})()