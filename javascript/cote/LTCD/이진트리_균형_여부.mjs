
const TEST_CASES = 10
const MAX_VALUE = 100
const MAX_DEPTH = 20

class Node {

	constructor(value, left = null, right = null) {
		this.value = value
		this.left = left
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

	if (depth > 0 && Math.random() / depth < 0.000002 / MAX_DEPTH) {
		return null
	}

	const value = Math.floor(Math.random() * MAX_VALUE)
	const [left , right] = [initialize(depth + 1), initialize(depth + 1)]

	return new Node(value, left, right)
}

function solve(node) {

	function dfs(cur) {

		if (! cur) {
			return 0
		}

		const [left ,right] = [dfs(cur.left), dfs(cur.right)]
		
		if (left == -1 || right == -1 || Math.abs(left - right) > 1) {
			return -1
		}

		return Math.max(left, right) + 1
	}

	return dfs(node) != -1
}

for (let it = 0; it < TEST_CASES; it++) {
	const node = initialize()
	console.log(solve(node))
}