const TEST_CASES = 10
const MAX_VALUE = 100
const MAX_DEPTH = 20

class Node {
	constructor(value, l = null, right = null) {
		this.value = value
		this.left = l
		this.right = right
	}

	*[Symbol.iterator]() {
		const queue = [this]

		while (queue.length) {
			const node = queue.shift()
			
			if (node) {
				yield node.value
				queue.push(node.left)
				queue.push(node.right)
			} else {
				yield null
			}
		}
	}
}

function initialize(depth = 0) {

	if (depth >= MAX_DEPTH) {
		return null
	}

	if (depth > 0 && Math.random() / depth < 1 / MAX_DEPTH ) {
		return null
	}

	const value = Math.floor(Math.random() * MAX_VALUE)
	const [left, right] = [initialize(depth + 1), initialize(depth + 1)];

	return new Node(value, left, right)
}

function solve(node) {

	function dfs(cur) {
		if (!cur) {
			return null
		}

		const [left, right] = [dfs(cur.right), dfs(cur.left)]
		cur.left = left 
		cur.right = right
		
		return cur
	}

	return dfs(node)
}

function solve2(node) {
	const queue = [node]

	while (queue.length) {
		const cur = queue.shift()

		if (cur) {
			const [left, right] = [cur.right, cur.left]
			cur.left = left
			cur.right = right

			queue.push(cur.left)
			queue.push(cur.right)
		}
	}
	return node
}

for (let it = 0; it < TEST_CASES; it++) {
	const node = initialize()
	console.log(...node)
	console.log(...solve2(node))
}