
const TEST_CASES = 10
const N = 100

class Node {
	constructor(value, next = null) {
		this.value = value
		this.next = next
	}

	*[Symbol.iterator]() {
		let cur = this

		while (cur) {
			yield cur.value
			cur = cur.next
		}

	}
}

function initialize() {
	const n = Math.floor(Math.random() * (N - 2)) + 2

	const root = new Node(0)
	let node = root

	for (let i = 0; i < n; i++) {
		node.next = new Node(node.value + 1)
		node = node.next
	}

	const end = Math.floor(Math.random() * (n - 1)) + 1
	const start = Math.floor(Math.random() * end)

	return [root, start, end]
}

function solve(node, start, end) {
	const root = new Node(-1, node)
	let [prev, cur] = [root, root.next]

	for (let i = 0; i < start; i++) {
		[prev, cur] = [prev.next, cur.next]
	}

	// prev ->  ... -> cur -> next -> next.next
	// prev -> next-> ... -> cur -> next.next
	for (let i = 0; i < end - start; i++) {
		let tmp = prev.next
		{	
			[prev.next, cur.next] = [cur.next, cur.next.next]
			prev.next.next = tmp
		}

	}

	return root.next
}

function main() {
	for (let i = 0; i < TEST_CASES; i++) {
		const [node, start, end] = initialize()
		console.log(...solve(node, start, end))
	}
}

main()