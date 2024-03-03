
const TEST_CASES = 10
const MAX_VALUE = 100
const MAX_DEPTH = 20


class Node {
	constructor(value, left = null, right = null){
		this.value = value
		this.left = left
		this.right = right
	}

	*[Symbol.iterator](){
		const queue = [this]

		while (queue.length) {
			 const node = queue.shift()
			 if (node) {
			 	queue.push(node.left)
			 	queue.push(node.right)
			 	yield  node.value
			 } else {
			 	yield null
			 }
		}
	}
}

function initialize(depth = 0) {

	if (depth >= MAX_DEPTH) return null 
	if (depth > 0 && Math.random() / depth < 1 / MAX_DEPTH) return null
	
	const value = Math.floor(Math.random() * MAX_VALUE)
	const left = initialize(depth + 1)
	const right = initialize(depth + 1)


	return new Node(value, left, right)
}

function solve(node) {
	let longest = Number.NEGATIVE_INFINITY

	function dfs(cur) {
		if (! cur) return -1

		const left = dfs(cur.left)
		const right = dfs(cur.right)

		longest = Math.max(longest, left + right + 2)

		return Math.max(left, right) + 1
	}

	dfs(node)

	return longest
}

for (let it = 0; it < TEST_CASES; it++) {
	const node = initialize()
	console.log(solve(node))
}