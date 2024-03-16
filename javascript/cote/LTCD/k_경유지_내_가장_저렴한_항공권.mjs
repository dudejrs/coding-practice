const N = 20
const MAX_COST = 100
const TEST_CASES = 10

class Heap {
	constructor(data, compare){
		this.data = [0, ...data]
		this.compare = compare
		this.init()
	}

	init() {
		for (let k = Math.floor(this.data.length / 2); k >= 0; k--) {
			this.heapify(k)
		}
	}

	heapify(k = 1){
		const left = 2 * k 
		const right = 2 * k + 1
		let min = k

		if (right < this.data.length) {
			if (this.data[left] < this.data[right]) {
				min = left
			} else {
				min = right
			}
		} else if (left < this.data.length) {
			min = left
		} else {
			return
		}

		if (this.compare(this.data[min], this.data[k])) {
			[this.data[min], this.data[k]] = [this.data[k], this.data[min]] 
			this.heapify(min)
		}
	}

	pop(){
		if (this.length() == 1){
			return this.data.pop()
		}

		const ret = this.data[1]
		this.data[1] = this.data.pop()
		this.heapify(1)

		return ret
	}

	push(item) {
		this.data.push(item)
		if (this.length() == 1) {
			return
		}

		[this.data[1], this.data[this.length()]] = [this.data[this.length()], this.data[1]]
		this.heapify(1)
	}

	length() {
		return this.data.length - 1
	}

	empty() {
		return this.length() == 0
	}
}

class State {
	constructor(price, index, k) {
		this.price = price
		this.index = index
		this.k = k
	}
}

function initialize(n) {
	const edges = []
	const counts = new Array(n).fill(0)

	for (let i = 0; i < n; i++) {
		for (let j = i + 1; j < n; j++){
			if (Math.random() < 0.25) {
				continue;
			}
			edges.push([i, j, Math.floor(Math.random() * MAX_COST) + 1])
			counts[i] += 1
			counts[j] += 1
		}
	}

	const counted = counts.map((v, i) => [i, v]).toSorted((a, b) => b[1] - a[1])

	return {edges, src: counted[0][0], dst: counted[2][0]};
}

function solve(edges, src, dst, k, n) {

	const graph = new Array(n).fill(0).map(i => new Array())

	for (let [i, j, price] of edges) {
		graph[i].push([j, price])
		graph[j].push([i, price])
	}

	const heap = new Heap([new State(0, src, k)], 
		(a, b) => a.price - b.price)

	while (!heap.empty()) {
		const cur = heap.pop()

		if (cur.index == dst) {
			return cur.price
		}

		if (cur.k >= 0) {
			for (let [next, price] of graph[cur.index]) {
				heap.push(new State(cur.price + price, next, cur.k - 1))
			}
		}
	}

	return -1
}

for (let it = 0; it < TEST_CASES; it++) {
	const n = Math.floor(Math.random() * (N - 3)) + 3
	const k = Math.floor(Math.random() * (n - 1)) + 1
	const {edges, src, dst} = initialize(n)
	console.log(solve(edges, src, dst, k, n))
}

